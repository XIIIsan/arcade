//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Enemy.cpp
//

#include "Enemy.hpp"
#include "SolarFoxGame.hpp"

Arcade::SolarFox::Enemy::Enemy(Arcade::Vect<size_t> pos, Arcade::SolarFox::Direction dir)
	: _pos(pos), _dir(dir), _moveCount(0), _shootCount(0), _lastTime(clock())
{
}

Arcade::Vect<size_t> Arcade::SolarFox::Enemy::getPos() const
{
	return this->_pos;
}

void Arcade::SolarFox::Enemy::setPos(Arcade::Vect<size_t> pos)
{
	this->_pos = pos;
}

Arcade::SolarFox::Direction Arcade::SolarFox::Enemy::getDirection() const
{
	return this->_dir;
}

void Arcade::SolarFox::Enemy::setDirection(Arcade::SolarFox::Direction dir)
{
	this->_dir = dir;
}

unsigned int Arcade::SolarFox::Enemy::getMoveCount() const
{
	return this->_moveCount;
}

unsigned int Arcade::SolarFox::Enemy::getShootCount() const
{
	return this->_shootCount;
}

void Arcade::SolarFox::Enemy::incShootCount(unsigned int sup)
{
	this->_shootCount += sup;
}

void Arcade::SolarFox::Enemy::move()
{
	auto sec = (clock() - this->_lastTime) / (CLOCKS_PER_SEC / 6);
	if (this->_moveCount >  sec / Arcade::SolarFox::Player::_moveRatio)
		return;
	auto x = this->_pos.getX() + Arcade::SolarFox::Player::_moves.at(this->_dir).first;
	auto y = this->_pos.getY() + Arcade::SolarFox::Player::_moves.at(this->_dir).second;
	this->_pos.setXY(x, y);
	this->_moveCount++;
	if (this->_dir == UP && this->_pos.getY() == 0)
		this->_dir = DOWN;
	else if (this->_dir == DOWN &&
		this->_pos.getY() == Arcade::SolarFoxGame::_mapSize.getY())
		this->_dir = UP;
	else if (this->_dir == LEFT && this->_pos.getX() == 0)
		this->_dir = RIGHT;
	else if (this->_dir == RIGHT &&
		this->_pos.getX() == Arcade::SolarFoxGame::_mapSize.getX())
		this->_dir = LEFT;
}