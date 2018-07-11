#include "stdafx.h"
#include "Chicken.h"

Chicken::Chicken(const String strFile, const float x, const float y, const float width, const float height)
{
	setFile(strFile);
	setWidth(width);
	setHeight(height);

	setSpeed(0.0);
	setHealth(100);
	setLife(true);

	imageLoadFromFile(strFile);
	getTexture().loadFromImage(getImage());

	getSprite().setTexture(getTexture());
	getSprite().setTextureRect(IntRect(x, y, getWidth(), getHeight()));

	srand(time(0)); // автоматическая рандомизация
}

void Chicken::update(const float time)
{
	//switch (getState())//реализуем поведение в зависимости от направления.
	//{
	//case StateObject::RIGHT: setDX(getSpeed());		setDY(0);			break;
	//case StateObject::LEFT:	 setDX(-getSpeed());	setDY(0);			break;
	//case StateObject::DOWN:	 setDX(0);				setDY(getSpeed());	break;
	//case StateObject::UP:	 setDX(0);				setDY(-getSpeed());	break;
	//}

	//setX(getX() + getDX() * time);
	//setY(getY() + getDY() * time);

	//setSpeed(0);//зануляем скорость, чтобы персонаж остановился.
	getSprite().setPosition(getX(), getY());

	checkCollisionWithMap();//ф-ция взаимодействия с картой

	if (getHealth() <= 0) {
		setLife(false);
	}
}

Chicken::~Chicken()
{
}

/////////////private//////////

void Chicken::setPosition()
{
	int x = 0;
	int y = 0;
	int z = 0;
	while (true) {
		for (x = 1 + rand() % getMap().getWidth() - 1; x < getMap().getWidth(); x++) {
			for (y = 1 + rand() % getMap().getHeight(); y < getMap().getHeight(); y++) {
				bool isFreeSpace = true; //проверяет есть свободное место для персонажа на всех словах
				for (z = 0; z < getMap().getCountLayer(); z++) {
					if (getMap().tileMap.at(z).at(x)[y] != ' ') {
						isFreeSpace = false;
					}
				}
				z--;
				if (isFreeSpace) {
					setX(x * 32); setY(y * 32);//координата появления спрайта
					break;
				}
			}
			if (getMap().tileMap.at(z).at(x)[y] == ' ') {
				break;
			}
		}
		if (getMap().tileMap.at(z).at(x)[y] == ' ') {
			break;
		}
	}
}