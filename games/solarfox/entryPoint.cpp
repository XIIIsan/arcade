/*
** EPITECH Project, 2018
** cpp_arcade
** File description:
** entryPoint.cpp
*/

#include "SolarFoxGame.hpp"

Arcade::SolarFoxGame *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::SolarFoxGame;
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