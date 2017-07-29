#include <SFML/Graphics.hpp>

class asteroid {
	sf::Texture asteroidTex;
	sf::Sprite asteroidSprite;
	float yPos;
	float xPos;

	asteroid();
	asteroid(sf::Vector2f position, sf::Texture* obstacleTexture);
	
	void update();
	void reposition();
	int randomizeYPos();
	int randomizeXPos();
};