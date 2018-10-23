//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Menu.hpp
//

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <fstream>
#include "Graphic/IGraphicLib.hpp"
#include "Core/Keys.hpp"

namespace Arcade {
	class Menu;
	using MenuMap = std::unordered_map<Arcade::Keys, std::function<bool(Arcade::Menu*)>>;

	class Menu {
	public:
		enum Modes {
			MAIN,
			GAMES,
			GAME,
			QUIT,
			LIBS,
			OPTIONS,
		};

		Menu(std::vector<std::string> &);
		~Menu() = default;

		bool handleKeyUp();
		bool handleKeyDown();
		bool handleKeyEscape();
		bool handleKeyEnter();

		std::vector<std::string> *getCurrentList() const;
		Arcade::Menu::Modes getMode() const;
		std::string getToLoad() const;
		void clearToLoad();

		std::string getCurrentLink() const;
		std::fstream getScoreFile(std::string) const;
		std::vector<std::string> getScores() const;

		void displayModeSpecs(Arcade::IGraphicLib &);
		void clearBackGround(Arcade::IGraphicLib &);
		void displayLinks(Arcade::IGraphicLib &);
		// returns true if keys is handled
		bool handleKeys(Arcade::Keys);
	private:
		std::vector<std::string> _mainMenu;
		std::vector<std::vector<std::string>*> _links;
		int _focus;
		Arcade::Menu::Modes _mode;
		Arcade::TextBox _textBox;
		std::string _toLoad;
		static const Arcade::MenuMap _keys;
		static const int _maxLinks;
		static const std::vector<std::string> _help;
	};
}

