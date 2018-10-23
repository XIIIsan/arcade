//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Beam.hpp
//

#pragma once

#include <unordered_map>
#include "Player.hpp"

namespace Arcade {
	namespace SolarFox {
		enum Origin {
			PLAYER,
			ENEMY
		};

		class Beam {
		public:
			Beam(int x, int y, Arcade::SolarFox::Direction dir,
				Origin = ENEMY);
			~Beam() = default;

			Arcade::Vect<size_t> getPos() const;
			Arcade::SolarFox::Direction getDirection() const;
			unsigned int getTurns() const;
			unsigned int getMaxTurns() const;
			Arcade::SolarFox::Origin getOrigin() const;

			void moveForward();
		private:
			Arcade::Vect<size_t> _pos;
			Arcade::SolarFox::Direction _dir;
			unsigned int _turns;
			Arcade::SolarFox::Origin _origin;
			clock_t _lastTime;
			static const std::unordered_map<Arcade::SolarFox::Origin, unsigned int> _maxTurns;
			static const std::unordered_map<Arcade::SolarFox::Origin, float> _moveRatio;
		};
	}
}


