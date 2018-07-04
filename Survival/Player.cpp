#include "stdafx.h"
#include "Player.h"

Player::Player(const String strFile, float x, float y, float width, float height) {
	setFile(strFile);
	setWidth(width); 
	setHeight(height);

	setSpeed(0.0);
	_wood = 3;
	_food = 0;
	setHealth(100);
	_satiety = 100;  //сытость
	setLife(true);

	imageLoadFromFile(strFile);
	getTexture().loadFromImage(getImage());

	getSprite().setTexture(getTexture());
	getSprite().setTextureRect(IntRect(x, y, getWidth(), getHeight())); 

	_font.loadFromFile("CyrilicOld.ttf");
	_text.setFont(_font);
	_text.setCharacterSize(20);
	_text.setColor(Color::Red);
	_text.setStyle(sf::Text::Bold);

	_progressBar.create(50, 50, 75, 20, sf::Color::Black, sf::Color::Red);
	_progressBar.setProgression(0.0);

	srand(time(0)); // автоматическая рандомизация
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

	switch (getState())//реализуем поведение в зависимости от направления.
	{
	case StateObject::RIGHT: setDX(getSpeed());		setDY(0);			break;
	case StateObject::LEFT:	 setDX(-getSpeed());	setDY(0);			break;
	case StateObject::DOWN:	 setDX(0);				setDY(getSpeed());	break;
	case StateObject::UP:	 setDX(0);				setDY(-getSpeed());	break;
	}

	setX(getX() + getDX() * time);
	setY(getY() + getDY() * time);

	setSpeed(0);//зануляем скорость, чтобы персонаж остановился.
	getSprite().setPosition(getX(), getY());

	checkCollisionWithMap();//ф-ция взаимодействия с картой

	std::ostringstream playerWoodString;    
	playerWoodString << _wood;		

	std::ostringstream playerFoodString;
	playerFoodString << _food;		

	std::ostringstream playerHealthString;    
	playerHealthString << (int)getHealth();		

	std::ostringstream playerSatietyString;    
	playerSatietyString << (int)_satiety;		

	_text.setString("\tДерево: " + playerWoodString.str() + "\t" + "Еда: " + playerFoodString.str() + "\t" +
					"Здоровье: " + playerHealthString.str() + "%\t" + "Сытость: " + playerSatietyString.str() + "%");
	_text.setPosition(_view.getCenter().x - _widthWindow / 2, _view.getCenter().y - _heightWindow / 2);//задаем позицию текста

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
	_view.reset(sf::FloatRect(0, 0, width, height));//устанавливаем камеру
	_widthWindow = width;
	_heightWindow = height;
}

/////////////private//////////

void Player::getPlayerCoordinateForView() {
	float tempX = getX(); float tempY = getY();//считываем коорд игрока и проверяем их, чтобы убрать края

	if (getX() < 320) { //убираем из вида левую сторону
		tempX = 320;
	}
	if (getX() > (getMap().getWidth() - 10) * 32) { //убираем из вида правую сторону
		tempX = (getMap().getWidth() - 10) * 32;
	}
	if (getY() < 240) { //верхнюю сторону
		tempY = 240;
	}
	if (getY() > (getMap().getHeight() - 8) * 32) { //нижнюю сторону
		tempY = (getMap().getHeight() - 8) * 32;
	}

	_view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 
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
		else if (Keyboard::isKeyPressed(Keyboard::Num1)) {
			if (getWood() > 0) {
				buildBridge();
			}
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

				bool isFreeSpace = true; //проверяет есть свободное место для персонажа на всех словах
				for (z = 0; z < getMap().getCountLayer(); z++) {
					if (getMap().tileMap[z][x][y] != ' ') {
						isFreeSpace = false;
					}
				}
				z--;
				if (isFreeSpace) {
					setX(x * 32); setY(y * 32);//координата появления спрайта
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
			if ((rand() % 2)) { // вероятность поймать рыбу 50%
				_food++;
			}
			_progressBar.setProgression(0.0);
		}
	};
	int x;
	int y;
	switch (getState())//в зависимости от направления ищем реку
	{
	case StateObject::RIGHT:
		x = getX() / 32 + 1;
		y = getY() / 32;
		if (getMap().tileMap[2][x][y] == 'r') {
			catchFishLambda();
		}
		break;
	case StateObject::LEFT:
		x = getX() / 32 - 1;
		y = getY() / 32;
		if (getMap().tileMap[2][x][y] == 'r') {
			catchFishLambda();
		}
		break;
	case StateObject::DOWN:
		x = getX() / 32;
		y = getY() / 32 + 1;
		if (getMap().tileMap[2][x][y] == 'r') {
			catchFishLambda();
		}
		break;
	case StateObject::UP:
		x = getX() / 32;
		y = getY() / 32 - 1;
		if (getMap().tileMap[2][x][y] == 'r') {
			catchFishLambda();
		}
		break;
	}
}

void Player::cutDownTree(float time)
{
	auto cutDownTreeLambda = [&](int x, int y)
	{
		_progressBar.setVisible(true);
		_progressBar.setCoordinate(getX() - _progressBar.getWidth() / 2 + getWidth() / 2, getY() + getHeight());
		_progressBar.setProgression(_progressBar.getProgression() + time / 10000);
		if (_progressBar.getProgression() == 1) {
			_wood++;
			_progressBar.setProgression(0.0);
			for (int i(2); i < 4; i++) { // проходим по 2-му и 3-му слою, там деревия
				if (getMap().tileMap[i][x][y] == '5') { //меняем дерево на пенёк

					getMap().tileMap[i][x]		[y]		= '7';
					getMap().tileMap[i][x + 1]	[y]		= '8';
					getMap().tileMap[i][x]		[y - 1] = ' ';
					getMap().tileMap[i][x + 1]	[y - 1] = ' ';
					getMap().tileMap[i][x]		[y - 2] = ' ';
					getMap().tileMap[i][x + 1]	[y - 2] = ' ';
				}
				else if (getMap().tileMap[i][x][y] == '6') {

					getMap().tileMap[i][x]		[y]		= '8';
					getMap().tileMap[i][x - 1]	[y]		= '7';
					getMap().tileMap[i][x - 1]	[y - 1] = ' ';
					getMap().tileMap[i][x]		[y - 1] = ' ';
					getMap().tileMap[i][x - 1]	[y - 1] = ' ';
					getMap().tileMap[i][x]		[y - 2] = ' ';
					getMap().tileMap[i][x - 1]	[y - 2] = ' ';
				}
			}
		}
	};
	int shift = 2; // смещение для проверки где есть дерево
	int x;
	int y;
	for (int j(2); j < 4; j++) {  // проходим по 2-му и 3-му слою, там деревия
		switch (getState())//реализуем поведение в зависимости от направления. 
		{
		case StateObject::RIGHT:
			for (int i(0); i < shift; i++) {
				for (int k(0); k < shift; k++) { 
					x = getX() / 32 + i;
					y = getY() / 32 + k;
					if (getMap().tileMap[j][x][y] == '5' || getMap().tileMap[j][x][y] == '6') {
						cutDownTreeLambda(x, y);
					}
				}
			}
			break;
		case StateObject::LEFT:
			for (int i(0); i < shift; i++) {
				for (int k(0); k < shift; k++) {
					x = getX() / 32 - i;
					y = getY() / 32 + k;
					if (getMap().tileMap[j][x][y] == '5' || getMap().tileMap[j][x][y] == '6') {
						cutDownTreeLambda(x, y);
					}
				}
			}
			break;
		case StateObject::DOWN:
			for (int i(0); i < shift; i++) {
				for (int k(0); k < shift; k++) {
					x = getX() / 32 + k;
					y = getY() / 32 + i;
					if (getMap().tileMap[j][x][y] == '5' || getMap().tileMap[j][x][y] == '6') {
						cutDownTreeLambda(x, y);
					}
				}
			}
			break;
		case StateObject::UP:
			for (int i(0); i < shift; i++) {
				for (int k(0); k < shift; k++) {
					x = getX() / 32 + k;
					y = getY() / 32 - i;
					if (getMap().tileMap[j][x][y] == '5' || getMap().tileMap[j][x][y] == '6') {
						cutDownTreeLambda(x, y);
					}
				}
			}
			break;
		}
	}
}

void Player::buildBridge()
{
	int x;
	int y;
	switch (getState())//в зависимости от направления ищем реку
	{
	case StateObject::RIGHT:
		x = getX() / 32 + 1;
		y = getY() / 32;
		if (getMap().tileMap[2][x][y] == 'r') {
			getMap().tileMap[0][x][y] = 'b';
			getMap().tileMap[2][x][y] = ' ';
			setWood(getWood() - 1);
		}
		break;
	case StateObject::LEFT:
		x = getX() / 32 - 1;
		y = getY() / 32;
		if (getMap().tileMap[2][x][y] == 'r') {
			getMap().tileMap[0][x][y] = 'b';
			getMap().tileMap[2][x][y] = ' ';
			setWood(getWood() - 1);
		}
		break;
	case StateObject::DOWN:
		x = getX() / 32;
		y = getY() / 32 + 1;
		if (getMap().tileMap[2][x][y] == 'r') {
			getMap().tileMap[0][x][y] = 'b';
			getMap().tileMap[2][x][y] = ' ';
			setWood(getWood() - 1);
		}
		break;
	case StateObject::UP:
		x = getX() / 32;
		y = getY() / 32 - 1;
		if (getMap().tileMap[2][x][y] == 'r') {
			getMap().tileMap[0][x][y] = 'b';
			getMap().tileMap[2][x][y] = ' ';
			setWood(getWood() - 1);
		}
		break;
	}
}