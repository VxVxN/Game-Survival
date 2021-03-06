#include "stdafx.h"
#include "Animation.h"
#include <array>

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

void Animation::setEntity(Entity *entity)
{
	entity->setMap(*_map);
	_listEntities.push_back(entity);
}

void Animation::draw(RenderWindow &window, float &time)
{
	(*_listEntities.begin())->update(time);
	drawAnimationPlayer(time);
	drawAnimationMap(window);
}

/////////////private//////////

void Animation::drawAnimationPlayer(float &time)
{
	if (_player->getLife()) {
		static float CurrentFrame = 0;//������ ������� ����
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			_player->setTextureRect(32 * int(CurrentFrame), 32, 32, 32); //������ ������, ����� ��������
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			_player->setTextureRect(32 * (int(CurrentFrame) + 1), 32, -32, 32); //������ ������, ����� ��������
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			_player->setTextureRect(32 * int(CurrentFrame), 97, 32, 32); //������ ������, ����� ��������
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			_player->setTextureRect(32 * int(CurrentFrame), 1, 32, 32); //������ ������, ����� ��������
		}

	}
}

void Animation::drawAnimationMap(RenderWindow &window)
{
	///������ ��� �����
	for (int z = 0; z < _map->getCountLayer(); z++) { // �������� �� ���� ����� 
		for (int x = 0; x < _map->getWidth(); x++) {
			for (int y = 0; y < _map->getHeight(); y++) {
				if (z == 0) {
					_map->sprite[z].setTextureRect(IntRect(32, 64, 32, 32)); //������ �����
				}
				else {
					if (_map->tileMap.at(z).at(x)[y] == ' ') _map->sprite[z].setTextureRect(IntRect(650, 650, 32, 32)); //������ ������� ������ � ������������ ������ ��� ������
				}

				if (_map->tileMap.at(z).at(x)[y] == 'r') _map->sprite[z].setTextureRect(IntRect(96, 672, 32, 32));//������ ����
				if (_map->tileMap.at(z).at(x)[y] == '0') _map->sprite[z].setTextureRect(IntRect(96, 32, 32, 32));//������ ����� ����� ���� �����
				if (_map->tileMap.at(z).at(x)[y] == 'b') _map->sprite[z].setTextureRect(IntRect(320, 32, 32, 32));//������ ����

				//////////////////������////////////////////////////////

				if (_map->tileMap.at(z).at(x)[y] == '1') _map->sprite[z].setTextureRect(IntRect(64, 389, 32, 32));
				if (_map->tileMap.at(z).at(x)[y] == '2') _map->sprite[z].setTextureRect(IntRect(96, 389, 32, 32));
				if (_map->tileMap.at(z).at(x)[y] == '3') _map->sprite[z].setTextureRect(IntRect(0,  384, 32, 32));
				if (_map->tileMap.at(z).at(x)[y] == '4') _map->sprite[z].setTextureRect(IntRect(32, 384, 32, 32));
				if (_map->tileMap.at(z).at(x)[y] == '5') _map->sprite[z].setTextureRect(IntRect(0,  416, 32, 32));
				if (_map->tileMap.at(z).at(x)[y] == '6') _map->sprite[z].setTextureRect(IntRect(32, 416, 32, 32));

				//////////���������� ������//////////////////////
				if (_map->tileMap.at(z).at(x)[y] == '7') _map->sprite[z].setTextureRect(IntRect(0, 448, 32, 32));
				if (_map->tileMap.at(z).at(x)[y] == '8') _map->sprite[z].setTextureRect(IntRect(32, 448, 32, 32));

				_map->sprite[z].setPosition(x * 32, y * 32);
				if (z == 1) {
					window.draw(_player->getSprite()); // �� ������ ���� ������ ���������

					for (auto & entity : _listEntities) {
						window.draw((*entity).getSprite());
					}
				}
				else {
					window.draw(_map->sprite[z]); // � �� ��������� ������ �����
				}
			}
		}
	}
}