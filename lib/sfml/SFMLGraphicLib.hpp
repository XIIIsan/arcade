/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Utils/Vect.hpp"
#include "Utils/PixelBox.hpp"
#include "Utils/TextBox.hpp"
#include "Utils/Keys.hpp"
#include "Graphic/IGraphicLib.hpp"

namespace Arcade {
	class SFMLGraphicLib : public IGraphicLib {
	public:
		SFMLGraphicLib();
		~SFMLGraphicLib();

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
		Arcade::Vect<size_t> getScreenSize() const;

		// get the Y max of the windows
		int getMaxY() const;

		// get the X max of the windows
		int getMaxX() const;

	private:
		std::string _libName;
		sf::RenderWindow *_window;
		sf::Event _event;
		sf::Texture _texture;
		sf::Sprite _sprite;
		sf::Font _font;
		sf::Text _text;
		std::vector<Arcade::Keys> _keyCode;
		Arcade::Vect<size_t> _screenSize = Arcade::Vect<size_t>(1920, 1080);
		static std::map<sf::Keyboard::Key, Arcade::Keys> _keys;
	};
};
