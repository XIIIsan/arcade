//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Ennemy.hpp
//

#pragma once

#include "ACharacter.hpp"

namespace Arcade {
	namespace Pacman {
		class Enemy : public ACharacter {
		public:
			Enemy(Color color = {20, 120, 20}, Vect<size_t> pos = {0, 0});
			bool isAlive() const;
			void kill();
		private:
			bool _alive;
		};
	}
}


