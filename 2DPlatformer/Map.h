#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <functional>
#include <chrono>

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
	void GenerateRoom(int length, int width, sf::Vector2i roomOrigin);
	void GenerateHallway(sf::Vector2i originPoint, sf::Vector2i endPoint);

	bool checkIfAdjancentSquares(sf::Vector2i currentSpace, sf::Vector2i nextSpace, std::vector <sf::Vector2i> previousSpaces);

	int random_int_in_range(int first, int last);

public:

	const static int mapX = 100;
	const static int mapY = 100;

	int startX, startY, finishX, finishY;

	std::vector<sf::RectangleShape> blockArray;
	std::vector<sf::FloatRect> blockBoundingBox;
	int Xoffset = 100;
	int Yoffset = 100;

	const int hallwayIndex = 10;

	sf::Vector2f playerStart;

	int levelArray[mapX][mapY];
	


	//const int levelArray[mapX][mapY] = {
	//{ 1, 1, 1, 1, 1 },
	//{ 1, 9, 0, 0, 1 },
	//{ 1, 1, 1, 0, 1 },
	//{ 1, 8, 0, 0, 1 },
	//{ 1, 1, 1, 1, 1 } };
};


