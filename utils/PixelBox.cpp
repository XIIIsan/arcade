/*
** EPITECH PROJECT, 2018
** PixelBox
** File description:
** PixelBox
*/

#include "Utils/PixelBox.hpp"
#include "Utils/Color.hpp"
#include "Utils/Vect.hpp"
#include <string>
#include <vector>

Arcade::PixelBox::PixelBox(Arcade::Vect<size_t> size,
		 Arcade::Vect<size_t> pos, Arcade::Color col)
	: _colorFrame(size.getX() * size.getY(), col), _size(size), _pos(pos)
{
}

size_t Arcade::PixelBox::getHeight() const
{
	return _size.getY();
}

size_t Arcade::PixelBox::getY() const
{
	return _pos.getY();
}

void Arcade::PixelBox::setHeight(size_t height)
{
	_size.setY(height);
}

void Arcade::PixelBox::setY(size_t y)
{
	_pos.setY(y);
}

size_t Arcade::PixelBox::getWidth() const
{
	return _size.getX();
}

size_t Arcade::PixelBox::getX() const
{
	return _pos.getX();
}

void Arcade::PixelBox::setWidth(size_t width)
{
	_size.setX(width);
}

void Arcade::PixelBox::setX(size_t x)
{
	_pos.setX(x);
}

Arcade::Vect<size_t> Arcade::PixelBox::getSize() const
{
	return _size;
}

void Arcade::PixelBox::setSize(Arcade::Vect<size_t> size)
{
	_size = size;
}

Arcade::Vect<size_t> Arcade::PixelBox::getPos() const
{
	return _pos;
}

void Arcade::PixelBox::setPos(Arcade::Vect<size_t> pos)
{
	_pos = pos;
}

void Arcade::PixelBox::putPixel(Arcade::Vect<size_t> pos, Color col)
{
	if (pos.getX() < _size.getX() && pos.getY() < _size.getY())
		_colorFrame[_size.getX() * pos.getY() + pos.getX()] = col;
}

Arcade::Color Arcade::PixelBox::getPixel(Arcade::Vect<size_t> pos) const
{
	return _colorFrame[pos.getX() * pos.getY()];
}

void Arcade::PixelBox::putRect(Arcade::Vect<size_t> pos,
			       Arcade::Vect<size_t> size, Color col)
{
	for (unsigned int i = 0; i < size.getX(); i++) {
		for (unsigned int j = 0; j < size.getY(); j++) {
			this->putPixel(Arcade::Vect<size_t>(i + pos.getX(),
							    j + pos.getY()),
				       col);
		}
	}
}

std::vector<Arcade::Color> &Arcade::PixelBox::getPixelArray()
{
	return _colorFrame;
}
