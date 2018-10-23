//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Beam.cpp
//

#include "Beam.hpp"

const std::unordered_map<Arcade::SolarFox::Origin, unsigned int> Arcade::SolarFox::Beam::_maxTurns = {
	{PLAYER, 4},
	{ENEMY, 30}
};

const std::unordered_map<Arcade::SolarFox::Origin, float> Arcade::SolarFox::Beam::_moveRatio = {
	{PLAYER, 0.5f},
	{ENEMY, Arcade::SolarFox::Player::_moveRatio + 0.5f}
};

Arcade::SolarFox::Beam::Beam(int x, int y, Arcade::SolarFox::Direction dir, Origin origin)
	: _pos(x, y), _dir(dir), _turns(0), _origin(origin), _lastTime(clock())
{
}

Arcade::SolarFox::Origin Arcade::SolarFox::Beam::getOrigin() const
{
	return this->_origin;
}

Arcade::SolarFox::Direction Arcade::SolarFox::Beam::getDirection() const
{
	return this->_dir;
}

Arcade::Vect<size_t> Arcade::SolarFox::Beam::getPos() const
{
	return this->_pos;
}

unsigned int Arcade::SolarFox::Beam::getTurns() const
{
	return this->_turns;
}

unsigned int Arcade::SolarFox::Beam::getMaxTurns() const
{
	return this->_maxTurns.at(this->_origin);
}

void Arcade::SolarFox::Beam::moveForward()
{
	auto sec = (clock() - this->_lastTime) / (CLOCKS_PER_SEC / 6);
	if (this->_turns >  sec / this->_moveRatio.at(this->_origin))
		return;
	auto x = this->_pos.getX() + Arcade::SolarFox::Player::_moves.at(this->_dir).first;
	auto y = this->_pos.getY() + Arcade::SolarFox::Player::_moves.at(this->_dir).second;
	this->_pos.setXY(x, y);
	this->_turns++;
}