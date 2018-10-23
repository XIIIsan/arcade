//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// ACharacter.cpp
//

#include "ACharacter.hpp"

Arcade::Pacman::ACharacter::ACharacter(Arcade::Color color, Arcade::Vect<size_t> pos)
	: _color(color), _pos(pos)
{
}

Arcade::Vect<size_t> Arcade::Pacman::ACharacter::getPos() const
{
	return this->_pos;
}

void Arcade::Pacman::ACharacter::setPos(Arcade::Vect<size_t> pos)
{
	this->_pos = pos;
}

Arcade::Color Arcade::Pacman::ACharacter::getColor() const
{
	return this->_color;
}