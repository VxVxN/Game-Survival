#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;
using namespace sf;

//���� 0 - ��� ����� � ����� ����� ���� �����
//���� 1 - ��� �����
//���� 2 - ��� ���� � ��������
//���� 3 - ��� ��������

class Map
{
public:
	Map(const String file, unsigned int width, unsigned  int height);

	Sprite sprite[4];//������ ������ ��� ���� ����� �����
	vector<vector<String>> tileMap; //������ ����� �� ������

	unsigned int getHeight() const;
	unsigned int getWidth() const;

	int getCountLayer() const;
	
private:
	const int _COUNT_LAYER = 4; //���������� �����
	Image _image;
	Texture _texture;
	unsigned int _height;
	unsigned int _width;
	String _file;

	void drawBasicBackground();//������ ��� � ����� ����� ���� �����
	void generationRiver(int layer);
	void generationForest(int layer);
};