#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;
using namespace sf;

//Слой 0 - для травы и стены возле края карты
//Слой 1 - для героя
//Слой 2 - для реки и деревьев
//Слой 3 - для деревьев

class Map
{
public:
	Map(const String file, unsigned int width, unsigned  int height);

	Sprite sprite[4];//создаём спрайт для всех слоев карты
	vector<vector<String>> tileMap; //вектор карты со слоями

	unsigned int getHeight() const;
	unsigned int getWidth() const;

	int getCountLayer() const;
	
private:
	const int _COUNT_LAYER = 4; //количество слоев
	Image _image;
	Texture _texture;
	unsigned int _height;
	unsigned int _width;
	String _file;

	void drawBasicBackground();//рисуем фон и стены возле края карты
	void generationRiver(int layer);
	void generationForest(int layer);
};