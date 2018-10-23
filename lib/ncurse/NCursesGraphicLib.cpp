//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Ncurses
//

#include <string>
#include <sys/ioctl.h>
#include <iostream>
#include <algorithm>
#include <ncurses.h>
#include "NCursesGraphicLib.hpp"

const std::map<unsigned char, Arcade::Keys> Arcade::NCursesGraphicLib::_keys = {
	{'a',                           Arcade::A},
	{'b',                           Arcade::B},
	{'c',                           Arcade::C},
	{'d',                           Arcade::D},
	{'e',                           Arcade::E},
	{'f',                           Arcade::F},
	{'g',                           Arcade::G},
	{'h',                           Arcade::H},
	{'i',                           Arcade::I},
	{'j',                           Arcade::J},
	{'k',                           Arcade::K},
	{'l',                           Arcade::L},
	{'m',                           Arcade::M},
	{'n',                           Arcade::N},
	{'o',                           Arcade::O},
	{'p',                           Arcade::P},
	{'q',                           Arcade::Q},
	{'r',                           Arcade::R},
	{'s',                           Arcade::S},
	{'t',                           Arcade::T},
	{'u',                           Arcade::U},
	{'v',                           Arcade::V},
	{'w',                           Arcade::W},
	{'x',                           Arcade::X},
	{'y',                           Arcade::Y},
	{'z',                           Arcade::Z},
	{(unsigned char) KEY_LEFT,      Arcade::LEFT},
	{(unsigned char) KEY_RIGHT,     Arcade::RIGHT},
	{(unsigned char) KEY_UP,        Arcade::UP},
	{(unsigned char) KEY_DOWN,      Arcade::DOWN},
	{(unsigned char) KEY_BACKSPACE, Arcade::BACKSPACE},
	{(unsigned char) 10,            Arcade::ENTER},
	{27,                            Arcade::ESC}
};

Arcade::NCursesGraphicLib::NCursesGraphicLib()
	:
	_name("ncurse"),
	_isOpen(0)
{}

Arcade::NCursesGraphicLib::~NCursesGraphicLib()
{}

std::string Arcade::NCursesGraphicLib::getName() const
{
	return _name;
}

// Main loop condition
bool Arcade::NCursesGraphicLib::isOpen() const
{
	return _isOpen;
}

// Closes the window => stop loop (go menu)
void Arcade::NCursesGraphicLib::closeRenderer()
{
	_isOpen = 0;
	endwin();
//	return ;
}

// Opens the window => start loop
void Arcade::NCursesGraphicLib::openRenderer()
{
	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	timeout(1);
	noecho();
//	win = subwin(stdscr, 50, 50, 2, 2);
	curs_set(0);
//	box(win, 0, 0);
	_isOpen = 1;
	start_color();
}

// Clears the screen
void Arcade::NCursesGraphicLib::clearWindow()
{
	clear();
}

// Displays the buffered frame to the screen
void Arcade::NCursesGraphicLib::refreshWindow()
{
	refresh();
//	wrefresh(win);
}

/* Rendering functions */
// Draws a PixelBox or the sprite if supported
void Arcade::NCursesGraphicLib::drawPixelBox(Arcade::PixelBox &pyxie)
{
	auto tab = pyxie.getPixelArray();
	auto height = pyxie.getHeight();
	auto width = pyxie.getWidth();
	Arcade::Color c1(0, 0, 0, 255);
	for (size_t y = pyxie.getY(); y < height; y++)
		for (size_t x = pyxie.getX(); x < width; x++) {
			auto c2 = tab[y * height + x];
			auto color = this->getColorPair(c1, c2);
			attron(COLOR_PAIR(color) | A_BOLD);
			mvprintw(y, x, "%s", " ");
			attroff(COLOR_PAIR(color) | A_BOLD);
		}
}

// Draws a TextBox
void Arcade::NCursesGraphicLib::drawText(Arcade::TextBox &box)
{
	auto c1 = box.getColor();
	auto c2 = box.getBackgroundColor();
	auto color = this->getColorPair(c1, c2);
	attron(COLOR_PAIR(color) | A_BOLD);
	mvprintw(box.getY(), box.getX(), box.getValue().c_str());
	attroff(COLOR_PAIR(color) | A_BOLD);
}

/* Events handling */
// Gets the last saved event (used in render loop)
Arcade::Keys Arcade::NCursesGraphicLib::getLastEvent()
{
	/*std::map<unsigned char,Arcade::Keys>::iterator it;

	it = _keys.find(this->_stock);
	if (it->second)
	return (it->second);*/
	if (!_event.empty()) {
		Arcade::Keys front = _event[0];
		_event.erase(_event.begin());
		return front;
	}
	return Arcade::Keys::NONE;
}

// Saves the event in the Graphics library
bool Arcade::NCursesGraphicLib::pollEvents()
{
	auto value = getch();
	if (_keys.count(value) > 0) {
		std::cerr << (int) value << std::endl;
		_event.push_back(_keys.at(value));
	}
	return (true);
}

void Arcade::NCursesGraphicLib::clearEvents()
{
	_event.clear();
//	clear();
}
//Context Info
// get the X and Y max of the windows
Arcade::Vect<size_t> Arcade::NCursesGraphicLib::getScreenSize() const
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	return {w.ws_col, w.ws_row};
}

// get the Y max of the windows
int Arcade::NCursesGraphicLib::getMaxY() const
{
//	return _screenSize.getY();
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	return w.ws_row;

}

// get the X max of the windows
int Arcade::NCursesGraphicLib::getMaxX() const
{
//	return _screenSize.getX();
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	return w.ws_col;
}

int Arcade::NCursesGraphicLib::getColor(Arcade::Color &color)
{
	auto pos = static_cast<int>(this->_colors.size());
	auto it = std::find(this->_colors.begin(), this->_colors.end(), color);
	if (it == this->_colors.end()) {
		init_color(static_cast<short>(pos + 1),
			   static_cast<short>(color.getRed() * 1000 / 255),
			   static_cast<short>(color.getGreen() * 1000 / 255),
			   static_cast<short>(color.getBlue () * 1000 / 255));
		this->_colors.push_back(color);
	} else
		pos = static_cast<int>(it - this->_colors.begin());
	return pos + 1;
}

int Arcade::NCursesGraphicLib::getColorPair(Arcade::Color &c1, Arcade::Color &c2)
{
	auto pos = static_cast<int>(this->_pair.size());
	auto p1 = this->getColor(c1);
	auto p2 = this->getColor(c2);
	auto pair = std::pair<int, int>(p1, p2);
	auto it = std::find(this->_pair.begin(), this->_pair.end(), pair);
	if (it == this->_pair.end()) {
		init_pair(pos + 1, p1, p2);
		this->_pair.push_back(pair);
	} else
		pos = static_cast<int>(it - this->_pair.begin());
	return pos + 1;
}