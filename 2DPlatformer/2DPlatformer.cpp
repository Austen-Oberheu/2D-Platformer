// 2DPlatformer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

void levelEditor(std::vector<sf::RectangleShape> &blockArray, std::vector<sf::FloatRect> &blockBoundingBox, sf::Vector2i mousePos)
{
	sf::RectangleShape block(sf::Vector2f(100.f, 25.f));
	block.setPosition(mousePos.x, mousePos.y);
	sf::FloatRect boxCollision = block.getGlobalBounds();
	blockBoundingBox.push_back(boxCollision);
	blockArray.push_back(block);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Platformer");
	window.setFramerateLimit(144);
	sf::Sprite playerSprite;

	std::vector <sf::Texture> idleAnimation(10);
	std::vector <sf::Texture> walkingAnimation(10);
	std::vector <sf::Texture> jumpingAnimation(10);

	Player player(playerSprite);
	player.textureInit(idleAnimation, walkingAnimation, jumpingAnimation);


	sf::Clock clock;
	sf::Clock frameTime;
	float lastTime = 0;

	sf::Font font;
	if (!font.loadFromFile("Fonts/HVR.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);

	//draw level
	const int levelWidth = 5;
	const int levelHeight = 5;

	int levelArray[levelHeight][levelWidth] = {
	{ 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1 } };
	std::vector<sf::RectangleShape> blockArray;
	std::vector<sf::FloatRect> blockBoundingBox;
	int Xoffset = 101;
	int Yoffset = 26;

	for (int y = 0; y < levelHeight; y++)
	{
		for (int x = 0; x < levelWidth; x++)
		{
			sf::RectangleShape block(sf::Vector2f(100.f, 25.f));
			block.setPosition(x * Xoffset, 600 + (y * Yoffset));
			sf::FloatRect boxCollision = block.getGlobalBounds();
			blockBoundingBox.push_back(boxCollision);
			blockArray.push_back(block);
		}
	}

	//playerSprite.setOrigin(playerSprite.getTextureRect().width / 2, playerSprite.getTextureRect().height / 2);
	
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

		}
		playerSprite = player.playerSpriteUpdate(playerSprite, idleAnimation, walkingAnimation, jumpingAnimation, deltaTime, playerSprite.getOrigin());
		
		player.Update(playerSprite, deltaTime, blockBoundingBox, playerSprite.getOrigin());
		

		sf::Vertex line[] =
		{
			sf::Vertex(playerSprite.getPosition()),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y + 50))
		};

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i localPos = sf::Mouse::getPosition(window);
			levelEditor(blockArray, blockBoundingBox, localPos);
		}

		float currentTime = frameTime.restart().asSeconds();
		int fps = 1.f / currentTime;
		lastTime = currentTime;
		
		
		//playerSprite.setOrigin(playerSprite.getTextureRect().width / 2, playerSprite.getTextureRect().height / 2);
		text.setString(std::to_string(fps));
		/*sf::IntRect debugRect = playerSprite.getTextureRect();
		sf::RectangleShape debugRectangle(sf::Vector2f(debugRect.left, debugRect.top));
		debugRectangle.setFillColor(sf::Color::Green);*/

		window.clear();
		window.draw(playerSprite);
		window.draw(line, 2, sf::Lines);
		window.draw(text);
		for (int i = 0; i < blockArray.size(); i++)
		{
			window.draw(blockArray[i]);
		}

		window.display();
	}

	return 0;
}