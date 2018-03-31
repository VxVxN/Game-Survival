#include "stdafx.h"
#include "Animation.h"


Animation::Animation()
{
}

void Animation::setMap(Map &map)
{
	_map = &map;
}

void Animation::setPlayer(Player &player)
{
	_player = &player;
}

void Animation::draw(RenderWindow &window, float &time)
{
	drawAnimationPlayer(time);
	drawAnimationMap(window);
}

/////////////private//////////

void Animation::drawAnimationPlayer(float &time)
{
	if (_player->getLife()) {
		static float CurrentFrame = 0;//хранит текущий кадр
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			_player->setTextureRect(32 * int(CurrentFrame), 32, 32, 32); //меняем спрайт, делая анимацию
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			_player->setTextureRect(32 * (int(CurrentFrame) + 1), 32, -32, 32); //меняем спрайт, делая анимацию
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			_player->setTextureRect(32 * int(CurrentFrame), 97, 32, 32); //меняем спрайт, делая анимацию
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			_player->setTextureRect(32 * int(CurrentFrame), 1, 32, 32); //меняем спрайт, делая анимацию
		}

	}
}

void Animation::drawAnimationMap(RenderWindow &window)
{
	///рисуем всю карту
	for (int z = 0; z < _map->getCountLayer(); z++) { // проходим по всем слоям 
		for (int x = 0; x < _map->getWidth(); x++) {
			for (int y = 0; y < _map->getHeight(); y++) {
				if (z == 0) {
					_map->sprite[z].setTextureRect(IntRect(32, 64, 32, 32)); //рисуем траву
				}
				else {
					if (_map->tileMap[z][x][y] == ' ') _map->sprite[z].setTextureRect(IntRect(650, 650, 32, 32)); //рисуем пустоту вторым и последующими слоями над травой
				}

				if (_map->tileMap[z][x][y] == 'r') _map->sprite[z].setTextureRect(IntRect(96, 672, 32, 32));//рисуем реку
				if (_map->tileMap[z][x][y] == '0') _map->sprite[z].setTextureRect(IntRect(96,  32, 32, 32));//рисуем стену возле края карты

				//////////////////дерево////////////////////////////////

				if (_map->tileMap[z][x][y] == '1') _map->sprite[z].setTextureRect(IntRect(64, 389, 32, 32));
				if (_map->tileMap[z][x][y] == '2') _map->sprite[z].setTextureRect(IntRect(96, 389, 32, 32));
				if (_map->tileMap[z][x][y] == '3') _map->sprite[z].setTextureRect(IntRect(0,  384, 32, 32));
				if (_map->tileMap[z][x][y] == '4') _map->sprite[z].setTextureRect(IntRect(32, 384, 32, 32));
				if (_map->tileMap[z][x][y] == '5') _map->sprite[z].setTextureRect(IntRect(0,  416, 32, 32));
				if (_map->tileMap[z][x][y] == '6') _map->sprite[z].setTextureRect(IntRect(32, 416, 32, 32));

				//////////срубленное дерево//////////////////////
				if (_map->tileMap[z][x][y] == '7') _map->sprite[z].setTextureRect(IntRect(0, 448, 32, 32));
				if (_map->tileMap[z][x][y] == '8') _map->sprite[z].setTextureRect(IntRect(32, 448, 32, 32));

				_map->sprite[z].setPosition(x * 32, y * 32);
				if (z == 1) {
					window.draw(_player->getSprite()); // на первом слою рисуем персонажа
				}
				else {
					window.draw(_map->sprite[z]); // а на остальных рисуем карту
				}
			}
		}
	}
}