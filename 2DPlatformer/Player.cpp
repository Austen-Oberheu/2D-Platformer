#include "stdafx.h"
#include "Player.h"


Player::Player(sf::Sprite &playerShape)
{
	playerShape.setPosition(25, 300);
	playerShape.setScale(.2f, .2f);
	
	velocity.x = 0; 
	velocity.y = 0;
	lastPosition.x = playerShape.getPosition().x;
	lastPosition.y = playerShape.getPosition().y;
	maxHorizontalVelocity = 500;
	minHorizontalVelocity = -500;
	maxVerticalVelocity = 1000;
	minVerticalVelocity = -1500;
	allowedToJump = false;
	
	time = 0.f;

}


Player::~Player()
{
}

void Player::Update(sf::Sprite &playerShape, float deltaTime, std::vector<sf::FloatRect>& blockBoundingBox)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		
		playerShape.setScale(.2f, .2f);
		if (velocity.x < maxHorizontalVelocity)
		{
			velocity.x += 50;
			std::cout << velocity.x << std::endl;
		}
		walking = true;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		
		playerShape.setScale(-.2f, .2f);

		if (velocity.x > minHorizontalVelocity)
		{
			velocity.x -= 50;
			
		}
		walking = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (allowedToJump == true)
		{
			velocity.y -= 1500;
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
		walking = false;
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
		velocity.y += 50;
	}

	sf::FloatRect playerBoundingBox = playerShape.getGlobalBounds();
	

	for (int i = 0; i < blockBoundingBox.size(); i++)
	{
		if (playerBoundingBox.intersects(blockBoundingBox[i]))
		{
			
			
			if (velocity.y > 0 && allowedToJump == false /*|| velocity.y < 0*/)
			{
				falling = false;
				allowedToJump = true;
				velocity.y = 0;
				playerShape.setPosition(playerShape.getPosition().x, lastPosition.y);
				break;
			}
		}
	}

	//std::cout << "x: " << velocity.x << " y: " << velocity.y << std::endl;
	//lastPosition.x = playerShape.getPosition().x;
	lastPosition.y = playerShape.getPosition().y;

	playerShape.move(velocity.x * deltaTime, velocity.y * deltaTime);

}

sf::Sprite Player::playerSpriteUpdate(sf::Sprite &playerSprite, std::vector<sf::Texture>& idleAnimation, std::vector<sf::Texture>& walkingAnimation, float deltaTime, sf::Vector2f origin)
{
	time += deltaTime;

	if ((time / deltaTime) > 10) 
	{
		if (walking == true)
		{
			
			playerSprite.setTexture(walkingAnimation[frame]);
			frame += 1;
			if (frame == 9)
				frame = 0;
			time = 0.f;
			
			playerSprite.setTextureRect(sf::IntRect(origin.x, origin.y, walkingAnimation[frame].getSize().x, walkingAnimation[frame].getSize().y));
		}
		else
		{
			playerSprite.setTexture(idleAnimation[frame]);
			frame += 1;
			if (frame == 9)
				frame = 0;
			time = 0.f;
			playerSprite.setTextureRect(sf::IntRect(origin.x, origin.y, idleAnimation[frame].getSize().x, idleAnimation[frame].getSize().y));
		}
		
	}
	return playerSprite;
}

void Player::textureInit(std::vector<sf::Texture> &idleAnimation, std::vector <sf::Texture> &walkingAnimation)
{
	idleAnimation[0].loadFromFile("Textures/Idle__000.png");
	idleAnimation[1].loadFromFile("Textures/Idle__001.png");
	idleAnimation[2].loadFromFile("Textures/Idle__002.png");
	idleAnimation[3].loadFromFile("Textures/Idle__003.png");
	idleAnimation[4].loadFromFile("Textures/Idle__004.png");
	idleAnimation[5].loadFromFile("Textures/Idle__005.png");
	idleAnimation[6].loadFromFile("Textures/Idle__006.png");
	idleAnimation[7].loadFromFile("Textures/Idle__007.png");
	idleAnimation[8].loadFromFile("Textures/Idle__008.png");
	idleAnimation[9].loadFromFile("Textures/Idle__009.png");

	walkingAnimation[0].loadFromFile("Textures/Run__000.png");
	walkingAnimation[1].loadFromFile("Textures/Run__001.png");
	walkingAnimation[2].loadFromFile("Textures/Run__002.png");
	walkingAnimation[3].loadFromFile("Textures/Run__003.png");
	walkingAnimation[4].loadFromFile("Textures/Run__004.png");
	walkingAnimation[5].loadFromFile("Textures/Run__005.png");
	walkingAnimation[6].loadFromFile("Textures/Run__006.png");
	walkingAnimation[7].loadFromFile("Textures/Run__007.png");
	walkingAnimation[8].loadFromFile("Textures/Run__008.png");
	walkingAnimation[9].loadFromFile("Textures/Run__009.png");
}
