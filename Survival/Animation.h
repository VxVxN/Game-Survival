#pragma once

#include "Player.h"
#include "map.h"

class Animation
{
public:
	Animation();

	void setMap(Map &map);
	void setPlayer(Player &player);

	void draw(RenderWindow &window, float &time);
private:
	Map *_map;
	Player *_player;
	void drawAnimationPlayer(float &time);
	void drawAnimationMap(RenderWindow &window);
};