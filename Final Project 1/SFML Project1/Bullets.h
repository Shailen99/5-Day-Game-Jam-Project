#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <random>
#include <thread>
#include <chrono>
//bullet class
class Bullets
{
public:

	sf::Sprite playerBullet;
	Bullets();
	Bullets(float x, float y, int direction);
	~Bullets();
	void fire(float x, float y, int direction);
	void update();
	sf::Vector2f pos;
	int d;
	bool fired;
	void loadTexture();
	void draw(sf::RenderWindow *window);
};

