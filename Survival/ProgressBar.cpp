#include "stdafx.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(float x, float y, float width, float heigh, sf::Color boxcolor, sf::Color barcolor)
{
	this->create(x, y, width, heigh, boxcolor, barcolor);
}

void ProgressBar::create(float x, float y, float width, float heigh, sf::Color boxcolor, sf::Color barcolor)
{
	_x = x;
	_y = y;
	_width = width;
	_heigh = heigh;
	_progression = 0;

	_box.setFillColor(sf::Color(0, 0, 0, 0));
	_box.setOutlineColor(boxcolor);
	_box.setOutlineThickness(1);
	_bar.setFillColor(barcolor);

	_box.setPosition(x, y);
	_bar.setPosition(x, y);

	_box.setSize(sf::Vector2<float>(width, heigh));
	_bar.setSize(sf::Vector2<float>(0, heigh));

}

void ProgressBar::setProgression(float p)
{
	if (p > 1)
	{
		p = 1;
	}
	if (p < 0)
	{
		p = 0;
	}
	_progression = p;
}

float ProgressBar::getProgression() const
{
	return _progression;
}

float ProgressBar::getWidth() const
{
	return _width;
}

float ProgressBar::getHeight() const
{
	return _heigh;
}

void ProgressBar::setCoordinate(float x, float y)
{
	_box.setPosition(x, y);
	_bar.setPosition(x, y);
}

void ProgressBar::setVisible(bool visible)
{
	_isvisible = visible;
}

bool ProgressBar::getVisible() const
{
	return _isvisible;
}

void ProgressBar::draw(sf::RenderWindow* mrw)
{
	if (_isvisible) {
		_bar.setSize(sf::Vector2<float>(_width * _progression, _heigh));
		if (_progression > 0) {
			mrw->draw(_bar);
		}
		mrw->draw(_box);
	}
}

/////////////private//////////