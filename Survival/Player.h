#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <sstream>
#include <iostream>
#include "Map.h"
#include "ProgressBar.h"
#include "Entity.h"

using namespace sf;

class Player : public Entity
{
public:

	Player(const String file, float width, float height);

	View getView() const;

	Text getText() const;

	void setWood(unsigned int wood);
	int getWood() const;

	void setFood(unsigned int food);
	int getFood() const;

	void setSatiety(float satiety);
	float getSatiety() const;

	void drawProgressBar(RenderWindow &window);
	
	void update(float time); 
	void resetView(int width, int height);

private:
	Image _image;
	Text _text;
	Font _font;
	ProgressBar _progressBar;
	float _widthWindow, _heightWindow;
	unsigned int _wood;
	unsigned int _food;
	float _satiety;  //сытость
	View _view;//камера игрока

	void getPlayerCoordinateForView(); //функция для считывания координат игрока для камеры
	void control(float time); //управление персонажем
	void setPosition(); 
	void catchFish(float time);
	void cutDownTree(float time);
};
