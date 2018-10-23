//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Ncurses
//

#pragma once

#include <string>
#include <ncurses.h>
#include <map>
#include <vector>
#include "Graphic/IGraphicLib.hpp"
#include "Utils/Vect.hpp"
#include "Utils/PixelBox.hpp"
#include "Utils/TextBox.hpp"
#include "Utils/Keys.hpp"

namespace Arcade {
	class NCursesGraphicLib : public IGraphicLib {
	public:
		NCursesGraphicLib();
		
		~NCursesGraphicLib();

		/* Get the name of the library */
		std::string getName() const;

		/* Window handling */
		// Main loop condition
		bool isOpen() const;
		
		// Closes the window => stop loop (go menu)
		void closeRenderer();
		
		// Opens the window => start loop
		void openRenderer();

		// Clears the screen
		void clearWindow();
		
		// Displays the buffered frame to the screen
		void refreshWindow();
		
		/* Rendering functions */
		// Draws a PixelBox or the sprite if supported
		void drawPixelBox(Arcade::PixelBox &);
		
		// Draws a TextBox
		void drawText(Arcade::TextBox &);
		
		/* Events handling */
		// Gets the last saved event (used in render loop)
		Arcade::Keys getLastEvent();
		
		// Saves the event in the Graphics library
		bool pollEvents();
		
		// Deletes the last event
		void clearEvents();
		
		/* Context Info */
		// get the X and Y max of the windows
		Vect<size_t> getScreenSize() const;
		
		// get the Y max of the windows
		int getMaxY() const;
		
		// get the X max of the windows
		int getMaxX() const;

		// inits curses color
		int getColor(Arcade::Color &color);
 		int getColorPair(Arcade::Color &c1, Arcade::Color &c2);
	private:
		std::string _name;
		bool _isOpen;	
		WINDOW	*win;
		static const std::map<unsigned char, Arcade::Keys> _keys;
		unsigned char _stock;
		std::vector<Arcade::Keys> _event;
		std::vector<Arcade::Color> _colors;
		std::vector<std::pair<int, int>> _pair;
	};
};
