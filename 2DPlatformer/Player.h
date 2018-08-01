//#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <list>
class Player
{
public:
	Player(sf::Sprite &playerShape, sf::Vector2f playerStart);
	~Player();

	void Update(sf::Sprite &playerShape, float deltaTime, int(&map)[100][100], /*std::vector<sf::RectangleShape> &blockBoundingBox,*/ sf::Vector2f origin, sf::Vertex ($bottomLine)[3][2], sf::Vertex($rightLine)[3][2], sf::Vertex($leftLine)[3][2], sf::Vertex($upLine)[3][2], bool &jumpVariable);

	sf::Sprite playerSpriteUpdate(sf::Sprite &playerSprite, std::vector<sf::Texture> &spriteTexture, std::vector<sf::Texture>& walkingAnimation, std::vector <sf::Texture> &jumpingAnimation, float deltaTime, sf::Vector2f origin);

	void textureInit(std::vector<sf::Texture> &idleAnimation, std::vector <sf::Texture> &walkingAnimation, std::vector <sf::Texture> &jumpingAnimation);

public:
	


	std::list<sf::Vector2f> lastPosition;
	sf::Vector2i velocity;
	sf::Time animationTimer;
	sf::Clock clock;

	float bottom, left, right, top;
	std::vector<sf::Vector2i> tiles;

	float time;

	bool walking = true;
	bool jumping = false;
	bool allowedToDoubleJump = false;
	bool hasDoubleJumped = false;
	bool falling = false;
	bool allowedToJump;	
	bool walkingRight;
	bool releasedSpaceKey = true;
	bool bottomCollision = false;

	int maxHorizontalVelocity;
	int minHorizontalVelocity;
	int maxVerticalVelocity;
	int minVerticalVelocity;
	int frame = 0;

};

