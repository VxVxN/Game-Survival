#include "stdafx.h"
#include "Player.h"

Player::Player(const String file, float width, float height) {  
	setFile(file);
	setWidth(width); 
	setHeight(height);

	setSpeed(0.0);
	_wood = 0;
	_food = 0;
	setHealth(100);
	_satiety = 100;  //�������
	setLife(true);

	_image.loadFromFile(getFile());
	getTexture().loadFromImage(_image);

	getSprite().setTexture(getTexture());
	getSprite().setTextureRect(IntRect(0, 0, getWidth(), getHeight())); 


	_font.loadFromFile("CyrilicOld.ttf");
	_text.setFont(_font);
	_text.setCharacterSize(20);
	_text.setColor(Color::Red);
	_text.setStyle(sf::Text::Bold);

	_progressBar.create(50, 50, 75, 20, sf::Color::Black, sf::Color::Red);
	_progressBar.setProgression(0.0);

	srand(time(0)); // �������������� ������������
}

View Player::getView() const
{
	return _view;
}

Text Player::getText() const
{
	return _text;
}

void Player::setWood(unsigned int wood)
{
	_wood = wood;
}

int Player::getWood() const
{
	return _wood;
}

void Player::setFood(unsigned int food)
{
	_food = food;
}

int Player::getFood() const
{
	return _food;
}

void Player::setSatiety(float satiety)
{
	_satiety = satiety;
}

float Player::getSatiety() const
{
	return _satiety;
}

void Player::drawProgressBar(RenderWindow &window)
{
	_progressBar.draw(&window);
}

void Player::update(float time) 
{
	control(time);
	getPlayerCoordinateForView();

	switch (getState())//��������� ��������� � ����������� �� �����������.
	{
	case StateObject::RIGHT: setDX(getSpeed());		setDY(0);			break;
	case StateObject::LEFT:	 setDX(-getSpeed());	setDY(0);			break;
	case StateObject::DOWN:	 setDX(0);				setDY(getSpeed());	break;
	case StateObject::UP:	 setDX(0);				setDY(-getSpeed());	break;
	}

	setX(getX() + getDX() * time);
	setY(getY() + getDY() * time);

	setSpeed(0);//�������� ��������, ����� �������� �����������.
	getSprite().setPosition(getX(), getY());

	checkCollisionWithMap();//�-��� �������������� � ������

	std::ostringstream playerWoodString;    
	playerWoodString << _wood;		

	std::ostringstream playerFoodString;
	playerFoodString << _food;		

	std::ostringstream playerHealthString;    
	playerHealthString << (int)getHealth();		

	std::ostringstream playerSatietyString;    
	playerSatietyString << (int)_satiety;		

	_text.setString("\t������: " + playerWoodString.str() + "\t" + "���: " + playerFoodString.str() + "\t" +
		"��������: " + playerHealthString.str() + "%\t" + "�������: " + playerSatietyString.str() + "%");
	_text.setPosition(_view.getCenter().x - _widthWindow / 2, _view.getCenter().y - _heightWindow / 2);//������ ������� ������

	if (_satiety >= 0) {
		_satiety -= time / 5000;
	}
	else {
		if (getHealth() > 0) {
			setHealth(getHealth() - time / 300);
		}
	}

	if (getHealth() <= 0) {
		setLife(false);
	}
}

void Player::resetView(int width, int height)
{
	_view.reset(sf::FloatRect(0, 0, width, height));//������������� ������
	_widthWindow = width;
	_heightWindow = height;
}

/////////////private//////////

void Player::getPlayerCoordinateForView() {
	float tempX = getX(); float tempY = getY();//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (getX() < 320) tempX = 320;//������� �� ���� ����� �������
	if (getX() >(getMap().getWidth() - 10) * 32) tempX = (getMap().getWidth() - 10) * 32;//������� �� ���� ������ �������
	if (getY() < 240) tempY = 240;//������� �������
	if (getY() >(getMap().getHeight() - 8) * 32) tempY = (getMap().getHeight() - 8) * 32;//������ �������	

	_view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 
}

void Player::control(float time)
{
	if (getLife()) {
		_progressBar.setVisible(false);
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			setState(StateObject::LEFT);
			setSpeed(0.1);
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			setState(StateObject::RIGHT);
			setSpeed(0.1);
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			setState(StateObject::UP);
			setSpeed(0.1);
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			setState(StateObject::DOWN);
			setSpeed(0.1);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Space)) {
			catchFish(time);
			cutDownTree(time);

		}
		if (!_progressBar.getVisible()) {
			_progressBar.setProgression(0.0);
		}
	}
}

void Player::setPosition()
{
	int x = 0;
	int y = 0;
	int z = 0;
	while (true) {
		for (x = 1 + rand() % getMap().getWidth(); x < getMap().getWidth(); x++) {
			for (y = 1 + rand() % getMap().getHeight(); y < getMap().getHeight(); y++) {
				bool isFreeSpace = true; //��������� ���� ��������� ����� ��� ��������� �� ���� ������
				for (z = 0; z < getMap().getCountLayer(); z++) {
					if (getMap().tileMap[z][x][y] != ' ') {
						isFreeSpace = false;
					}
				}
				z--;
				if (isFreeSpace) {
					setX(x * 32); setY(y * 32);//���������� ��������� �������
					break;
				}
			}
			if (getMap().tileMap[z][x][y] == ' ') {
				break;
			}
		}
		if (getMap().tileMap[z][x][y] == ' ') {
			break;
		}
	}
}

void Player::catchFish(float time)
{
	auto catchFishLambda = [&]()
	{
		_progressBar.setVisible(true);
		_progressBar.setCoordinate(getX() - _progressBar.getWidth() / 2 + getWidth() / 2, getY() + getHeight());
		_progressBar.setProgression(_progressBar.getProgression() + time / 3000);
		if (_progressBar.getProgression() == 1) {
			if ((rand() % 2)) { // ����������� ������� ���� 50%
				_food++;
			}
			_progressBar.setProgression(0.0);
		}
	};
	switch (getState())//� ����������� �� ����������� ���� ����
	{
	case StateObject::RIGHT:
		if (getMap().tileMap[2][getX() / 32 + 1][getY() / 32] == 'r') {
			catchFishLambda();
		}
		break;
	case StateObject::LEFT:
		if (getMap().tileMap[2][getX() / 32 - 1][getY() / 32] == 'r') {
			catchFishLambda();
		}
		break;
	case StateObject::DOWN:
		if (getMap().tileMap[2][getX() / 32][getY() / 32 + 1] == 'r') {
			catchFishLambda();
		}
		break;
	case StateObject::UP:
		if (getMap().tileMap[2][getX() / 32][getY() / 32] == 'r') {
			catchFishLambda();
		}
		break;
	}
}

void Player::cutDownTree(float time)
{
	auto cutDownTreeLambda = [&]()
	{
		_progressBar.setVisible(true);
		_progressBar.setCoordinate(getX() - _progressBar.getWidth() / 2 + getWidth() / 2, getY() + getHeight());
		_progressBar.setProgression(_progressBar.getProgression() + time / 10000);
		if (_progressBar.getProgression() == 1) {
			_wood++;
			_progressBar.setProgression(0.0);
		}
	};
	int shift = 3; // �������� �� �������� ��� ���� ������
	switch (getState())//��������� ��������� � ����������� �� �����������. 
	{
	shift = 1;
	case StateObject::RIGHT:
		for (int i(0); i < shift; i++) {
			if (getMap().tileMap[2][getX() / 32 + i][getY() / 32] == '5' || getMap().tileMap[2][getX() / 32 + i][getY() / 32] == '6') {
				cutDownTreeLambda();
			}
		}
		break;
	case StateObject::LEFT:
		for (int i(0); i < shift; i++) {
			if (getMap().tileMap[2][getX() / 32 - i][getY() / 32] == '5' || getMap().tileMap[2][getX() / 32 - i][getY() / 32] == '6') {
				cutDownTreeLambda();
			}
		}
		break;
	case StateObject::DOWN:
		for (int i(0); i < shift; i++) {
			if (getMap().tileMap[2][getX() / 32][getY() / 32 + i] == '5' || getMap().tileMap[2][getX() / 32][getY() / 32 + i] == '6') {
				cutDownTreeLambda();
			}
		}
		break;
	case StateObject::UP:
		for (int i(0); i < shift; i++) {
			if (getMap().tileMap[2][getX() / 32][getY() / 32 - i] == '5' || getMap().tileMap[2][getX() / 32][getY() / 32 - i] == '6') {
				cutDownTreeLambda();
			}
		}
		break;
	}
}