#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"

using namespace sf;

class Entity
{
public:
	Entity();

	enum class StateObject { LEFT, RIGHT, UP, DOWN };

	Sprite & getSprite();

	void setFile(const String &strFile);
	const String getFile() const;

	void imageLoadFromFile(const String &strFile);
	Image getImage() const;

	Texture & getTexture();

	void setState(StateObject state);
	const StateObject getState() const;

	void setMap(Map &map);
	Map & getMap();

	void setX(float x);
	float getX() const;

	void setY(float y);
	float getY() const;

	void setDX(float dx);
	float getDX() const;

	void setDY(float dy);
	float getDY() const;

	void setSpeed(float speed);
	float getSpeed() const;

	void setWidth(unsigned int  width);
	unsigned int  getWidth() const;

	void setHeight(unsigned int  height);
	unsigned int  getHeight() const;

	void setLife(bool life);
	bool getLife() const;

	void setHealth(float health);
	float getHealth() const;

	void setTextureRect(float x, float y, float width, float height);

	virtual void update(float time) {}; 
	bool checkCollisionWithMap();//ф-ция взаимодействия с картой
	
private:
	Sprite _sprite;
	String _file; 
	Image _image;
	Texture _texture;
	StateObject _state;
	Map * _map;
	float _x, _y;
	float _dx, _dy; //ускорение (по х и по у)
	float _speed;
	unsigned int  _width, _height;
	bool _life;
	float _health;
	virtual void setPosition() {};
};

