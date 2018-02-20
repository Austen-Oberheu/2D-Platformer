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

	std::vector <sf::Texture> playerTexture(10);
	playerTexture[0].loadFromFile("Textures/Idle__000.png");
	playerTexture[1].loadFromFile("Textures/Idle__001.png");
	playerTexture[2].loadFromFile("Textures/Idle__002.png");
	playerTexture[3].loadFromFile("Textures/Idle__003.png");
	playerTexture[4].loadFromFile("Textures/Idle__004.png");
	playerTexture[5].loadFromFile("Textures/Idle__005.png");
	playerTexture[6].loadFromFile("Textures/Idle__006.png");
	playerTexture[7].loadFromFile("Textures/Idle__007.png");
	playerTexture[8].loadFromFile("Textures/Idle__008.png");
	playerTexture[9].loadFromFile("Textures/Idle__009.png");
	

	Player player(playerSprite, playerTexture[0]);

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

		
		player.Update(playerSprite, deltaTime, blockBoundingBox);
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
		
		playerSprite = player.playerSpriteUpdate(playerSprite, playerTexture, deltaTime);

		text.setString(std::to_string(fps));
		
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