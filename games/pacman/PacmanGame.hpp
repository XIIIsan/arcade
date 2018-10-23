/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <unordered_map>
#include "Enemy.hpp"
#include "Game/IGameLib.hpp"
#include "Utils/TextBox.hpp"
#include "Utils/Vect.hpp"
#include "Utils/PixelBox.hpp"
#include "Utils/Keys.hpp"
#include "Utils/Color.hpp"

namespace Arcade {
	class PacmanGame : public IGameLib {
	public:
		enum Entity {
			VOID,
			WALL,
			CHERRY,
			DOT,
			PLAYER,
			ENEMY
		};
		PacmanGame();
		const std::string getName() const override;
		bool init() override;
		bool stop() override;
		bool applyEvent(Arcade::Keys key) override;
		bool update() override;
		void refresh(IGraphicLib &graphicLib) override;
		size_t getScore() override;
	private:
		void drawMap(Arcade::Vect<size_t> posInVec, Arcade::Vect<size_t> &shift);
		void printMap(IGraphicLib &);
		void printEnemy();
		void drawPlayer();
		void movePlayer();
		bool isValid(Arcade::Vect<size_t> posEnemy, int y, int x);
		void gameOver();

		Arcade::PixelBox _pixelBox;
		Arcade::TextBox _textBox;
		std::vector<std::string> _mapVectorCp;
		std::string _name;
		std::vector<Arcade::Pacman::Enemy> _enemy;
		Arcade::Pacman::ACharacter _player;
		Arcade::Keys _playerDirection;
		int _score;
		bool _gameOver;
		int _coefSize;

		Arcade::Vect<size_t> _shift;
		static const std::vector<std::string> _mapVector;
		static const std::unordered_map<Entity, Arcade::Color> _colors;
		static const std::unordered_map<char, Entity> _characters;
		static const std::unordered_map<Keys, Vect<int>> _directions;
	};
};
