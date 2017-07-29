#pragma once
#include <SFML/Graphics.hpp>
class Projectile
{
public:
	sf::Texture bulletTexturee;
	static sf:: Sprite bulletSprite;
	
	void SetDirection(sf::Sprite);
	void SetSpeed(float);
	};

