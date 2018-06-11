#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	GenerateMap();
}


Map::~Map()
{
}

void Map::GenerateMap()
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 6);
	int dice_roll = distribution(generator);

	auto dice = std::bind(distribution, generator);



	for (int y = 1; y < mapY - 1; y++)
	{
		for (int x = 1; x < mapX - 1; x++)
		{
			levelArray[y][x] = dice();
		}
	}

	for (int y = 0; y < mapY; y++)
	{
		levelArray[y][0] = 1;
	}
	for (int x = 0; x < mapX; x++)
	{
		levelArray[0][x] = 1;
	}
	for (int y = 0; y < mapY; y++)
	{
		levelArray[y][mapX-1] = 1;
	}
	for (int x = 0; x < mapX; x++)
	{
		levelArray[mapY-1][x] = 1;
	}


	levelArray[5][5] = 8;
	levelArray[10][10] = 9;

	
}

std::vector<sf::RectangleShape> Map::DrawMap()
{

	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			if (levelArray[y][x] == 1)
			{
				sf::RectangleShape block(sf::Vector2f(100.f, 100.f));
				block.setPosition(x * Xoffset, 600 + (y * Yoffset));
				sf::FloatRect boxCollision = block.getGlobalBounds();
				blockBoundingBox.push_back(boxCollision);
				blockArray.push_back(block);
			}
			if (levelArray[y][x] == 8)
			{
				playerStart.x = x * Xoffset;
				playerStart.y = 600 + (y * Yoffset);
			}
			
		}
	}

	return blockArray;
}

std::vector<sf::FloatRect> Map::MapBoundingBox()
{
	return blockBoundingBox;
}

sf::Vector2f Map::PlayerStart()
{
	return playerStart;
}

bool Map::CheckMapSolvable()
{
	std::map<std::pair<int, int>, int> pathableSpaces;
	//find the start and end position
	for (int x = 0; x < mapX; x++)
	{
		for (int y = 0; y < mapY; y++)
		{
			if (levelArray[y][x] == 8)
			{
				startX = x;
				startY = y;
				pathableSpaces[std::make_pair(x, y)] = 2;
			}
			if (levelArray[y][x] == 9)
			{
				finishX = x;
				finishY = y;
				pathableSpaces[std::make_pair(x, y)] = 3;
			}
			if (levelArray[y][x] == 0)
			{
				pathableSpaces[std::make_pair(x, y)] = 1;
			}
		}
	}
	int numberSteps = 0;
	sf::Vector2i currentSpace = sf::Vector2i(startX, startY);
	sf::Vector2i endSpace = sf::Vector2i(finishX, finishY);
	bool potentialSpaces = true;
	bool solution = false;
	while (potentialSpaces == true && solution == false)
	{
		//is marked false by default so a space must be found to keep looping.
		potentialSpaces = false;
		//mark any spaces adjancent to the current space as reachable
		if (pathableSpaces[std::make_pair(currentSpace.x + 1, currentSpace.y)] != NULL && pathableSpaces[std::make_pair(currentSpace.x + 1, currentSpace.y)] != 3)
		{
			pathableSpaces[std::make_pair(currentSpace.x + 1, currentSpace.y)] = 9;
		}
		if (pathableSpaces[std::make_pair(currentSpace.x, currentSpace.y + 1)] != NULL && pathableSpaces[std::make_pair(currentSpace.x, currentSpace.y + 1)] != 3)
		{
			pathableSpaces[std::make_pair(currentSpace.x, currentSpace.y + 1)] = 9;
		}
		if (pathableSpaces[std::make_pair(currentSpace.x - 1, currentSpace.y)] != NULL && pathableSpaces[std::make_pair(currentSpace.x - 1, currentSpace.y)] != 3)
		{
			pathableSpaces[std::make_pair(currentSpace.x - 1, currentSpace.y)] = 9;
		}
		if (pathableSpaces[std::make_pair(currentSpace.x, currentSpace.y - 1)] != NULL && pathableSpaces[std::make_pair(currentSpace.x, currentSpace.y - 1)] != 3)
		{
			pathableSpaces[std::make_pair(currentSpace.x, currentSpace.y - 1)] = 9;
		}

		if (pathableSpaces[std::make_pair(currentSpace.x + 1, currentSpace.y)] == 3)
		{
			std::cout << "solution found in " << numberSteps << " number of steps" << std::endl;
			solution = true;
			return true;
		}
		if (pathableSpaces[std::make_pair(currentSpace.x, currentSpace.y + 1)] == 3)
		{
			std::cout << "solution found in " << numberSteps << " number of steps" << std::endl;
			solution = true;
			return true;
		}
		if (pathableSpaces[std::make_pair(currentSpace.x - 1, currentSpace.y)] == 3)
		{
			std::cout << "solution found in " << numberSteps << " number of steps" << std::endl;
			solution = true;
			return true;
		}
		if (pathableSpaces[std::make_pair(currentSpace.x, currentSpace.y - 1)] == 3)
		{
			std::cout << "solution found in " << numberSteps << " number of steps" << std::endl;
			solution = true;
			return true;
		}
		//Mark the current space as already searched
		pathableSpaces.erase (std::make_pair(currentSpace.x, currentSpace.y));

		for (auto const& x : pathableSpaces)
		{
			if (x.second == 9)
			{
				//This horrendous line asigns the current space to the first space found that is reachable from the current space
				//and the weirdness is due to using std::pair for the key, so first.first is the x value and first.second the y
				currentSpace = sf::Vector2i(x.first.first, x.first.second);
				potentialSpaces = true;
			}
		}
		numberSteps++;
	}


	return false;
}
