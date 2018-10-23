//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Player.cpp
//

#include "Player.hpp"

const std::map<Arcade::SolarFox::Direction, std::pair<int, int>> Arcade::SolarFox::Player::_moves = {
	{Arcade::SolarFox::Direction::UP, std::pair<int, int>(0, -1)},
	{Arcade::SolarFox::Direction::DOWN, std::pair<int, int>(0, 1)},
	{Arcade::SolarFox::Direction::LEFT, std::pair<int, int>(-1, 0)},
	{Arcade::SolarFox::Direction::RIGHT, std::pair<int, int>(1, 0)}
};

const int Arcade::SolarFox::Player::_moveRatio = 3;

Arcade::SolarFox::Player::Player()
	: _status(true), _pos(0, 0), _direction(UP), _lastTime(clock()), _moveCount(0)
{
}

void Arcade::SolarFox::Player::reset()
{
	this->_status = true;
	this->_pos = Arcade::Vect<size_t>(0, 0);
	this->_direction = UP;
	this->_lastTime = clock();
	this->_moveCount = 0;
}

Arcade::SolarFox::Direction Arcade::SolarFox::Player::getDirection() const
{
	return this->_direction;
}

Arcade::Vect<size_t> Arcade::SolarFox::Player::getPos() const
{
	return this->_pos;
}

void Arcade::SolarFox::Player::setPos(Arcade::Vect<size_t> pos)
{
	this->_pos = pos;
}

void Arcade::SolarFox::Player::moveForward()
{
	auto sec = (clock() - this->_lastTime) / (CLOCKS_PER_SEC / 6);
	if (this->_moveCount >  sec / this->_moveRatio)
		return;
	auto x = this->_pos.getX() + this->_moves.at(this->_direction).first;
	auto y = this->_pos.getY() + this->_moves.at(this->_direction).second;
	this->_pos.setXY(x, y);
	this->_moveCount++;
}

void Arcade::SolarFox::Player::rotateRight()
{
	switch (this->_direction) {
	case UP:
		this->_direction = RIGHT;
		break;
	case RIGHT:
		this->_direction = DOWN;
		break;
	case LEFT:
		this->_direction = UP;
		break;
	case DOWN:
		this->_direction = LEFT;
	}
}

void Arcade::SolarFox::Player::rotateLeft()
{
	switch (this->_direction) {
	case UP:
		this->_direction = LEFT;
		break;
	case RIGHT:
		this->_direction = UP;
		break;
	case LEFT:
		this->_direction = DOWN;
		break;
	case DOWN:
		this->_direction = RIGHT;
	}
}

bool Arcade::SolarFox::Player::rotate(Direction dir)
{
	if (dir == LEFT)
		this->rotateLeft();
	else  if (dir == RIGHT)
		this->rotateRight();
	return true;
}

bool Arcade::SolarFox::Player::isAlive() const
{
	return this->_status;
}

void Arcade::SolarFox::Player::kill()
{
	this->_status = false;
}