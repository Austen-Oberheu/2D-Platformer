#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <functional>

#include "SFML/Graphics.hpp"

class Map
{
public:
	Map();
	~Map();

	void GenerateMap();
	std::vector<sf::RectangleShape> DrawMap();
	std::vector<sf::FloatRect> MapBoundingBox();
	sf::Vector2f PlayerStart();
	bool CheckMapSolvable();

public:

	const static int mapX = 25;
	const static int mapY = 25;

	int startX, startY, finishX, finishY;

	std::vector<sf::RectangleShape> blockArray;
	std::vector<sf::FloatRect> blockBoundingBox;
	int Xoffset = 100;
	int Yoffset = 100;

	sf::Vector2f playerStart;

	int levelArray[mapX][mapY];
	


	//const int levelArray[mapX][mapY] = {
	//{ 1, 1, 1, 1, 1 },
	//{ 1, 9, 0, 0, 1 },
	//{ 1, 1, 1, 0, 1 },
	//{ 1, 8, 0, 0, 1 },
	//{ 1, 1, 1, 1, 1 } };
};


