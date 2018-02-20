//#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player(sf::Sprite &playerShape, sf::Texture &playerTexture);
	~Player();

	void Update(sf::Sprite &playerShape, float deltaTime, std::vector<sf::FloatRect> &blockBoundingBox);

	sf::Sprite playerSpriteUpdate(sf::Sprite &playerSprite, std::vector<sf::Texture> &spriteTexture, float deltaTime);

public:
	sf::Vector2f lastPosition;
	sf::Vector2i velocity;
	bool jumping = false;
	bool falling = false;
	bool allowedToJump;	
	int maxHorizontalVelocity;
	int minHorizontalVelocity;
	int maxVerticalVelocity;
	int minVerticalVelocity;
	int frame = 0;
};

