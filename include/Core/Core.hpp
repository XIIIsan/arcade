//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Core.hpp
//

#pragma once

#include <unordered_map>
#include <functional>
#include "LibsHandler.hpp"
#include "Graphic/IGraphicLib.hpp"
#include "Game/IGameLib.hpp"
#include "Core/Menu.hpp"
#include "Core/Keys.hpp"

namespace Arcade {
	class Core;
	using CoreMap = std::unordered_map<Arcade::Keys, std::function<int(Arcade::Core*)>>;

	class Core {
	public:
		Core();
		~Core() = default;

		bool loadArgs(int ac, char **av);
		void handleKeys(Arcade::Keys);

		// loads left graphical library
		int handleKeyLGrap();
		// loads left game library
		int handleKeyLGame();
		// loads right graphical library
		int handleKeyRGrap();
		// loads right game library
		int handleKeyRGame();
		// does something else
		int handleKeyElse();
		// resets the game
		int handleKeyReset();

		// rendering functions
		void renderMenu();
		void renderGame();

		// returns true if the lib was successfully loaded
		bool changeLib();

		// returns false if the program is closed.
		void saveScore(std::string, int);
		bool checkMenuMode();
		void closeGame();
		void quit();
		void libRun();
		// runs the whole game
		void run();
	private:
		LibsHandler<Arcade::IGraphicLib> _libs;
		LibsHandler<Arcade::IGameLib> _games;
		Arcade::IGraphicLib *_lib;
		Arcade::IGameLib *_game;
		std::string _title;
		std::string _newLib;
		std::string _newGame;
		Arcade::Menu _menu;
		static const CoreMap _keys;
	};
}
