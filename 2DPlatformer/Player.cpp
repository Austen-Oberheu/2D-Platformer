#include "stdafx.h"
#include "Player.h"


Player::Player(sf::Sprite &playerShape, sf::Texture &playerTexture)
{
	
	playerShape.setPosition(0, 300);
	playerShape.setOrigin(12.5, 25.f);
	playerShape.setScale(.2f, .2f);
	playerShape.setTexture(playerTexture);
	velocity.x = 0; 
	velocity.y = 0;
	lastPosition.x = playerShape.getPosition().x;
	lastPosition.y = playerShape.getPosition().y;
	maxHorizontalVelocity = 500;
	minHorizontalVelocity = -500;
	maxVerticalVelocity = 1000;
	minVerticalVelocity = -500;
	allowedToJump = false;


}


Player::~Player()
{
}

void Player::Update(sf::Sprite &playerShape, float deltaTime, std::vector<sf::FloatRect>& blockBoundingBox)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (velocity.x < maxHorizontalVelocity)
		{
			velocity.x += 50;
			std::cout << velocity.x << std::endl;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (velocity.x > minHorizontalVelocity)
		{
			velocity.x -= 50;
			
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (allowedToJump == true)
		{
			velocity.y -= 500;
			allowedToJump = false;
			jumping = true;
			falling = true;

		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (falling == false && velocity.y >= minHorizontalVelocity || jumping == false)
		{
			allowedToJump = false;
			falling = true;
		}
		if (falling == false && jumping == true && velocity.y < minHorizontalVelocity)
		{
			allowedToJump = false;
			falling = true;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		if (velocity.x < 0)
		{
			velocity.x += 25;
		}
		if (velocity.x > 0)
		{
			velocity.x -= 25;
		}
	}

	if (falling == true)
	{
		velocity.y += 10;
	}

	sf::FloatRect playerBoundingBox = playerShape.getGlobalBounds();

	for (int i = 0; i < blockBoundingBox.size(); i++)
	{
		if (playerBoundingBox.intersects(blockBoundingBox[i]))
		{
			falling = false;
			if (velocity.y > 0 || velocity.y < 0)
			{
				allowedToJump = true;
				velocity.y = 0;
				playerShape.setPosition(lastPosition);
				break;
			}
		}
	}

	//std::cout << "x: " << velocity.x << " y: " << velocity.y << std::endl;
	lastPosition.x = playerShape.getPosition().x;
	lastPosition.y = playerShape.getPosition().y;

	playerShape.move(velocity.x * deltaTime, velocity.y * deltaTime);

}

sf::Sprite Player::playerSpriteUpdate(sf::Sprite &playerSprite, std::vector<sf::Texture>& spriteTexture, float deltaTime)
{
	/*if deltaTime*/
	playerSprite.setTexture(spriteTexture[frame]);
	frame += 1;
	if (frame == 9)
		frame = 0;
	return playerSprite;
}
