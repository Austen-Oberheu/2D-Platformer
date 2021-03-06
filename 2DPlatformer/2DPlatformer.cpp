// 2DPlatformer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include "Map.h"
#include "TileMap.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Platformer");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::Sprite playerSprite;

	std::vector <sf::Texture> idleAnimation(10);
	std::vector <sf::Texture> walkingAnimation(10);
	std::vector <sf::Texture> jumpingAnimation(10);

	sf::Shader shader;

	Map map;

	sf::Vector2f playerStart = map.PlayerStart();

	TileMap tileMap;

	tileMap.load("Textures/tiles.png", sf::Vector2u(48, 48), map.ReturnMap(), 100, 100);

	sf::View view;
	view.setSize(1920, 1080);
	view.setCenter(playerStart.x, playerStart.y);
	window.setView(view);

	Player player(playerSprite, playerStart);
	player.textureInit(idleAnimation, walkingAnimation, jumpingAnimation);


	if (!shader.loadFromFile("Shaders/fragment_shader.frag", sf::Shader::Fragment))
	{
		std::cout << "Could not load fragment shader!" << std::endl;
	}
	shader.setUniform("texture", sf::Shader::CurrentTexture);


	sf::Clock clock;
	sf::Clock frameTime;
	sf::Clock deltaClock;

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

	sf::Text debugText;
	debugText.setFont(font);
	debugText.setCharacterSize(16);
	debugText.setFillColor(sf::Color::White);
	debugText.setPosition(200, 0);

	float pixelate = 0.95f;
	
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

		}
		playerSprite = player.playerSpriteUpdate(playerSprite, idleAnimation, walkingAnimation, jumpingAnimation, deltaTime, playerSprite.getOrigin());

		float currentTime = frameTime.restart().asSeconds();
		int fps = 1.f / currentTime;
		lastTime = currentTime;


		std::string fpsString = std::string("FPS: ") + std::to_string(fps);

		char const *fps_char = fpsString.c_str();

		std::string vyString = std::string("Velocity.y: ") + std::to_string(player.velocity.y);

		char const *velY = vyString.c_str();

		std::string vxString = std::string("Velocity.x: ") + std::to_string(player.velocity.x);

		char const *velX = vxString.c_str();

		std::string wallSlideString = std::string("WallSliding: ") + std::to_string(player.wallSliding);

		char const *wallSlide = wallSlideString.c_str();

		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::Begin("Debug Info");
		ImGui::Text(fps_char);
		ImGui::Text(velY);
		ImGui::Text(velX);
		ImGui::Text(wallSlide);
		ImGui::End();

		//debug
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			playerSprite.setPosition(map.PlayerStart());
		}
		

		sf::Vertex topLine[3][2] =
		{
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + 50)),

			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width + 35) / 2, playerSprite.getPosition().y)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width + 35) / 2, playerSprite.getPosition().y + 50)),

			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width  - 25) / 2, playerSprite.getPosition().y)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width - 25) / 2, playerSprite.getPosition().y + 50))
		};
		sf::Vertex bottomLine[3][2] =
		{
			//Middle Bottom Line
			{sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + 100))},
			//Middle Right Line
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width + 35) / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width + 35) / 2, playerSprite.getPosition().y + 93)) },
			//Middle Left Line
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width - 25) / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width - 25) / 2, playerSprite.getPosition().y + 93)) },

		};
		sf::Vertex rightLine[3][2] =
		{
			//Middle Right Line
			{sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + 65, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2))},
			//Bottom Right Line
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height + 50) / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height + 50) / 2)) },
			//Top Right Lin
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height - 35) / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height - 35) / 2)) },
		};
		sf::Vertex leftLine[3][2] =
		{
			//Middle Left Line
			{sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2))},
			//Bottom Left Line
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height + 50) / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x - (playerSprite.getGlobalBounds().width - 80), playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height + 50) / 2)) },
			//Top Left Line
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height - 35) / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x - (playerSprite.getGlobalBounds().width - 80), playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height - 35) / 2)) },

		};

		player.Update(playerSprite, deltaTime, map.levelArray, /*blockArray,*/ playerSprite.getOrigin(), bottomLine, rightLine, leftLine, topLine);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			view.zoom(1.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			view.zoom(0.9f);
		}
		view.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);

		shader.setUniform("pixel_threshold", pixelate / 30);

		
		window.clear();
		window.draw(tileMap);
		window.draw(playerSprite, &shader);
		//window.draw(topLine[0], 2, sf::Lines);
		//window.draw(topLine[1], 2, sf::Lines);
		//window.draw(topLine[2], 2, sf::Lines);
		//window.draw(bottomLine[0], 2, sf::Lines);
		//window.draw(bottomLine[1], 2, sf::Lines);
		//window.draw(bottomLine[2], 2, sf::Lines);
		//window.draw(rightLine[0], 2, sf::Lines);
		//window.draw(rightLine[1], 2, sf::Lines);
		//window.draw(rightLine[2], 2, sf::Lines);
		//window.draw(leftLine[0], 2, sf::Lines);
		//window.draw(leftLine[1], 2, sf::Lines);
		//window.draw(leftLine[2], 2, sf::Lines);
		window.setView(view);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}


