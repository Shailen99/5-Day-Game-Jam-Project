#include "Bullets.h"


Bullets::Bullets()
{

}
Bullets::Bullets(float x, float y, int direction)
{
	pos = sf::Vector2f(x, y);
	d = direction;
	sf::Texture playerBulletTexture;
	playerBulletTexture.loadFromFile("Textures/bullet.png");
	playerBullet.setTexture(playerBulletTexture);
	playerBullet.setRotation(0.0f);
	playerBullet.setOrigin(10, 10);
	playerBullet.setScale(1, 1);
}


Bullets::~Bullets()
{

}

void Bullets::fire(float x, float y, int direction)
{
	pos = sf::Vector2f(x, y);
	d = direction;
	fired = true;
}

void Bullets::update()
{
	if (fired == true) {
		switch (d) {
		case 0:
			pos.y--;
			break;
		case 1:
			pos.x++;
			break;
		case 2:
			pos.y++;
			break;
		case 3:
			pos.x--;
			break;
		}
	}
	playerBullet.setPosition(pos);
}

void Bullets::loadTexture()
{


}

void Bullets::draw(sf::RenderWindow *window)
{
	window->draw(playerBullet);
}