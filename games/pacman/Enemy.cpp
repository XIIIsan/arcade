//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Ennemy.cpp
//

#include "Enemy.hpp"

Arcade::Pacman::Enemy::Enemy(Arcade::Color color, Arcade::Vect<size_t> pos)
 : ACharacter(color, pos),
   _alive(true)
{}

bool Arcade::Pacman::Enemy::isAlive() const
{
	return this->_alive;
}

void Arcade::Pacman::Enemy::kill()
{
	this->_alive = false;
}