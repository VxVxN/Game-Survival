#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "map.h"
#include "Animation.h"
#include "Chicken.h"

using namespace sf;

int main()
{
	int windowsWidth = 640;
	int windowsHeidht = 480;
	RenderWindow window(sf::VideoMode(windowsWidth, windowsHeidht), "Game"); 

	Clock clock;

	Player player("Sprites/person.png", 0.0, 0.0, 27.0, 31.0);

	Map map("Sprites/map.png", 25, 17);

	player.setMap(map);
	player.resetView(windowsWidth, windowsHeidht);//устанавливаем размер камеры

	Animation animation;
	animation.setMap(map);
	animation.setPlayer(player);

	animation.setEntity(new Chicken("Sprites/animals.png", 200.0, 19.0, 15.0, 13.0));
	animation.setEntity(new Chicken("Sprites/animals.png", 200.0, 19.0, 15.0, 13.0));
	animation.setEntity(new Chicken("Sprites/animals.png", 200.0, 19.0, 15.0, 13.0));

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart(); //перезагружает время
		time = time / 800; //скорость игры

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		player.update(time);
		window.setView(player.getView());

		animation.draw(window, time);

		window.draw(player.getText());
		player.drawProgressBar(window);

		window.display();
	}

	return 0;
}
