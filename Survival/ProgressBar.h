#pragma once

#include <SFML/Graphics.hpp>


using namespace sf;


class ProgressBar
{
public:

	ProgressBar() {}

	ProgressBar(float x, float y, float width, float heigh, sf::Color boxcolor, sf::Color barcolor);

	void create(float x, float y, float width, float heigh, sf::Color boxcolor, sf::Color barcolor);

	void setProgression(float p);
	float getProgression() const;

	float getWidth() const;
	float getHeight() const;

	void setCoordinate(float x, float y);

	void setVisible(bool visible);
	bool getVisible() const;

	void draw(sf::RenderWindow* mrw);

private:
	float _x;
	float _y;
	float _width;
	float _heigh;
	float _progression;
	bool _isvisible = false;

	sf::RectangleShape _box;
	sf::RectangleShape _bar;

};