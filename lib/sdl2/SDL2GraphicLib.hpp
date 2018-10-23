//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Sdl2 header
//

#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <unordered_map>
#include "Graphic/IGraphicLib.hpp"


namespace Arcade {
	class SDL2GraphicLib : public Arcade::IGraphicLib {
	public:
		SDL2GraphicLib();
		~SDL2GraphicLib();

		/* Get the name of the library */
		std::string getName() const override;

		/* Window handling */
		// Main loop condition
		bool isOpen() const override;

		// Closes the window => stop loop (go menu)
		void closeRenderer() override;

		// Opens the window => start loop
		void openRenderer() override;

		// Clears the screen
		void clearWindow() override;

		// Displays the buffered frame to the screen
		void refreshWindow() override;

		/* Rendering functions */
		// Draws a PixelBox or the sprite if supported
		void drawPixelBox(PixelBox &) override;

		// Draws a TextBox
		void drawText(TextBox &) override;

		/* EVENT HANDLING */
		/* */
		/* This part can seem complicated but the implementation is quite simple. */
		/* */
		/* pollEvent() fetches the events from the user and saves it */
		/* inside an std::vector<Arcade::Keys> or std::list<Arcade::Keys>. */
		/* It returns true if at least one new event was added to the list, false otherwise. */
		/* */
		/* getLastEvent() returns the first event of the list. (using front() and pop_front() methods) */
		/* or Arcade::Keys::NONE if the list is empty. */
		/* */
		/* clearEvents() clears the list (using clear() method). */
		/* */
		bool pollEvents() override;
		Keys getLastEvent() override;
		void clearEvents() override;

		/* Context Info */
		// get the X and Y max of the windows
		Vect<size_t> getScreenSize() const override;

		// get the Y max of the windows
		int getMaxY() const override;

		// get the X max of the windows
		int getMaxX() const override;
	private:
		std::string _name;
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		SDL_Event _event;
		SDL_Texture *_texture;
		static const std::unordered_map<SDL_Keycode, Arcade::Keys> _keys;
	};
};
