//
// EPITECH PROJECT, 2018
// arcade
// File description:
// main.cpp
//

#include "Core/Core.hpp"

int main(int ac, char **av)
{
	Arcade::Core core;
	if (!core.loadArgs(ac, av))
		return 84;
	core.run();
	return 0;
}