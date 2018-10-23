//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Player.hpp
//

#pragma once

#include <Utils/Vect.hpp>
#include <cstdio>
#include <ctime>
#include <string>
#include <vector>
#include <map>

namespace Arcade {
	namespace SolarFox {
		enum Direction {
			LEFT,
			UP,
			RIGHT,
			DOWN
		};
		class Player {
		public:
			Player();
			~Player() = default;

			Arcade::SolarFox::Direction getDirection() const;
			Arcade::Vect<size_t> getPos() const;

			void setPos(Arcade::Vect<size_t>);

			bool isAlive() const;
			void kill();
			void reset();

			void rotateRight();
			void rotateLeft();
			bool rotate(Direction);
			void moveForward();

			static const int _moveRatio;
			static const std::map<Direction, std::pair<int, int>> _moves;
		private:
			bool _status;
			Arcade::Vect<size_t> _pos;
			Arcade::SolarFox::Direction _direction;
			clock_t _lastTime;
			int _moveCount;
		};
	}
}


