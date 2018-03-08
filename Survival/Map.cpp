#pragma once
#include "stdafx.h"
#include "Map.h"

Map::Map(const String file, unsigned int width, unsigned int height)
{
	_height = height;
	_width = width;
	_file = file;

	srand(time(0)); // автоматическая рандомизация

	drawBasicBackground();//рисуем фон и стены возле края карты
	generationRiver(2); // генерациия реки на втором слое
	for (int i = 0; i < 10; i++) {
		generationForest(2); // генерациия леса на втором слое и (второй + 1) слое
	}

	_image.loadFromFile(file);
	_texture.loadFromImage(_image);
	sprite[0].setTexture(_texture);
	//sprite[1].setTexture(_texture); // этот слой для персонажа, поэтому тут не нажна текстура карты
	sprite[2].setTexture(_texture);
	sprite[3].setTexture(_texture);

}

unsigned int Map::getHeight() const
{
	return _height;
}

unsigned int Map::getWidth() const
{
	return _width;
}

int Map::getCountLayer() const
{
	return _COUNT_LAYER;
}


/////////////private//////////

void Map::drawBasicBackground()
{
	for (int z = 0; z < _COUNT_LAYER; z++) {
		vector<String> vStr;
		for (int i = 0; i < _width; i++) {
			String str;
			for (int j = 0; j < _height; j++) {
				if ((i == 0 && z == 0) || (z == 0 && i == _width - 1)) {
					str += '0';
				}
				else {
					str += ' ';
				}
			}
			if (z == 0) {
				str[0] = '0';
				str[_height - 1] = '0';
			}
			vStr.push_back(str);
		}
		tileMap.push_back(vStr);
	}
}

void Map::generationRiver(int layer)
{
	int x, y;
	int xEndRiver, yEndRiver;
	int width = _width - 2, height = _height - 2;
	if (rand() % 2) { //задаем начало реки, начитается либо по Х или по У координате
		if (rand() % 2) { //задаем начало реки по Х координате слева либо с право начинается
			x = 1;
		}
		else {
			x = width;
		}
		y = 1 + rand() % height;
	}
	else {
		if (rand() % 2) { //задаем начало реки по У координате слева либо с право начинается
			y = 1;
		}
		else {
			y = height;
		}
		x = 1 + rand() % width;
	}

	if (x == 1) { //если река начиналось на х = 0 то закончится на х = width
		xEndRiver = width;
		yEndRiver = 1 + rand() % height;
	}
	else if (x == width) {//если река начиналось на х = width то закончится на х = 0
		xEndRiver = 1;
		yEndRiver = 1 + rand() % height;
	}
	else if (y == 1) {//если река начиналось на y = 0 то закончится на y = heigth
		yEndRiver = height;
		xEndRiver = 1 + rand() % width;
	}
	else if (y == height) {//если река начиналось на y = heigth то закончится на y = 0
		yEndRiver = 1;
		xEndRiver = 1 + rand() % width;
	}

	while (x != xEndRiver || y != yEndRiver) { //цикл генераций реки

		if (x > _width || y > _height) {
			break;
		}

		tileMap[layer][x][y] = 'r';
		bool isRandom = rand() % 2;
		if (x == xEndRiver) {
			isRandom = 0;
		}
		else if (y == yEndRiver) {
			isRandom = 1;
		}
		if (isRandom) { // случайным образом река идет по Х или по У
			if (x < xEndRiver) {
				x++;
			}
			else if (x > xEndRiver) {
				x--;
			}
		}
		else {
			if (y < yEndRiver) {
				y++;
			}
			else if (y > yEndRiver)  {
				y--;
			}
		}
	}
	tileMap[layer][xEndRiver][yEndRiver] = 'r';
}

void Map::generationForest(int layer)
{
	int x = 10;
	while (x)
	{
		x--;
		int width = 6+1, height = 5+1;

		int randomX = 1 + rand() % (_width - width),
			randomY = 1 + rand() % (_height - height);

		bool isFreeSpace = true; //проверяет есть свободное место для леса

		for (int x = randomX; x < (randomX + width); x++) {
			for (int y = randomY; y < (randomY + height); y++) {
				if (tileMap[layer][x][y] != ' ') {
					isFreeSpace = false;
				}
			}
		}

		if (isFreeSpace == true) {
			///////////////////для примера
			int x = randomX, y = randomY;
			x += 0; y += 1;
			tileMap[layer][x][y] = '1';
			tileMap[layer][x + 1][y] = '2';
			tileMap[layer][x][y + 1] = '3';
			tileMap[layer][x + 1][y + 1] = '4';
			tileMap[layer][x][y + 2] = '5';
			tileMap[layer][x + 1][y + 2] = '6';
			x = randomX, y = randomY;
			x += 2; y += 0;
			tileMap[layer][x][y] = '1';
			tileMap[layer][x + 1][y] = '2';
			tileMap[layer][x][y + 1] = '3';
			tileMap[layer][x + 1][y + 1] = '4';
			tileMap[layer][x][y + 2] = '5';
			tileMap[layer][x + 1][y + 2] = '6';
			x = randomX, y = randomY;
			x += 1; y += 2;
			tileMap[layer + 1][x][y] = '1';
			tileMap[layer + 1][x + 1][y] = '2';
			tileMap[layer + 1][x][y + 1] = '3';
			tileMap[layer + 1][x + 1][y + 1] = '4';
			tileMap[layer + 1][x][y + 2] = '5';
			tileMap[layer + 1][x + 1][y + 2] = '6';
			x = randomX, y = randomY;
			x += 3; y += 2;
			tileMap[layer + 1][x][y] = '1';
			tileMap[layer + 1][x + 1][y] = '2';
			tileMap[layer + 1][x][y + 1] = '3';
			tileMap[layer + 1][x + 1][y + 1] = '4';
			tileMap[layer + 1][x][y + 2] = '5';
			tileMap[layer + 1][x + 1][y + 2] = '6';
			x = randomX, y = randomY;
			x += 4; y += 1;
			tileMap[layer][x][y] = '1';
			tileMap[layer][x + 1][y] = '2';
			tileMap[layer][x][y + 1] = '3';
			tileMap[layer][x + 1][y + 1] = '4';
			tileMap[layer][x][y + 2] = '5';
			tileMap[layer][x + 1][y + 2] = '6';
			break;
		}
	}
}
