#include <asteroid.h>

asteroid::asteroid() {}

asteroid::asteroid(sf::Vector2f position, sf::Texture* asteroidTex)
{
	asteroidSprite.setTexture(*asteroidTexture);
	asteroidSprite.setScale(1.5, 1.5);
	asteroidSprite.setPosition(position.x, position.y);

	srand(time(NULL));
}