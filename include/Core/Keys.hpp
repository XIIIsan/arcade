//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Keys.hpp
//

#pragma once

#include <cstdlib>
#include "Utils/Keys.hpp"

namespace std {

	template <>
	struct hash<Arcade::Keys>
	{
		std::size_t operator()(const Arcade::Keys &k) const
		{
			return ((hash<int>()(k)));
		}
	};

}