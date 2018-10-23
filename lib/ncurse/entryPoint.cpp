/*
** EPITECH Project, 2018
** cpp_arcade
** File description:
** entryPoint.cpp
*/

#include "NCursesGraphicLib.hpp"

Arcade::NCursesGraphicLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::NCursesGraphicLib;
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