#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Entity.h"

using namespace sf;

class Chicken :	public Entity
{
public:
	Chicken() = delete;
	Chicken(const String file, float x, float y, float width, float height);

	void update(float time);

	~Chicken();
};

