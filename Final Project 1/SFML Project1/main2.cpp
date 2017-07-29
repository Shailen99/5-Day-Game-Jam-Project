#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullets.h"

/*
Monday:
- Finished the movement code allowing the player to move through the game world.
- Implemented a background image to show the game world in which the player resides.
- Added a basic, looping engine sound which plays throughout the exploratory phase of the game.
- Added camera movement so player can now move around freely and have the camera follow them.

Tuesday:
- Added State Machines to show different parts of the game although
  right now the only part which is active is the map.
- Added basic camera and player collision so they can't go through the map.
- Added one song for background music which loops as of now.

Wednesday:
- Implemented a Health System which functions properly and shows on screen.
- Added a game over screen for when player health reaches 0 though it doesn't show on screen.
- Added stationary asteroids which hurt the player.
- Health loss is slowed down for when the player collides with the asteroid.

Thursday:
(Morning)
- Added three more asteroids to create a basic asteroid field in the game.
- Added basic hyperboost/nitro which speeds up the players movement when clicked.
- Added a visual reminder to show that the player is using nitro/Hyper Boost.
- Added a currency otherwise known as credits in the game.
(Afternoon):
- Added ores which the player can get by mining and then can turn into credits.
- Added three planets which shows planet names when collided with. These will be used as platformer exploration areas when I complete the game later.
- Added an npc ship which moves around randomly and when it collides with wall, it moves somewhere else in the map. Although it sometimes glitches out and moves randomly.
- Added a game over function though you'll have to reopen the game to make it work, since player's health, when equalling zero, closes the program.
- Added two enemies who when touched make the player lose 100 health per second.

Friday:
- Fixed enemy collisions with the wall so they now stay within the boundaries.
- Fixed enemy movement so they now move randomly and sometimes slowly.
- Added bullets which shoot all over the map

Needs to be done on Thursday (Order of Importance or what can be done):
1. Fix health damage with enemies and make it possible to kill enemies in the game.
2. Add another enemy.
*/
enum GameState
{
	 SPACE, GAMEOVER
};
GameState state = SPACE;
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1680, 1050), "Final Project");

	//Camera
	sf::View camera(sf::FloatRect(50, 50, 150, 150));
	camera.setSize(1680, 1050);
	camera.setCenter(1300, 850);

	//Bullets
	bool fired = false;
	std::vector<Bullets> bulletPos = {};
	//Bullets
	sf::Sprite playerBullet;
	sf::Vector2f pos;
	float x = 0;
	float y = 0;
	pos = sf::Vector2f(x, y);
	sf::Texture playerBulletTexture;
	playerBulletTexture.loadFromFile("Textures/bullet.png");
	playerBullet.setTexture(playerBulletTexture);
	playerBullet.setRotation(0.0f);
	playerBullet.setOrigin(10, 10);
	playerBullet.setScale(1, 1);
	playerBullet.setPosition(pos);

	//Currency/Gold/"Credits"
	int Currency = 0;
	sf::Text money;
	sf::Font gameFont;
	gameFont.loadFromFile("Font/Candal.ttf");

	money.setFont(gameFont);
	money.setString("Credits: " + std::to_string(Currency));
	money.setCharacterSize(50);
	money.setColor(sf::Color::Green);
	money.setPosition(1150, 1000);

	//Planet Sprites
	sf::Texture glassPlanetTexture;
	sf::Texture gasPlanetTexture;
	sf::Texture rockPlanetTexture;
	sf::Sprite glassPlanet;//Planet Name:Shilles 78WQ
	sf::Sprite gasPlanet;//Planet Name:Qeymia
	sf::Sprite rockPlanet;//Planet Name:Chion  

	glassPlanetTexture.loadFromFile("Textures/planet_glass.png");
	glassPlanet.setTexture(glassPlanetTexture);
	glassPlanet.setPosition(2000, 1000);

	gasPlanetTexture.loadFromFile("Textures/hjm-small_gas_planet.png");
	gasPlanet.setTexture(gasPlanetTexture);
	gasPlanet.setPosition(1200, 1230);

	rockPlanetTexture.loadFromFile("Textures/rock_type_planet.png");
	rockPlanet.setTexture(rockPlanetTexture);
	rockPlanet.setPosition(200, 700);

	//Planets & Planet Names
	sf::Text glassPlanetName;
	sf::Text gasPlanetName;
	sf::Text rockPlanetName;

	glassPlanetName.setFont(gameFont);
	gasPlanetName.setFont(gameFont);
	rockPlanetName.setFont(gameFont);

	glassPlanetName.setCharacterSize(50);
	glassPlanetName.setColor(sf::Color::White);
	glassPlanetName.setPosition(2000, 900);

	gasPlanetName.setCharacterSize(50);
	gasPlanetName.setColor(sf::Color::White);
	gasPlanetName.setPosition(1100, 1130);

	rockPlanetName.setCharacterSize(50);
	rockPlanetName.setColor(sf::Color::White);
	rockPlanetName.setPosition(200, 650);

	//Ore Sprites
	sf:: Texture OreTexture;
	OreTexture.loadFromFile("Textures/shieldstonegrey.png");
	sf::Sprite OreSprite;
	OreSprite.setTexture(OreTexture);
	OreSprite.setPosition(600, 300);

	sf::Sprite OreSprite1;
	OreSprite1.setTexture(OreTexture);
	OreSprite1.setPosition(700, 700);

	//Enemy Ship
	sf:: Texture Shiptexture;
	Shiptexture.loadFromFile("Textures/spiked ship 3. small.blue_.png");
	sf:: Sprite upgradeShip;
	upgradeShip.setTexture(Shiptexture);
	upgradeShip.setPosition(400,1000);
	sf::Clock clock;
	//Enemy Ship 2
	sf::Texture Shiptexture1;
	Shiptexture1.loadFromFile("Textures/Spaceship_tut_thin.png");
	sf::Sprite upgradeShip1;
	upgradeShip1.setTexture(Shiptexture1);
	upgradeShip1.setPosition(1000, 1000);

	//Health
	int PlayHealth = 1000;
	sf::Text healthText;
	healthText.setFont(gameFont);
	healthText.setString("Health: " + std::to_string(PlayHealth));
	healthText.setCharacterSize(50);
	healthText.setColor(sf::Color::Red);
	healthText.setPosition(1150, 950);

	//Hyperboost
	sf::Text HBText;
	HBText.setFont(gameFont);
	HBText.setCharacterSize(100);
	HBText.setColor(sf::Color::Cyan);
	HBText.setPosition(700, 300);

	//Background Music
	sf::Music music2;
	music2.openFromFile("Gymnopaedia.ogg");
	music2.play();
	//Asteroid 1
	sf::Texture asteroidTex;
	asteroidTex.loadFromFile("Textures/0492.png");
	sf::Sprite asteroidSprite;
	asteroidSprite.setTexture(asteroidTex);
	asteroidSprite.setPosition(400, 400);

	//Asteroid 2
	sf::Sprite asteroidSprite1;
	asteroidSprite1.setTexture(asteroidTex);
	asteroidSprite1.setPosition(657, 857);
	
	//Asteroid 3
	sf::Sprite asteroidSprite2;
	asteroidSprite2.setTexture(asteroidTex);
	asteroidSprite2.setPosition(1000, 300);

	//Asteroid 4
	sf::Sprite asteroidSprite3;
	asteroidSprite3.setTexture(asteroidTex);
	asteroidSprite3.setPosition(717, 567);

	//Asteroid 5
	sf::Sprite asteroidSprite4;
	asteroidSprite4.setTexture(asteroidTex);
	asteroidSprite4.setPosition(854, 700);

	//Background Image
	sf::Texture backtext;
	backtext.loadFromFile("Textures/space-03.jpg");
	sf::Sprite backSprite;
	backSprite.setTexture(backtext);

	//Player Model
	sf::Texture playertex;
	playertex.loadFromFile("Textures/player_ship.png");
	sf::Sprite playerSprite;
	playerSprite.setTexture(playertex);
	playerSprite.setOrigin(32, 32);
	playerSprite.setScale(1.5, 1.5);
	playerSprite.setPosition(1300, 850);

	//Game Over Screen
	bool GameOver = false;
	//Hyper Boost Movement
	bool HyperSpeed = false;
	//Player and Camera Movement
	bool movingUp = false;
	bool movingDown = false;
	bool movingLeft = false;
	bool movingRight = false;
	//Enemy Movement
	srand(time(NULL));
	float random = (rand() % 5) - 2;
	float random2 = (rand() % 5) - 2;
	float random3 = (rand() % 5) - 2;
	float random4 = (rand() % 5) - 2;

	while (window.isOpen())
		{

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
					//Nitro Movement
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code ==sf::Keyboard::LShift)
					{
						HyperSpeed = true;
					}
				}
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code ==  sf::Keyboard::LShift)
					{
						HyperSpeed = false;
					}
				}
					//Gun Conditionals
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Up && fired == false)
					{
						Bullets b = Bullets(-100,-100,0);
						b.fire(playerSprite.getPosition().x, playerSprite.getPosition().y,0);
						bulletPos.push_back(b);
						fired = true;
					}
					if (event.key.code == sf::Keyboard::Down && fired == false)
					{
						Bullets b = Bullets(-100, -100, 2);
						b.fire(playerSprite.getPosition().x, playerSprite.getPosition().y, 2);
						bulletPos.push_back(b);
						fired = true;
					}
					if (event.key.code == sf::Keyboard::Right && fired == false)
					{
						Bullets b = Bullets(-100, -100, 1);
						b.fire(playerSprite.getPosition().x, playerSprite.getPosition().y, 1);
						bulletPos.push_back(b);
						fired = true;
					}
					if (event.key.code == sf::Keyboard::Left && fired == false)
					{
						Bullets b = Bullets(-100, -100, 3);
						b.fire(playerSprite.getPosition().x, playerSprite.getPosition().y, 3);
						bulletPos.push_back(b);
						fired = true;
					}
				}
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Up)
					{
						fired = false;
					}
					if (event.key.code == sf::Keyboard::Down)
					{
						fired = false;
					}
					if (event.key.code == sf::Keyboard::Right)
					{
						fired = false;
					}
					if (event.key.code == sf::Keyboard::Left)
					{
						fired = false;
					}
				}


				//Player Control
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::W)
					{
						movingUp = true;
					}
					if (event.key.code == sf::Keyboard::S)
					{
						movingDown = true;
					}
					if (event.key.code == sf::Keyboard::D)
					{
						movingRight = true;
					}
					if (event.key.code == sf::Keyboard::A)
					{
						movingLeft = true;
					}
				}
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::W)
					{
						movingUp = false;
					}
					if (event.key.code == sf::Keyboard::S)
					{
						movingDown = false;
					}
					if (event.key.code == sf::Keyboard::A)
					{
						movingLeft = false;
					}
					if (event.key.code == sf::Keyboard::D)
					{
						movingRight = false;
					}
				}
			}

			//Player movement
			sf::Vector2f movement(0, 0);
			if (movingUp)
				movement.y -= 1.0;
			if (movingDown)
				movement.y += 1.0;
			if (movingRight)
				movement.x += 1.0;
			if (movingLeft)
				movement.x -= 1.0;
			//Nitro
			if (HyperSpeed)
			{
				HBText.setString("Hyperboost intiated");

				if (movingUp)
					movement.y -= 1.0;
				if (movingDown)
					movement.y += 1.0;
				if (movingRight)
					movement.x += 1.0;
				if (movingLeft)
					movement.x -= 1.0;
			}
			else
			{
				HBText.setString("");
			}
			//Enemy movement
			if (clock.getElapsedTime().asSeconds() >= 1)
			{
				random = (rand() %3) - 1.5;
				random2 = (rand() % 3) - 1.5;
				random3 = (rand() % 4) - 2;
				random4 = (rand() % 4) - 2;
				clock.restart();
			}
			upgradeShip.move(random, random2);

			if (upgradeShip.getPosition().x >= (2760))
			{
				upgradeShip.move(-5, 0);
			}
			if (upgradeShip.getPosition().x <= 0)
			{
				upgradeShip.move(5, 0);
			}
			if (upgradeShip.getPosition().y >= (1810))
			{
				upgradeShip.move(0, -5);
			}
			if (upgradeShip.getPosition().y <= 0)
			{
				upgradeShip.move(0, 5);
			}


			upgradeShip1.move(random3, random4);

			if (upgradeShip1.getPosition().x >= (2760))
			{
				upgradeShip.move(-5, 0);
			}
			if (upgradeShip1.getPosition().x <= 0)
			{
				upgradeShip1.move(5, 0);
			}
			if (upgradeShip1.getPosition().y >= (1810))
			{
				upgradeShip1.move(0, -5);
			}
			if (upgradeShip1.getPosition().y <= 0)
			{
				upgradeShip1.move(0, 5);
			}
			//Camera Boundaries
			if (playerSprite.getPosition().x >= (2760))
			{
				movement.x -= 5.0;
			}
			if (playerSprite.getPosition().x <= 0)
			{
				movement.x += 5.0;
			}
			if (playerSprite.getPosition().y >= (1810))
			{
				movement.y -= 5.0;
			}
			if (playerSprite.getPosition().y <= 0)
			{
				movement.y += 5.0;
			}

			//Asteroids and Player Collisions
			if (playerSprite.getGlobalBounds().intersects(asteroidSprite.getGlobalBounds()))
			{
				PlayHealth -= .00005f;
				healthText.setString("Health: " + std::to_string(PlayHealth));
			}
			if (playerSprite.getGlobalBounds().intersects(asteroidSprite1.getGlobalBounds()))
			{
				PlayHealth -= .00005f;
				healthText.setString("Health: " + std::to_string(PlayHealth));
			}
			if (playerSprite.getGlobalBounds().intersects(asteroidSprite2.getGlobalBounds()))
			{
				PlayHealth -= .00005f;
				healthText.setString("Health: " + std::to_string(PlayHealth));
			}
			if (playerSprite.getGlobalBounds().intersects(asteroidSprite3.getGlobalBounds()))
			{
				PlayHealth -= .00005f;
				healthText.setString("Health: " + std::to_string(PlayHealth));
			}
			if (playerSprite.getGlobalBounds().intersects(asteroidSprite4.getGlobalBounds()))
			{
				PlayHealth -= .00005f;
				healthText.setString("Health: " + std::to_string(PlayHealth));
			}
			//Ores
			if (playerSprite.getGlobalBounds().intersects(OreSprite.getGlobalBounds()))
			{
				Currency += 100.0f;
				money.setString("Credits: " + std::to_string(Currency));
				OreSprite.setPosition(1000000,100000);
			}
			if (playerSprite.getGlobalBounds().intersects(OreSprite1.getGlobalBounds()))
			{
				Currency += 100.0f;
				money.setString("Credits: " + std::to_string(Currency));
				OreSprite1.setPosition(1000000, 1000000);
			}

			//Planet Names
			if (playerSprite.getGlobalBounds().intersects(rockPlanet.getGlobalBounds()))
			{
				rockPlanetName.setString("Planet: Chion ");
			}
			else
			{
				rockPlanetName.setString(" ");
			}
			if (playerSprite.getGlobalBounds().intersects(gasPlanet.getGlobalBounds()))
			{
				gasPlanetName.setString("Planet: Qeymia");
			}
			else
			{
				gasPlanetName.setString(" ");
			}
			if (playerSprite.getGlobalBounds().intersects(glassPlanet.getGlobalBounds()))
			{
				glassPlanetName.setString("Planet: Shilles 78WQ ");
			}
			else
			{
				glassPlanetName.setString(" ");

			}
			//Change Game State to Game Over State
			if (PlayHealth <= 0)
			{
				window.close();
			}
			//Enemy And Bullet Collisionsv
			int EnemyHealth = 100;
			int EnemyHealth1 = 100;
		if (upgradeShip1.getGlobalBounds().intersects(playerBullet.getGlobalBounds()))
			{
				Currency += 100.0f;
				money.setString("Credits: " + std::to_string(Currency));
				EnemyHealth -= 100;
			}
			if (EnemyHealth >= 0)
			{
				upgradeShip1.setPosition(10000,1000);
			}

			//Drawing Objects
			camera.move(movement);
			window.setView(camera);
			playerSprite.move(movement);
			window.clear();
			window.draw(backSprite);
			//Asteroid Field
			window.draw(asteroidSprite);
			window.draw(asteroidSprite1);
			window.draw(asteroidSprite2);
			window.draw(asteroidSprite3);
			window.draw(asteroidSprite4);
			window.draw(rockPlanet);
			window.draw(gasPlanet);
			window.draw(glassPlanet);
			//Upgrade Ship and Gems to find/Credits
			window.draw(OreSprite);
			window.draw(OreSprite1);
			window.draw(upgradeShip);
			window.draw(upgradeShip1);
			//Draw Player and Text
			window.draw(playerSprite);
			healthText.move(movement);
			window.draw(healthText);
			HBText.move(movement);
			window.draw(HBText);
			money.move(movement);
			window.draw(money);
			window.draw(rockPlanetName);
			window.draw(gasPlanetName);
			window.draw(glassPlanetName);

			//bullet updating
			for (int i = 0; i < bulletPos.size(); i++) {
				bulletPos[i].update();
			}
			for (int i = 0; i < bulletPos.size(); i++) {
				bulletPos[i].draw(&window);
			}
			window.display();
		}
}
