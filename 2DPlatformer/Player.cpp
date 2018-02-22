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
	walkingRight = true;
	time = 0.f;

}


Player::~Player()
{
}

void Player::Update(sf::Sprite &playerShape, float deltaTime, std::vector<sf::FloatRect>& blockBoundingBox, sf::Vector2f origin)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (velocity.x < maxHorizontalVelocity)
		{
			velocity.x += 50;
			std::cout << velocity.x << std::endl;
		}
		walking = true;
		walkingRight = true;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		
		//playerShape.scale(-1.f, 1.f);

		if (velocity.x > minHorizontalVelocity)
		{
			velocity.x -= 50;
			
		}
		walking = true;
		walkingRight = false;
		
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

	if (falling == true && velocity.y < maxVerticalVelocity)
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
				jumping = false;
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

sf::Sprite Player::playerSpriteUpdate(sf::Sprite &playerSprite, std::vector<sf::Texture>& idleAnimation, std::vector<sf::Texture>& walkingAnimation, std::vector <sf::Texture> &jumpingAnimation, float deltaTime, sf::Vector2f origin)
{
	time += deltaTime;

	if ((time / deltaTime) > 10) 
	{
		
		if (jumping == true)
		{
			playerSprite.setTexture(jumpingAnimation[frame]);
			frame += 1;
			if (frame == 9)
				frame = 8;
			time = 0.f;
			playerSprite.setTextureRect(sf::IntRect(origin.x, origin.y, jumpingAnimation[frame].getSize().x, jumpingAnimation[frame].getSize().y));
			if (walkingRight == false)
				playerSprite.setTextureRect(sf::IntRect(playerSprite.getTextureRect().width, 0, -playerSprite.getTextureRect().width, playerSprite.getTextureRect().height));
		}
		else if (walking == true)
		{

			playerSprite.setTexture(walkingAnimation[frame]);
			frame += 1;
			if (frame == 9)
				frame = 0;
			time = 0.f;
			playerSprite.setTextureRect(sf::IntRect(origin.x, origin.y, walkingAnimation[frame].getSize().x, walkingAnimation[frame].getSize().y));
			if (walkingRight == false)
				playerSprite.setTextureRect(sf::IntRect(playerSprite.getTextureRect().width, 0, -playerSprite.getTextureRect().width, playerSprite.getTextureRect().height));
		}
		else
		{
			playerSprite.setTexture(idleAnimation[frame]);
			frame += 1;
			if (frame == 9)
				frame = 0;
			time = 0.f;

			playerSprite.setTextureRect(sf::IntRect(origin.x, origin.y, idleAnimation[frame].getSize().x, idleAnimation[frame].getSize().y));
			if (walkingRight == false)
			{
				playerSprite.setTextureRect(sf::IntRect(playerSprite.getTextureRect().width, 0, -playerSprite.getTextureRect().width, playerSprite.getTextureRect().height));
			}
		}
		
	}
	return playerSprite;
}

void Player::textureInit(std::vector<sf::Texture> &idleAnimation, std::vector <sf::Texture> &walkingAnimation, std::vector <sf::Texture> &jumpingAnimation)
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

	jumpingAnimation[0].loadFromFile("Textures/Jump__000.png");
	jumpingAnimation[1].loadFromFile("Textures/Jump__001.png");
	jumpingAnimation[2].loadFromFile("Textures/Jump__002.png");
	jumpingAnimation[3].loadFromFile("Textures/Jump__003.png");
	jumpingAnimation[4].loadFromFile("Textures/Jump__004.png");
	jumpingAnimation[5].loadFromFile("Textures/Jump__005.png");
	jumpingAnimation[6].loadFromFile("Textures/Jump__006.png");
	jumpingAnimation[7].loadFromFile("Textures/Jump__007.png");
	jumpingAnimation[8].loadFromFile("Textures/Jump__008.png");
	jumpingAnimation[9].loadFromFile("Textures/Jump__009.png");
}
