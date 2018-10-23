//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Enemy.hpp
//

#pragma once

#include "Player.hpp"

namespace Arcade {
	namespace SolarFox {
		class Enemy {
		public:
			Enemy(Arcade::Vect<size_t>, Arcade::SolarFox::Direction);
			~Enemy() = default;

			void setPos(Arcade::Vect<size_t>);
			Arcade::Vect<size_t> getPos() const;
			void setDirection(Arcade::SolarFox::Direction);
			Arcade::SolarFox::Direction getDirection() const;
			unsigned int getMoveCount() const;
			unsigned int getShootCount() const;
			void incShootCount(unsigned int);

			void move();
		private:
			Arcade::Vect<size_t> _pos;
			Arcade::SolarFox::Direction _dir;
			unsigned int _moveCount;
			unsigned int _shootCount;
			clock_t _lastTime;
		};
	}
}


