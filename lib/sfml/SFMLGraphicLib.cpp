#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstring>
#include "SFMLGraphicLib.hpp"

std::map<sf::Keyboard::Key, Arcade::Keys> Arcade::SFMLGraphicLib::_keys = {
	{sf::Keyboard::A, Arcade::A},
	{sf::Keyboard::B, Arcade::B},
	{sf::Keyboard::C, Arcade::C},
	{sf::Keyboard::D, Arcade::D},
	{sf::Keyboard::E, Arcade::E},
	{sf::Keyboard::F, Arcade::F},
	{sf::Keyboard::G, Arcade::G},
	{sf::Keyboard::H, Arcade::H},
	{sf::Keyboard::I, Arcade::I},
	{sf::Keyboard::J, Arcade::J},
	{sf::Keyboard::K, Arcade::K},
	{sf::Keyboard::L, Arcade::L},
	{sf::Keyboard::M, Arcade::M},
	{sf::Keyboard::N, Arcade::N},
	{sf::Keyboard::O, Arcade::O},
	{sf::Keyboard::P, Arcade::P},
	{sf::Keyboard::Q, Arcade::Q},
	{sf::Keyboard::R, Arcade::R},
	{sf::Keyboard::S, Arcade::S},
	{sf::Keyboard::T, Arcade::T},
	{sf::Keyboard::U, Arcade::U},
	{sf::Keyboard::V, Arcade::V},
	{sf::Keyboard::W, Arcade::W},
	{sf::Keyboard::X, Arcade::X},
	{sf::Keyboard::Y, Arcade::Y},
	{sf::Keyboard::Z, Arcade::Z},
	{sf::Keyboard::Left, Arcade::LEFT},
	{sf::Keyboard::Right, Arcade::RIGHT},
	{sf::Keyboard::Up, Arcade::UP},
	{sf::Keyboard::Down, Arcade::DOWN},
	{sf::Keyboard::Return, Arcade::ENTER},
	{sf::Keyboard::Space, Arcade::SPACE},
	{sf::Keyboard::Delete, Arcade::DELETE},
	{sf::Keyboard::BackSpace, Arcade::BACKSPACE},
	{sf::Keyboard::Tab, Arcade::TAB},
	{sf::Keyboard::Escape, Arcade::ESC}
};

Arcade::SFMLGraphicLib::SFMLGraphicLib()
	: _libName("sfml"), _window(nullptr)
{
}

Arcade::SFMLGraphicLib::~SFMLGraphicLib()
{
}

std::string Arcade::SFMLGraphicLib::getName() const
{
	return _libName;
}

bool Arcade::SFMLGraphicLib::isOpen() const
{
	if (this->_window)
		return this->_window->isOpen();
	return false;
}

void Arcade::SFMLGraphicLib::closeRenderer()
{
	delete _window;
	_window = nullptr;
}

void Arcade::SFMLGraphicLib::openRenderer()
{
	_window = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML");
	_font.loadFromFile("./resources/Symtext.ttf");
}

void Arcade::SFMLGraphicLib::clearWindow()
{
	if (_window != nullptr)
		_window->clear();
}

void Arcade::SFMLGraphicLib::refreshWindow()
{
	if (_window != nullptr)
		_window->display();	
}

void Arcade::SFMLGraphicLib::drawPixelBox(Arcade::PixelBox &pixelBox)
{
	sf::Uint8 *pixelArray = pixelBox.getPixelArray()[0];
	
	if (_window != nullptr) {
		_texture.create(pixelBox.getWidth(), pixelBox.getHeight());
		_texture.update(pixelArray);
		_sprite.setTexture(_texture);
		_sprite.setPosition(sf::Vector2f(pixelBox.getX(), pixelBox.getY()));
		_window->draw(_sprite);
	}
}

void Arcade::SFMLGraphicLib::drawText(Arcade::TextBox &drawText)
{
	if (_window != nullptr) {
		const auto &tmp = (unsigned char *)drawText.getColor();
		sf::Color color(tmp[0], tmp[1], tmp[2], tmp[3]);
		_text = sf::Text(drawText.getValue(), _font);
		_text.setCharacterSize(drawText.getFontSize());
		_text.setColor(color);
		_text.setPosition(drawText.getX(), drawText.getY());
		_window->draw(_text);
	}
}

Arcade::Keys Arcade::SFMLGraphicLib::getLastEvent()
{
	Arcade::Keys keyCode(Arcade::NONE);
	
	if (!_keyCode.empty()) {
		keyCode = _keyCode[0];
		_keyCode.erase(_keyCode.begin(), _keyCode.begin()+1);
	}
	return keyCode;
}

bool Arcade::SFMLGraphicLib::pollEvents()
{
	bool stateEvent(false);
	
	while (this->_window && _window->pollEvent(_event)) {
		if (_event.type == sf::Event::KeyPressed) {
			_keyCode.push_back(_keys[_event.key.code]);
			stateEvent = true;
		}
	}
	return stateEvent;
}

void Arcade::SFMLGraphicLib::clearEvents()
{
	memset(&this->_event, 0, sizeof(this->_event));
	_keyCode.clear();
}

Arcade::Vect<size_t> Arcade::SFMLGraphicLib::getScreenSize() const
{
	sf::Vector2u size;
	if (_window->isOpen())
		size = _window->getSize();
	else
		size = {0, 0};
	
	return (Arcade::Vect<size_t>(size.x, size.y));
}

int Arcade::SFMLGraphicLib::getMaxY() const
{
	auto size = this->getScreenSize();
	return (size.getY());
}

int Arcade::SFMLGraphicLib::getMaxX() const
{
	auto size = this->getScreenSize();
	return (size.getX());
}
