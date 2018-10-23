//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Menu.cpp
//

#include <regex>
#include <iostream>
#include <zconf.h>
#include <sys/stat.h>
#include "Core/Menu.hpp"

const int Arcade::Menu::_maxLinks = 9;

const std::vector<std::string> Arcade::Menu::_help = {
	"A <-> P : Change graphical library",
	"Q <-> M : Change game library",
	"Escape : Quit the game",
	"R : Reset the game"
};

const Arcade::MenuMap Arcade::Menu::_keys = {
	{Arcade::ESC,   &Arcade::Menu::handleKeyEscape},
	{Arcade::UP,    &Arcade::Menu::handleKeyUp},
	{Arcade::DOWN,  &Arcade::Menu::handleKeyDown},
	{Arcade::ENTER, &Arcade::Menu::handleKeyEnter}
};

Arcade::Menu::Menu(std::vector<std::string> &games)
	: _mainMenu(), _links(), _focus(0), _mode(Arcade::Menu::MAIN),
	  _textBox("", Vect<size_t>(0, 0), 0,
		   Arcade::Color(0, 255, 0, 255),
		   Arcade::Color(0, 0, 0, 255)),
	  _toLoad("None")
{
	this->_mainMenu.emplace_back("Games");
	this->_mainMenu.emplace_back("Quit");
	this->_links.emplace_back(&this->_mainMenu);
	this->_links.emplace_back(&games);
}

std::vector<std::string> *Arcade::Menu::getCurrentList() const
{
	if (this->_links.size() < this->_mode)
		return nullptr;
	std::vector<std::string> *ret = this->_links[this->_mode];
	return ret;
}

std::string Arcade::Menu::getToLoad() const
{
	return this->_toLoad;
}

void Arcade::Menu::clearToLoad()
{
	this->_toLoad = "None";
}

bool Arcade::Menu::handleKeyUp()
{
	if (this->_mode == Arcade::Menu::GAME)
		return false;
	auto list = this->getCurrentList();
	if (this->_focus == 0)
		this->_focus = list->size() - 1;
	else
		this->_focus -= 1;
	return true;
}

bool Arcade::Menu::handleKeyDown()
{
	if (this->_mode == Arcade::Menu::GAME)
		return false;
	auto list = this->getCurrentList();
	if (list->begin() + this->_focus + 1 == list->end())
		this->_focus = 0;
	else
		this->_focus += 1;
	return true;
}

bool Arcade::Menu::handleKeyEscape()
{
	bool ret(true);
	switch (this->_mode) {
	case Arcade::Menu::MAIN:
		this->_mode = Arcade::Menu::QUIT;
		break;
	case Arcade::Menu::GAMES:
		this->_mode = Arcade::Menu::MAIN;
		this->_focus = 0;
		break;
	case Arcade::Menu::GAME:
		this->_mode = Arcade::Menu::GAMES;
		break;
	default:
		ret = false;
		break;
	}
	return ret;
}

bool Arcade::Menu::handleKeyEnter()
{
	bool ret(true);
	auto &tmp = this->_links[this->_mode];
	switch (this->_mode) {
	case Arcade::Menu::MAIN:
		if ((*tmp)[this->_focus] == "Games")
			this->_mode = Arcade::Menu::GAMES;
		else if ((*tmp)[this->_focus] == "Quit")
			this->_mode = Arcade::Menu::QUIT;
		break;
	case Arcade::Menu::GAMES:
		if (!tmp->empty()) {
			this->_toLoad = (*tmp)[this->_focus];
			this->_mode = Arcade::Menu::GAME;
		}
		break;
	default:
		ret = false;
		break;
	}
	return ret;
}

bool Arcade::Menu::handleKeys(Arcade::Keys key)
{
	bool ret(false);
	if (this->_keys.count(key) > 0) {
		ret = this->_keys.at(key)(this);
	}
	return ret;
}

static const std::string getName(const std::string &name)
{
	std::regex expr(R"(^(.*/)*lib_arcade_(.*)\.so$)");
	if (std::regex_match(name, expr)) {
		std::smatch matches;
		std::regex_search(name, matches, expr);
		return matches[2];
	}
	return name;
}

void Arcade::Menu::clearBackGround(Arcade::IGraphicLib &lib)
{
	Arcade::PixelBox bg(lib.getScreenSize(),
			    Arcade::Vect<size_t>(0, 0),
			    Arcade::Color(0, 0, 0, 255));
	lib.drawPixelBox(bg);
}

std::string Arcade::Menu::getCurrentLink() const
{
	auto tmp = (this->_mode == Arcade::Menu::GAME ? 1 : 0);
	return getName((*this->_links[this->_mode - tmp])[this->_focus]);
}

std::fstream Arcade::Menu::getScoreFile(std::string file) const
{
	if (access("./scores/", F_OK) == -1) {
		mkdir("./scores", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	return std::fstream("./scores/" + file, std::fstream::out | std::fstream::in);
}

std::vector<std::string> Arcade::Menu::getScores() const
{
	std::vector<std::string> ret;
	ret.emplace_back("Scoreboard");
	auto file = getScoreFile(this->getCurrentLink());
	std::string line;
	for (unsigned i = 0; i < 8; i++) {
		if (!std::getline(file, line)) {
			line = "0";
		}
		ret.emplace_back("      " + line);
	}
	return ret;
}

void Arcade::Menu::displayModeSpecs(Arcade::IGraphicLib &lib)
{
	int size = lib.getMaxY() / Arcade::Menu::_maxLinks * 0.9;
	if (this->_mode == Arcade::Menu::MAIN) {
		this->_textBox.setX(size / 5 * 4);
		this->_textBox.setFontSize(size / 2);
		for (unsigned int i = 0; i < this->_help.size(); i++) {
			this->_textBox.setValue(this->_help[i]);
			this->_textBox.setY(size / 2 * (i + 1));
			lib.drawText(this->_textBox);
		}
	} else if (this->_mode == Arcade::Menu::GAMES) {
		std::vector<std::string> scores = this->getScores();
		this->_textBox.setFontSize(size);
		this->_textBox.setX(lib.getMaxX() - (size * 8));
		for (unsigned int i = 0; i < scores.size(); i++) {
			this->_textBox.setValue(scores[i]);
			this->_textBox.setY(size * i);
			lib.drawText(this->_textBox);
		}
	}
}

void Arcade::Menu::displayLinks(Arcade::IGraphicLib &lib)
{
	this->clearBackGround(lib);
	this->displayModeSpecs(lib);
	int size = lib.getMaxY() / Arcade::Menu::_maxLinks;
	auto links = this->getCurrentList();
	if (!links)
		return;
	this->_textBox.setFontSize(size);
	auto fontSize = size * 90 / 100;
	this->_textBox.setX(fontSize / 5 * 4);
	auto maxY = lib.getMaxY();
	for (int i = 0; i + links->begin() < links->end(); i++) {
		this->_textBox.setValue((this->_focus == i ? "> " : "") + getName((*links)[i]));
		this->_textBox.setY(maxY - (links->size() + 1 - i) * fontSize);
		lib.drawText(_textBox);
	}
}

Arcade::Menu::Modes Arcade::Menu::getMode() const
{
	return this->_mode;
}
