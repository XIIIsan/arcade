//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// SolarFoxGame.cpp
//

#include <zconf.h>
#include <iostream>
#include "SolarFoxGame.hpp"

const Arcade::Vect<size_t> Arcade::SolarFoxGame::_mapSize(33, 33);

const std::unordered_map<char, Arcade::Color> Arcade::SolarFoxGame::_colors = {
	{'0', {0, 0, 0, 255}}, // void movable
	{'1', {0, 0, 0, 255}}, // void immovable
	{'2', {0, 255, 0, 255}}, // Player
	{'3', {255, 255, 255, 255}}, // Asteroïds
	{'4', {255, 0, 0, 255}}, // Enemy
	{'5', {0, 0, 255, 255}}, // Beams
	{'6', {100, 100, 100, 255}}, // Walls
};

const std::unordered_map<Arcade::SolarFox::Direction, Arcade::Vect<size_t>> Arcade::SolarFoxGame::_enemyPos = {
	{Arcade::SolarFox::DOWN, Arcade::Vect<size_t>{0, 1}},
	{Arcade::SolarFox::RIGHT, Arcade::Vect<size_t>{1, 0}},
	{Arcade::SolarFox::LEFT, Arcade::Vect<size_t>{_mapSize.getX() - 2, _mapSize.getY() - 1}},
	{Arcade::SolarFox::UP, Arcade::Vect<size_t>{_mapSize.getX() - 1, _mapSize.getY() - 2}}
};

const Arcade::SolarFoxMap Arcade::SolarFoxGame::_keys = {
	{Arcade::LEFT,  &Arcade::SolarFoxGame::handleKeyLeft},
	{Arcade::RIGHT, &Arcade::SolarFoxGame::handleKeyRight},
	{Arcade::SPACE, &Arcade::SolarFoxGame::handleKeyShoot},
};

Arcade::SolarFoxGame::SolarFoxGame()
	: _name("SolarFox"), _score(0), _player()
{
}

size_t Arcade::SolarFoxGame::getScore()
{
	return _score;
}

const std::string Arcade::SolarFoxGame::getName() const
{
	return _name;
}

char Arcade::SolarFoxGame::getMapChar(unsigned int i, unsigned int j) const
{
	char ret('0');
	if (i < 3 || i > this->_mapSize.getY() - 3 ||
		j < 3 || j > this->_mapSize.getX() - 3)
		ret = '1';
	else {
		auto randomness = 50;
		auto tmp = random() % randomness;
		if (tmp > randomness - 3)
			ret = '3';
		else if (tmp < 1)
			ret = '6';
	}
	return ret;
}

void Arcade::SolarFoxGame::initMap()
{
	auto x = this->_mapSize.getX();
	auto y = this->_mapSize.getY();
	for (unsigned int i = 0; i < y; i++) {
		std::string line;
		for (unsigned int j = 0; j < x; j++)
			line.push_back(this->getMapChar(i, j));
		this->_map.push_back(line);
	}
	for (unsigned int i = y / 2 - 1; i <= y / 2 + 1; i++) {
		for (unsigned int j = x / 2 - 1; j <= x / 2 + 1; j++)
			this->_map[i][j] = '0';
	}
	this->_player.setPos(Arcade::Vect<size_t>(x / 2, y / 2));
}

bool Arcade::SolarFoxGame::init()
{
	srandom(getpid() * time(nullptr));
	this->_player.reset();
	this->initMap();
	this->_score = 0;
	this->_gameStatus = true;
	for (const auto &pos : this->_enemyPos) {
		this->_enemies.emplace_back(Arcade::SolarFox::Enemy(pos.second,
			pos.first));
	}
	return true;
}

bool Arcade::SolarFoxGame::stop()
{
	this->_map.clear();
	this->_beams.clear();
	this->_enemies.clear();
	return true;
}

void Arcade::SolarFoxGame::refreshGameOver(IGraphicLib &graphicLib)
{
	auto screenSize = graphicLib.getScreenSize();
	auto black = Arcade::Color(0, 0, 0, 255);
	Arcade::PixelBox box(screenSize, Arcade::Vect<size_t>(0, 0), black);
	Arcade::Vect<size_t> size(screenSize / this->_mapSize * 3);
	graphicLib.drawPixelBox(box);
	Arcade::TextBox text("Game Over", Vect<size_t>(screenSize.getX() / 3,
		screenSize.getY() / 2), size.getY(),
		Color(200, 200, 200, 255), black);
	graphicLib.drawText(text);
	text.setValue("Score : " + std::to_string(this->_score));
	text.setY(text.getY() + size.getY() * 1.5);
	graphicLib.drawText(text);
}

void Arcade::SolarFoxGame::refresh(IGraphicLib &graphicLib)
{
	if (this->_gameStatus)
		this->refreshGame(graphicLib);
	else
		this->refreshGameOver(graphicLib);
}

void Arcade::SolarFoxGame::displayTemp(Arcade::PixelBox &box, Arcade::Vect<size_t> &rectSize)
{
	auto posPlayer = this->_player.getPos();
	box.putRect(rectSize * Arcade::Vect<size_t>(posPlayer.getX(),
		posPlayer.getY()), rectSize, this->_colors.at('2'));
	auto &color = this->_colors.at('5');
	for (const auto &beam : this->_beams)
		box.putRect(rectSize * beam.getPos(), rectSize, color);
	auto &color2 = this->_colors.at('4');
	for (const auto &enemy : this->_enemies)
		box.putRect(rectSize * enemy.getPos(), rectSize, color2);
}

void Arcade::SolarFoxGame::refreshGame(IGraphicLib &graphicLib)
{
	auto screenSize = graphicLib.getScreenSize();
	auto black = Arcade::Color(0, 0, 0, 255);
	Arcade::PixelBox box(screenSize, Arcade::Vect<size_t>(0, 0), black);
	Arcade::Vect<size_t> size(screenSize / this->_mapSize);
	auto x = this->_mapSize.getX();
	auto y = this->_mapSize.getY();
	for (size_t i = 0; i < y; i++)
		for (size_t j = 0; j < x; j++) {
			auto color = this->_colors.at(this->_map[i][j]);
			if (color != black)
				box.putRect(size * Arcade::Vect<size_t>(j, i),
					size, color);
		}
	this->displayTemp(box, size);
	graphicLib.drawPixelBox(box);
	Arcade::TextBox score("Score : " + std::to_string(this->_score),
		Vect<size_t>(screenSize.getX() / 20, size.getY()),
		size.getY(), Color(200, 200, 200, 255), black);
	graphicLib.drawText(score);
}

bool Arcade::SolarFoxGame::applyEvent(Keys key)
{
	bool ret(false);
	if (this->_keys.count(key))
		ret = this->_keys.at(key)(this);
	return ret;
}

bool Arcade::SolarFoxGame::checkPlayerStatus() const
{
	auto pos = this->_player.getPos();
	for (const auto &it : this->_beams)
		if (it.getOrigin() == Arcade::SolarFox::ENEMY &&
			pos == it.getPos())
			return false;
	auto chara = this->_map[pos.getY()][pos.getX()];
	return (chara == '0' || chara == '3');
}

void Arcade::SolarFoxGame::checkBeams()
{
	for (const auto &beam : this->_beams) {
		if (beam.getOrigin() == Arcade::SolarFox::PLAYER) {
			std::vector<int> toErase;
			auto pos = beam.getPos();
			for (size_t i = 0; i < this->_beams.size(); i++) {
				if (this->_beams[i].getOrigin() ==
					Arcade::SolarFox::PLAYER)
					continue;
				auto tmp = this->_beams[i].getPos();
				if (pos.getX() == tmp.getX() &&
					pos.getY() == tmp.getY()) {
					toErase.push_back(i);
					this->_score += 25;
				}
			}
			for (const auto &it : toErase)
				this->_beams.erase(this->_beams.begin() + it);
		}
	}
}

void Arcade::SolarFoxGame::updateScore()
{
	std::vector<int> toErase;
	for (unsigned int i = 0; this->_beams.size() > i; i++) {
		auto &beam = this->_beams[i];
		const auto &pos = beam.getPos();
		auto &chara = this->_map[pos.getY()][pos.getX()];
		if (chara == '3' &&
			beam.getOrigin() == Arcade::SolarFox::PLAYER) {
			chara = '0';
			this->_score += 10;
			toErase.emplace_back(i);
		} else if (beam.getTurns() > beam.getMaxTurns())
			toErase.emplace_back(i);
		checkBeams();
	}
	for (auto &pos : toErase)
		this->_beams.erase(this->_beams.begin() + pos);
}

static Arcade::SolarFox::Direction getDir(Arcade::Vect<size_t> pos)
{
	Arcade::SolarFox::Direction ret(Arcade::SolarFox::UP);
	if (pos.getX() == 0)
		ret = Arcade::SolarFox::RIGHT;
	else if (pos.getY() == 0)
		ret = Arcade::SolarFox::DOWN;
	else if (pos.getX() == Arcade::SolarFoxGame::_mapSize.getX() - 1)
		ret = Arcade::SolarFox::LEFT;
	return ret;
}

void Arcade::SolarFoxGame::checkVictory()
{
	if (!this->_gameStatus)
		return;
	for (const auto &line : this->_map)
		for (const auto &chara : line)
			if (chara == '3')
				return;
	this->_gameStatus = false;
}

bool Arcade::SolarFoxGame::update()
{
	if (!(this->_player.isAlive() && this->_gameStatus))
		return false;
	for (auto &it : this->_beams)
		it.moveForward();
	for (auto &enemy : this->_enemies) {
		enemy.move();
		if (enemy.getMoveCount() / 10 > enemy.getShootCount()) {
			enemy.incShootCount(1);
			auto x = enemy.getPos().getX();
			auto y = enemy.getPos().getY();
			this->_beams.emplace_back(Arcade::SolarFox::Beam(x,
				y, getDir(enemy.getPos()),
				Arcade::SolarFox::ENEMY));
		}
	}
	this->updateScore();
	this->_player.moveForward();
	this->_gameStatus = this->checkPlayerStatus();
	this->checkVictory();
	return this->_gameStatus;
}

bool Arcade::SolarFoxGame::handleKeyLeft()
{
	return this->_player.rotate(Arcade::SolarFox::LEFT);
}

bool Arcade::SolarFoxGame::handleKeyRight()
{
	return this->_player.rotate(Arcade::SolarFox::RIGHT);
}

bool Arcade::SolarFoxGame::handleKeyShoot()
{
	auto pos = this->_player.getPos();
	this->_beams.emplace_back(Arcade::SolarFox::Beam(pos.getX(),
		pos.getY(), this->_player.getDirection(),
		Arcade::SolarFox::PLAYER));
	return false;
}
