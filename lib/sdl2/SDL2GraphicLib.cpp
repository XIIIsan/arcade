//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Sdl2 file
//

#include <iostream>
#include <algorithm>
#include <SDL2/SDL_ttf.h>
#include "SDL2GraphicLib.hpp"
#include "Utils/TextBox.hpp"

const std::unordered_map<SDL_Keycode, Arcade::Keys> Arcade::SDL2GraphicLib::_keys = {
	{SDLK_a, Arcade::A},
	{SDLK_b, Arcade::B},
	{SDLK_c, Arcade::C},
	{SDLK_d, Arcade::D},
	{SDLK_e, Arcade::E},
	{SDLK_f, Arcade::F},
	{SDLK_g, Arcade::G},
	{SDLK_h, Arcade::H},
	{SDLK_i, Arcade::I},
	{SDLK_j, Arcade::J},
	{SDLK_k, Arcade::K},
	{SDLK_l, Arcade::L},
	{SDLK_m, Arcade::M},
	{SDLK_n, Arcade::N},
	{SDLK_o, Arcade::O},
	{SDLK_p, Arcade::P},
	{SDLK_q, Arcade::Q},
	{SDLK_r, Arcade::R},
	{SDLK_s, Arcade::S},
	{SDLK_t, Arcade::T},
	{SDLK_u, Arcade::U},
	{SDLK_v, Arcade::V},
	{SDLK_w, Arcade::W},
	{SDLK_x, Arcade::X},
	{SDLK_y, Arcade::Y},
	{SDLK_z, Arcade::Z},
	{SDLK_LEFT, Arcade::LEFT},
	{SDLK_RIGHT, Arcade::RIGHT},
	{SDLK_UP, Arcade::UP},
	{SDLK_DOWN, Arcade::DOWN},
	{SDLK_RETURN, Arcade::ENTER},
	{SDLK_SPACE, Arcade::SPACE},
	{SDLK_DELETE, Arcade::DELETE},
	{SDLK_BACKSPACE, Arcade::BACKSPACE},
	{SDLK_TAB, Arcade::TAB},
	{SDLK_ESCAPE, Arcade::ESC}
};

Arcade::SDL2GraphicLib::SDL2GraphicLib()
	: _name("SDL2")
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
		std::cerr << "Une erreur est survenue." << std::endl;
}

Arcade::SDL2GraphicLib::~SDL2GraphicLib()
{
	SDL_Quit();
	TTF_Quit();
}

std::string Arcade::SDL2GraphicLib::getName() const
{
	return _name;
}

bool Arcade::SDL2GraphicLib::isOpen() const
{
	return !(this->_event.type == SDL_WINDOWEVENT_CLOSE ||
		 this->_event.type == SDL_QUIT);
}

void Arcade::SDL2GraphicLib::closeRenderer()
{
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
	this->clearEvents();
	this->_event.type = SDL_QUIT;
	SDL_DestroyTexture(this->_texture);
}

void Arcade::SDL2GraphicLib::openRenderer()
{
	int width = 1600;
	int height = 900;
	memset(&this->_event, 0, sizeof(this->_event));
	this->_window = SDL_CreateWindow("SDL2",
					 SDL_WINDOWPOS_CENTERED,
					 SDL_WINDOWPOS_CENTERED,
					 width, height,
					 SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	this->_renderer = SDL_CreateRenderer(this->_window, -1, 0);
	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
	this->_texture = SDL_CreateTexture(this->_renderer,
					   SDL_PIXELFORMAT_ABGR8888,
					   SDL_TEXTUREACCESS_TARGET,
					   width, height);
}

void Arcade::SDL2GraphicLib::clearWindow()
{
	SDL_RenderClear(this->_renderer);
}

void Arcade::SDL2GraphicLib::refreshWindow()
{
	SDL_RenderPresent(this->_renderer);
}

void Arcade::SDL2GraphicLib::drawPixelBox(Arcade::PixelBox &toDisplay)
{
	auto &arr = toDisplay.getPixelArray()[0];
	SDL_Rect rect = {
		static_cast<int>(toDisplay.getX()),
		static_cast<int>(toDisplay.getY()),
		static_cast<int>(toDisplay.getWidth()),
		static_cast<int>(toDisplay.getHeight())
	};
	SDL_UpdateTexture(this->_texture, &rect, &arr, rect.w * 4);
	SDL_RenderCopy(this->_renderer, this->_texture, &rect, &rect);
}

void Arcade::SDL2GraphicLib::drawText(Arcade::TextBox &text)
{
	const auto &tmp = (unsigned char *) text.getColor();
	SDL_Color color = {tmp[0], tmp[1], tmp[2], tmp[3]};
	TTF_Font *font = TTF_OpenFont("resources/Symtext.ttf",
				      static_cast<int>(text.getFontSize()));
	if (font == nullptr)
		throw std::bad_alloc();
	SDL_Surface *toDisp = TTF_RenderText_Blended(font,
						     text.getValue().c_str(),
						     color);
	auto texture = SDL_CreateTextureFromSurface(this->_renderer, toDisp);
	SDL_Rect rect = {(int) text.getX(), (int) text.getY(),
			 toDisp->w, toDisp->h};
	SDL_RenderCopy(this->_renderer, texture, nullptr, &rect);
	SDL_FreeSurface(toDisp);
	TTF_CloseFont(font);
}

bool Arcade::SDL2GraphicLib::pollEvents()
{
	if (this->_event.type != SDL_QUIT)
		SDL_PollEvent(&this->_event);
	return !(this->_event.type == SDL_WINDOWEVENT_CLOSE ||
		 this->_event.type == SDL_QUIT);
}

Arcade::Keys Arcade::SDL2GraphicLib::getLastEvent()
{
	Arcade::Keys ret(Arcade::NONE);
	if (this->_event.type == SDL_KEYUP) {
		auto key = this->_event.key.keysym.sym;
		if (this->_keys.count(key) > 0) {
			ret = this->_keys.at(key);
		}
		this->clearEvents();
	}
	return ret;
}

void Arcade::SDL2GraphicLib::clearEvents()
{
	memset(&this->_event, 0, sizeof(this->_event));
}

Arcade::Vect<size_t> Arcade::SDL2GraphicLib::getScreenSize() const
{
	int x;
	int y;
	SDL_GetWindowSize(this->_window, &x, &y);
	return Arcade::Vect<size_t>(x, y);
}

int Arcade::SDL2GraphicLib::getMaxY() const
{
	int w;
	int h;
	SDL_GetWindowSize(this->_window, &w, &h);
	return h;
}

int Arcade::SDL2GraphicLib::getMaxX() const
{
	int w;
	int h;
	SDL_GetWindowSize(this->_window, &w, &h);
	return w;
}
