//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// ACharacter.hpp
//

#pragma once

#include <cstdlib>
#include <Utils/Vect.hpp>
#include <Utils/Color.hpp>

namespace Arcade {
	namespace Pacman {
		class ACharacter {
		public:
			ACharacter(Color color = {20, 120, 20}, Vect<size_t> pos = {0, 0});
			~ACharacter() = default;

			Vect<size_t> getPos() const;
			void setPos(Vect<size_t>);
			Color getColor() const;
		private:
			Color _color;
			Arcade::Vect<size_t> _pos;
		};
	}
}


