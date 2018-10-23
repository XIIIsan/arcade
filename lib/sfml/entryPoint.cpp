/*
** EPITECH Project, 2018
** cpp_arcade
** File description:
** entryPoint.cpp
*/

#include "SFMLGraphicLib.hpp"

Arcade::SFMLGraphicLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::SFMLGraphicLib;
}

__attribute__((destructor))
void out()
{
	delete ret;
}

extern "C" Arcade::IGraphicLib *entryPoint()
{
	return ret;
}