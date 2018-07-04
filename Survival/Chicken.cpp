#include "stdafx.h"
#include "Chicken.h"

Chicken::Chicken(const String strFile, float x, float y, float width, float height)
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

void Chicken::update(float time)
{
	setX(32);
	setY(32);

	switch (getState())//реализуем поведение в зависимости от направления.
	{
	case StateObject::RIGHT: setDX(getSpeed());		setDY(0);			break;
	case StateObject::LEFT:	 setDX(-getSpeed());	setDY(0);			break;
	case StateObject::DOWN:	 setDX(0);				setDY(getSpeed());	break;
	case StateObject::UP:	 setDX(0);				setDY(-getSpeed());	break;
	}

	setX(getX() + getDX() * time);
	setY(getY() + getDY() * time);

	setSpeed(0);//зануляем скорость, чтобы персонаж остановился.
	getSprite().setPosition(getX(), getY());

	checkCollisionWithMap();//ф-ция взаимодействия с картой

	if (getHealth() <= 0) {
		setLife(false);
	}
}

Chicken::~Chicken()
{
}
