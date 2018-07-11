#pragma once

#include <list>
#include <memory>
#include "Player.h"
#include "map.h"
#include "Entity.h"

class Animation
{
public:
	Animation();

	void setMap(Map &map);
	void setPlayer(Player &player);
	void setEntity(Entity *Entity);

	void draw(RenderWindow &window, float &time);
private:
	Map *_map;
	Player *_player;
	list<Entity *> _listEntities;

	void drawAnimationPlayer(float &time);
	void drawAnimationMap(RenderWindow &window);
};