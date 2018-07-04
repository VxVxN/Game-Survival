#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
}

Sprite& Entity::getSprite()
{
	return _sprite;
}

void Entity::setFile(const String &strFile)
{
	_file = strFile;
}

const String Entity::getFile() const
{
	return _file;
}

void Entity::imageLoadFromFile(const String &strFile)
{
	_image.loadFromFile(strFile);
}

Image Entity::getImage() const
{
	return _image;
};

Texture & Entity::getTexture()
{
	return _texture;
}

void Entity::setState(StateObject state)
{
	_state = state;
}

const Entity::StateObject Entity::getState() const
{
	return _state;
}

void Entity::setMap(Map &map)
{
	_map = &map;
	setPosition();
}

Map & Entity::getMap()
{
	return *_map;
}

void Entity::setX(float x)
{
	_x = x;
}

float Entity::getX() const
{
	return _x;
}

void Entity::setY(float y)
{
	_y = y;
}

float Entity::getY() const
{
	return _y;
}

void Entity::setDX(float dx)
{
	_dx = dx;
}

float Entity::getDX() const
{
	return _dx;
}

void Entity::setDY(float dy)
{
	_dy = dy;
}

float Entity::getDY() const
{
	return _dy;
}

void Entity::setSpeed(float speed)
{
	_speed = speed;
}

float Entity::getSpeed() const
{
	return _speed;
}

void Entity::setWidth(unsigned int  width)
{
	_width = width;
}

unsigned int  Entity::getWidth() const
{
	return _width;
}

void Entity::setHeight(unsigned int  height)
{
	_height = height;
}

unsigned int  Entity::getHeight() const
{
	return _height;
}

void Entity::setLife(bool life)
{
	_life = life;
}

bool Entity::getLife() const
{
	return _life;
}

void Entity::setHealth(float health)
{
	_health = health;
}

float Entity::getHealth() const
{
	return _health;
}

void Entity::setTextureRect(float x, float y, float width, float height)
{
	getSprite().setTextureRect(IntRect(x, y, width, height));
}

bool Entity::checkCollisionWithMap()//ф-ция взаимодействия с картой
{
	for (int z = 0; z < _map->getCountLayer(); z += 1) {
		for (int x = getX() / 32; x < (getX() + getWidth()) / 32; x++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32
			for (int y = getY() / 32; y < (getY() + getHeight()) / 32; y++)
			{
				if (_map->tileMap[z][x][y] == '0' || _map->tileMap[z][x][y] == 'r' || _map->tileMap[z][x][y] == '5' || _map->tileMap[z][x][y] == '6' || _map->tileMap[z][x][y] == '7' || 
					_map->tileMap[z][x][y] == '8')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (getDY() > 0)
					{
						setY(y * 32 - getHeight());
						return true;
					}
					if (getDY() < 0)
					{
						setY(y * 32 + 32);
						return true;
					}
					if (getDX() > 0)
					{
						setX(x * 32 - getWidth());
						return true;
					}
					if (getDX() < 0)
					{
						setX(x * 32 + 32);
						return true;
					}
				}
			}
	}
	return false;
}

/////////////private//////////