//
// EPITECH Project, 2018
// cpp_arcade
// File description:
// Core.cpp
//

#include <algorithm>
#include <cstring>
#include <fstream>
#include "Core/Core.hpp"

const Arcade::CoreMap Arcade::Core::_keys = {
	{Arcade::A, &Arcade::Core::handleKeyLGrap},
	{Arcade::Q, &Arcade::Core::handleKeyLGame},
	{Arcade::P, &Arcade::Core::handleKeyRGrap},
	{Arcade::M, &Arcade::Core::handleKeyRGame},
	{Arcade::R, &Arcade::Core::handleKeyReset},
	{Arcade::NONE, &Arcade::Core::handleKeyElse}
};

Arcade::Core::Core()
	: _libs("./lib"), _games("./games"), _lib(nullptr), _game(nullptr),
	  _title("Main Menu"), _newLib("NoCare"), _newGame("None"),
	  _menu(this->_games.getNames())
{
}

bool Arcade::Core::loadArgs(int ac, char **av)
{
	bool ret(false);
	if (ac == 2 && this->_libs.loadLib(av[1]) &&
		!this->_games.getNames().empty()) {
		ret = true;
		this->_lib = this->_libs.getInstance();
	}
	return ret;
}

void Arcade::Core::closeGame()
{
	if (this->_game) {
		this->_game->stop();
		this->_games.unloadLib();
		this->_game = nullptr;
	}
}

bool Arcade::Core::checkMenuMode()
{
	bool ret(true);
	auto mode = this->_menu.getMode();
	switch (mode) {
	case Arcade::Menu::QUIT:
		this->quit();
		ret = false;
		break;
	case Arcade::Menu::GAMES:
		this->closeGame();
		break;
	default:
		break;
	}
	return ret;
}

void Arcade::Core::quit()
{
	this->_lib->closeRenderer();
}

int Arcade::Core::handleKeyReset()
{
	if (this->_game) {
		this->_game->stop();
		this->_game->init();
	}
	return 0;
}

int Arcade::Core::handleKeyLGrap()
{
	this->_newLib = this->_libs.leftLib();
	return 0;
}

int Arcade::Core::handleKeyLGame()
{
	if (this->_game)
		this->_newGame = this->_games.leftLib();
	return 0;
}

int Arcade::Core::handleKeyRGrap()
{
	this->_newLib = this->_libs.rightLib();
	return 0;
}

int Arcade::Core::handleKeyRGame()
{
	if (this->_game)
		this->_newGame = this->_games.rightLib();
	return 0;
}

int Arcade::Core::handleKeyElse()
{
	std::cout << "useless key" << std::endl;
	return 0;
}

void Arcade::Core::handleKeys(Arcade::Keys key)
{
	if (this->_keys.count(key) == 0) {
		auto ret = this->_menu.handleKeys(key);
		auto toLoad = this->_menu.getToLoad();
		if (toLoad != "None") {
			this->_newGame = toLoad;
			this->_menu.clearToLoad();
		}
		if (!ret && this->_game)
			this->_game->applyEvent(key);
	} else
		Arcade::Core::_keys.at(key)(this);
}

void Arcade::Core::renderMenu()
{
	this->_menu.displayLinks(*this->_lib);
}

static int myGetNbr(std::string &nbr)
{
	int ret = 0;
	int i = 0;
	while ('0' <= nbr[i] && nbr[i] <= '9') {
		ret = ret * 10 + nbr[i] - '0';
		i++;
	}
	return ret;
}

void Arcade::Core::saveScore(std::string game, int score)
{
	std::fstream file = this->_menu.getScoreFile(game);
	if (!file.good())
		return;
	std::vector<int> scores;
	std::string line = "no";
	while (!line.empty()) {
		std::getline(file, line);
		scores.push_back(myGetNbr(line));
	}
	file.clear();
	file.close();
	if (std::find(scores.begin(), scores.end(), score) == scores.end())
		scores.emplace_back(score);
	std::sort(scores.begin(), scores.end(), std::greater<int>());
	while (scores.size() > 8)
		scores.pop_back();
	file = this->_menu.getScoreFile(game);
	for (auto it : scores)
		file << it << std::endl;
	file.close();
}

void Arcade::Core::renderGame()
{
	if (this->_newGame != "None") {
		if (this->_game)
			this->_game->stop();
		this->_games.loadLib(this->_newGame);
		this->_game = this->_games.getInstance();
		this->_game->init();
		this->_newGame = "None";
	}
	if (this->_game) {
		if (!this->_game->update()) {
			auto score = this->_game->getScore();
			this->saveScore(this->_menu.getCurrentLink(), score);
		}
		this->_game->refresh(*this->_lib);
	}
}

void Arcade::Core::libRun()
{
	bool isOpen(true);
	this->_lib->openRenderer();
	this->_lib->clearWindow();
	this->_lib->refreshWindow();
	while (isOpen && this->_newLib == "None") {
		this->_lib->pollEvents();
		isOpen = this->_lib->isOpen();
		if (!isOpen)
			break;
		this->_lib->clearWindow();
		if (this->_game || this->_newGame != "None")
			this->renderGame();
		else
			this->renderMenu();
		auto key = this->_lib->getLastEvent();
		if (key != Arcade::NONE) {
			this->handleKeys(key);
		}
		this->_lib->refreshWindow();
		isOpen = this->checkMenuMode();
	}
	this->_lib->closeRenderer();
}

bool Arcade::Core::changeLib()
{
	bool ret = this->_libs.loadLib(this->_newLib);
	if (ret) {
		this->_lib = this->_libs.getInstance();
	}
	return ret;
}

void Arcade::Core::run()
{
	while (this->_newLib != "None") {
		this->_newLib = "None";
		this->libRun();
		if (this->_newLib != "None") {
			if (!this->changeLib())
				throw std::bad_alloc();
		}
	}
}