//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// SolarFoxGame.hpp
//

#pragma once

#include <unordered_map>
#include <functional>
#include "Core/Keys.hpp"
#include "Game/IGameLib.hpp"
#include "Player.hpp"
#include "Beam.hpp"
#include "Enemy.hpp"

namespace std {

	template <>
	struct hash<Arcade::SolarFox::Direction>
	{
		std::size_t operator()(const Arcade::SolarFox::Direction &k) const
		{
			return ((hash<int>()(k)));
		}
	};

}

namespace Arcade {

	class SolarFoxGame;
	using SolarFoxMap = std::unordered_map<Arcade::Keys, std::function<bool(Arcade::SolarFoxGame*)>>;

	class SolarFoxGame : public IGameLib {
	public:
		SolarFoxGame();

		/* Get the name of the game */
		const std::string getName() const override;

		/* Resources handling */
		// Initializes the library
		bool init() override;

		// Unloads the library
		bool stop() override;

		// Processes the key obtained by the IGraphicLib from the user to update the game state
		bool applyEvent(Keys key) override;

		// Updates the game state. (Move the player forward and/or move the NPCs)
		bool update() override;

		// Renders the game state to the screen. This should call IGraphicLib::refresh() to display content to the user.
		void refresh(IGraphicLib &graphicLib) override;
		void refreshGame(IGraphicLib &graphicLib);
		void refreshGameOver(IGraphicLib &graphicLib);
		void displayTemp(Arcade::PixelBox &, Arcade::Vect<size_t> &rectSize);

		// To call at the end of the execution of the game (after the player loose or win) for getting his score
		size_t getScore() override;
		void updateScore();
		void checkBeams();
		void checkVictory();

		void initMap();
		char getMapChar(unsigned int, unsigned int) const;

		bool checkPlayerStatus() const;
		bool handleKeyLeft();
		bool handleKeyRight();
		bool handleKeyShoot();

		static const Arcade::Vect<size_t> _mapSize;
	private:
		std::string _name;
		size_t _score;
		std::vector<std::string> _map;
		SolarFox::Player _player;
		bool _gameStatus;
		std::vector<Arcade::SolarFox::Beam> _beams;

		std::vector<Arcade::SolarFox::Enemy> _enemies;
		static const std::unordered_map<char, Arcade::Color> _colors;
		static const Arcade::SolarFoxMap _keys;
		static const std::unordered_map<Arcade::SolarFox::Direction, Arcade::Vect<size_t>> _enemyPos;
	};
}
