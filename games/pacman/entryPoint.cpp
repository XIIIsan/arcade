/*
** EPITECH Project, 2018
** cpp_arcade
** File description:
** entryPoint.cpp
*/

#include "PacmanGame.hpp"

Arcade::PacmanGame *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::PacmanGame;
}

__attribute__((destructor))
void out()
{
	delete ret;
}

extern "C" Arcade::IGameLib *entryPoint()
{
	return ret;
}
