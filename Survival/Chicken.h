#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Entity.h"

using namespace sf;

class Chicken :	public Entity
{
public:
	Chicken() = delete;
	Chicken(const String strFile, const float x, const float y, const float width, const float height);

	void update(const float time);

	~Chicken();
private:
	void setPosition() override final;
};

