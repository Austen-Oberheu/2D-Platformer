//#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player(sf::Sprite &playerShape);
	~Player();

	void Update(sf::Sprite &playerShape, float deltaTime, std::vector<sf::FloatRect> &blockBoundingBox, sf::Vector2f origin);

	sf::Sprite playerSpriteUpdate(sf::Sprite &playerSprite, std::vector<sf::Texture> &spriteTexture, std::vector<sf::Texture>& walkingAnimation, std::vector <sf::Texture> &jumpingAnimation, float deltaTime, sf::Vector2f origin);

	void textureInit(std::vector<sf::Texture> &idleAnimation, std::vector <sf::Texture> &walkingAnimation, std::vector <sf::Texture> &jumpingAnimation);

public:
	

	sf::Vector2f lastPosition;
	sf::Vector2i velocity;
	sf::Time animationTimer;

	float time;

	bool walking = true;
	bool jumping = false;
	bool falling = false;
	bool allowedToJump;	
	bool walkingRight;

	int maxHorizontalVelocity;
	int minHorizontalVelocity;
	int maxVerticalVelocity;
	int minVerticalVelocity;
	int frame = 0;

};

