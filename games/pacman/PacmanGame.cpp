/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "PacmanGame.hpp"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "../../include/Utils/Vect.hpp"
#include "../../include/Utils/PixelBox.hpp"
#include "../../include/Utils/Keys.hpp"
#include "../../include/Utils/Color.hpp"
#include "../../include/Utils/TextBox.hpp"

const std::unordered_map<char, Arcade::PacmanGame::Entity> Arcade::PacmanGame::_characters = {
	{'0', VOID},
	{'1', WALL},
	{'2', DOT},
	{'3', CHERRY}
};


const std::unordered_map<Arcade::PacmanGame::Entity, Arcade::Color> Arcade::PacmanGame::_colors = {
	{VOID, Arcade::Color(0, 0, 0)},
	{DOT, Arcade::Color(255, 255, 255)},
	{PLAYER, Arcade::Color(255, 255, 0)},
	{WALL, Arcade::Color(100, 100, 100)},
	{CHERRY, Arcade::Color(255, 0, 0)},
	{ENEMY, Arcade::Color(0, 0, 255)},
};

const std::unordered_map<Arcade::Keys, Arcade::Vect<int>> Arcade::PacmanGame::_directions = {
	{NONE, {0, 0}},
	{UP, {0, -1}},
	{DOWN, {0, 1}},
	{LEFT, {-1, 0}},
	{RIGHT, {1, 0}}
};

const std::vector<std::string> Arcade::PacmanGame::_mapVector = {
	{"1111111111111111111111111111"},
	{"1222222222222112222222222221"},
	{"1211112111112112111112111121"},
	{"1311112111112112111112111131"},
	{"1211112111112112111112111121"},
	{"1222222222222222222222222221"},
	{"1211112112111111112112111121"},
	{"1211112112111111112112111121"},
	{"1222222112222112222112222221"},
	{"1111112111112112111112111111"},
	{"1111112111112112111112111111"},
	{"1111112112222222222112111111"},
	{"1111112112111001112112111111"},
	{"2222222222100000012222222222"},
	{"1111112112100000012112111111"},
	{"1111112112111111112112111111"},
	{"1111112112222222222112111111"},
	{"1111112112111111112112111111"},
	{"1111112112111111112112111111"},
	{"1222222222222112222222222221"},
	{"1211112111112112111112111121"},
	{"1211112111112112111112111121"},
	{"1322112222222222222222112231"},
	{"1112112112111111112112112111"},
	{"1112112112111111112112112111"},
	{"1222222112222112222112222221"},
	{"1211111111112112111111111121"},
	{"1211111111112112111111111121"},
	{"1322222222222222222222222231"},
	{"1111111111111111111111111111"}
};

Arcade::PacmanGame::PacmanGame()
	:
	_textBox("Score = 0", Arcade::Vect<size_t>(1, 1), 25, {0, 0, 0}),
	_mapVectorCp(_mapVector),
	_name("Pacman"),
	_playerDirection(Arcade::UP),
	_score(0),
	_gameOver(false),
	_coefSize(17)
{}

const std::string Arcade::PacmanGame::getName() const
{
	return this->_name;
}

void Arcade::PacmanGame::printEnemy()
{
	for (auto &tmp : _enemy) {
		if (tmp.isAlive())
			this->_pixelBox.putRect(tmp.getPos() * this->_shift,
				this->_shift, tmp.getColor());
		else
			this->_pixelBox.putRect(tmp.getPos() * this->_shift,
				this->_shift, _colors.at(ENEMY));
	}
}

void Arcade::PacmanGame::drawPlayer()
{
	this->_pixelBox.putRect(this->_player.getPos() * this->_shift,
		this->_shift, _player.getColor());
}

void Arcade::PacmanGame::drawMap(Arcade::Vect<size_t> posInVec, Arcade::Vect<size_t> &shift)
{
	Arcade::Color color(0, 0, 0);
	auto chara = this->_mapVectorCp[posInVec.getY()][posInVec.getX()];
	if (_characters.count(chara) > 0)
		if (_colors.count(_characters.at(chara)) > 0)
		color = _colors.at(_characters.at(chara));
	this->_pixelBox.putRect(posInVec * shift, shift, color);
}

void Arcade::PacmanGame::printMap(IGraphicLib &lib)
{
	auto size = lib.getScreenSize();
	this->_pixelBox = Arcade::PixelBox(size, Arcade::Vect<size_t>(0, 0),
		this->_colors.at(VOID));
	for (size_t y = 0; y < this->_mapVectorCp.size(); y++) {
		for (size_t x = 0; x < this->_mapVectorCp[y].size(); x++) {
			this->drawMap(Arcade::Vect<size_t>(x, y),
			        this->_shift);
		}
	}
}

void Arcade::PacmanGame::gameOver()
{
	this->_gameOver = true;
}

void Arcade::PacmanGame::movePlayer()
{
	auto pos = _player.getPos();
	auto dir = _directions.at(_playerDirection);
	auto &chara = this->_mapVectorCp[pos.getY() + dir.getY()][pos.getX() + dir.getX()];

	if (chara != '1') {
		_player.setPos({pos.getX() + dir.getX(), pos.getY() + dir.getY()});
		auto x = _player.getPos().getX();
		switch (chara) {
		case '2':
			chara = '0';
			_score += 10;
			break;
		case '3':
			chara = '0';
			_score += 50;
			for (auto &tmp : _enemy)
				tmp.kill();
			break;
		default:
			break;
		}
		for (size_t i = 0; i < _enemy.size(); i++)
			if (_player.getPos() == _enemy[i].getPos() &&
				_enemy[i].isAlive())
				this->gameOver();
			else if (_player.getPos() == _enemy[i].getPos()) {
				_enemy.erase(_enemy.begin() + i);
				_score += 100;
			}
		if (x == 0)
			_player.setPos({this->_mapVector[0].size() - 1, _player.getPos().getY()});
		else if (x == _mapVector[0].size() - 1)
			_player.setPos({1, _player.getPos().getY()});
	}
}

bool Arcade::PacmanGame::init()
{
	_score = 0;
	_gameOver = false;
	this->_playerDirection = Arcade::NONE;
	this->_player = Arcade::Pacman::ACharacter(_colors.at(PLAYER),
		{14, 16});
	this->_enemy.emplace_back(Arcade::Pacman::Enemy(Color(255, 0, 0),
		Vect<size_t>(16, 14)));
	this->_enemy.emplace_back(Arcade::Pacman::Enemy(Color(255, 0, 255),
		Vect<size_t>(16, 13)));
	this->_enemy.emplace_back(Arcade::Pacman::Enemy(Color(0, 0, 255),
		Vect<size_t>(11, 13)));
	this->_enemy.emplace_back(Arcade::Pacman::Enemy(Color(255, 255, 0),
		Vect<size_t>(11, 14)));
	this->_mapVectorCp = this->_mapVector;
	return true;
}

bool Arcade::PacmanGame::stop()
{
	_mapVectorCp = _mapVector;
	_enemy.clear();
	_playerDirection = Arcade::NONE;
	return _gameOver;
}

bool Arcade::PacmanGame::applyEvent(Keys key)
{
	if (key == Arcade::LEFT || key == Arcade::RIGHT
		|| key == Arcade::UP || key == Arcade::DOWN) {
		_playerDirection = key;
		return true;
	}
	return false;
}

bool Arcade::PacmanGame::update()
{
	char score[20];

	sprintf(score, "Score = %d", _score);
	_textBox.setValue(score);
	if (!this->_gameOver) {
		this->movePlayer();
	}
	return true;
}

void Arcade::PacmanGame::refresh(IGraphicLib &graphicLib)
{
	auto size = graphicLib.getScreenSize();
	this->_shift = size / Arcade::Vect<size_t>(
		this->_mapVectorCp[0].size(), this->_mapVectorCp.size());
	this->printMap(graphicLib);
	this->drawPlayer();
	this->printEnemy();
	graphicLib.drawPixelBox(_pixelBox);
	graphicLib.drawText(_textBox);
	graphicLib.refreshWindow();
}

size_t Arcade::PacmanGame::getScore()
{
	return static_cast<size_t>(this->_score);
}
