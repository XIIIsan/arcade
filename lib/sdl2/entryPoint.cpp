/*
** EPITECH Project, 2018
** cpp_arcade
** File description:
** entryPoint.cpp
*/

#include "SDL2GraphicLib.hpp"

Arcade::SDL2GraphicLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::SDL2GraphicLib;
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