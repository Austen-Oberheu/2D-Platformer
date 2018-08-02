#include "stdafx.h"
#include "Player.h"


Player::Player(sf::Sprite &playerShape, sf::Vector2f playerStart)
{
	playerShape.setPosition(playerStart.x, playerStart.y);
	playerShape.setScale(.2f, .2f);

	velocity.x = 0; 
	velocity.y = 0;
	lastPosition.push_back(sf::Vector2f(playerShape.getPosition().x, playerShape.getPosition().y));
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

void Player::Update(sf::Sprite &playerShape, float deltaTime, int (&map)[100][100], /*std::vector<sf::RectangleShape>& blockBoundingBox,*/ sf::Vector2f origin, sf::Vertex ($bottomLine)[3][2], sf::Vertex ($rightLine)[3][2], sf::Vertex ($leftLine)[3][2], sf::Vertex ($upLine)[3][2], bool &jumpVariable)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (velocity.x < maxHorizontalVelocity)
		{
			velocity.x += 50;
		}
		walking = true;
		walkingRight = true;
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
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
			allowedToDoubleJump = true;
			jumping = true;
			falling = true;
			bottomCollision = false;
			clock.restart();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && allowedToJump == false && clock.getElapsedTime().asMilliseconds() > 250)
	{
		if (allowedToDoubleJump == true)
		{
			velocity.y = 0;
			velocity.y -= 1500;
			allowedToJump = false;
			allowedToDoubleJump = false;
			jumping = true;
			falling = true;
			releasedSpaceKey = false;
		}
	}


	
	/*if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
	}*/
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		walking = false;
		if (velocity.x < 0)
		{
			velocity.x += 50;
		}
		if (velocity.x > 0)
		{
			velocity.x -= 50;
		}
	}

	//New Collision Code, takes the ray traces and just uses their farthest out point and checks if they collide with any of the tiles that the character is touching
	//And if so check what kind of tile, if it is a solid one it causes a collision

	sf::Vector2i bottomPoint;
	sf::Vector2i bottomRightPoint;
	sf::Vector2i bottomLeftPoint;

	sf::Vector2i rightPoint;
	sf::Vector2i leftPoint;
	sf::Vector2i topPoint;

	
	bottomPoint = sf::Vector2i($bottomLine[0][1].position.x / 48, $bottomLine[0][1].position.y / 48);
	bottomRightPoint = sf::Vector2i($bottomLine[2][1].position.x / 48, $bottomLine[2][1].position.y / 48);
	bottomLeftPoint = sf::Vector2i($bottomLine[1][1].position.x / 48, $bottomLine[1][1].position.y / 48);

	rightPoint = sf::Vector2i($rightLine[1][1].position.x / 48, $rightLine[1][1].position.y / 48);
	leftPoint = sf::Vector2i($leftLine[1][1].position.x / 48, $leftLine[1][1].position.y / 48);
	topPoint = sf::Vector2i($upLine[1][1].position.x / 48, $upLine[1][1].position.y / 48);
	
	bottom = playerShape.getPosition().y + playerShape.getGlobalBounds().height;
	left = playerShape.getPosition().x;
	right = playerShape.getPosition().x + playerShape.getGlobalBounds().width;
	top = playerShape.getPosition().y;

	topTiles.clear();
	leftTiles.clear();
	rightTiles.clear();
	bottomTiles.clear();
	bottomRightTiles.clear();
	bottomLeftTiles.clear();

	if (std::find(topTiles.begin(), topTiles.end(), topPoint) == topTiles.end()) topTiles.push_back(topPoint);
	if (std::find(rightTiles.begin(), rightTiles.end(), rightPoint) == rightTiles.end()) rightTiles.push_back(rightPoint);
	if (std::find(bottomTiles.begin(), bottomTiles.end(), bottomPoint) == bottomTiles.end()) bottomTiles.push_back(bottomPoint);
	if (std::find(leftTiles.begin(), leftTiles.end(), leftPoint) == leftTiles.end()) leftTiles.push_back(leftPoint);

	if (std::find(bottomLeftTiles.begin(), bottomLeftTiles.end(), bottomLeftPoint) == bottomLeftTiles.end()) bottomLeftTiles.push_back(bottomLeftPoint);
	if (std::find(bottomRightTiles.begin(), bottomRightTiles.end(), bottomRightPoint) == bottomRightTiles.end()) bottomRightTiles.push_back(bottomRightPoint);

	bool secondaryBottomCollsion = false;

	for (int i = 0; i < bottomTiles.size(); i++)
	{
		if (map[bottomTiles[i].y][bottomTiles[i].x] == 1)
		{
			
			
			
			//playerShape.setPosition(playerShape.getPosition().x, lastPosition.front().y);
			//lastPosition.pop_front();
			bottomCollision = true;
			break;
		}
		else
		{
			bottomCollision = false;
			falling = true;
		}
	}

	for (int i = 0; i < bottomRightTiles.size(); i++) 
	{
		if (map[bottomRightTiles[i].y][bottomRightTiles[i].x] == 1)
		{
			jumping = false;
			allowedToJump = true;
			hasDoubleJumped = false;
			falling = false;
			velocity.y = 0;
			secondaryBottomCollsion = true;
		}
	}

	for (int i = 0; i < bottomLeftTiles.size(); i++)
	{
		if (map[bottomLeftTiles[i].y][bottomLeftTiles[i].x] == 1)
		{
			jumping = false;
			allowedToJump = true;
			hasDoubleJumped = false;
			falling = false;
			velocity.y = 0;
			secondaryBottomCollsion = true;
		}
	}



	if (bottomCollision == true && secondaryBottomCollsion == false)
	{
		falling == false;
	}
	else if (bottomCollision == true && secondaryBottomCollsion == true)
	{
		playerShape.setPosition(playerShape.getPosition().x, lastPosition.front().y);
		lastPosition.pop_front();
	}

	if (falling == true && velocity.y < maxVerticalVelocity)
	{
		velocity.y += 50;
	}

	jumpVariable = allowedToJump;


	playerShape.setOrigin(origin);
	//std::cout << "x: " << velocity.x << " y: " << velocity.y << std::endl;
	lastPosition.push_front(sf::Vector2f(playerShape.getPosition().x, playerShape.getPosition().y));
	if (lastPosition.size() > 50)
	{
		lastPosition.pop_back();
	}
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
