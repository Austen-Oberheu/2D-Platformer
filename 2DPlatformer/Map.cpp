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
	GenerateRoom(5, 10, sf::Vector2i(0, 0));
	GenerateRoom(5, 15, sf::Vector2i(40, 18));

	GenerateHallway(sf::Vector2i(50, 50), sf::Vector2i(0, 0));

	/*GenerateRoom(20, 20, sf::Vector2i(0, 0));
	levelArray[5][5] = 8;
	levelArray[10][10] = 9;*/

	//std::default_random_engine generator;
	//generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	//std::uniform_int_distribution<int> distribution(1, 6);
	//std::uniform_int_distribution<int> roomDistribution(1, 90);

	////do {
	//	int dice_roll = distribution(generator);
	//	int room_roll = roomDistribution(generator);

	//	auto dice = std::bind(distribution, generator);
	//	auto room_dice = std::bind(roomDistribution, generator);

	//	for (int y = 1; y < mapY - 1; y++)
	//	{
	//		for (int x = 1; x < mapX - 1; x++)
	//		{
	//			int roomLength = dice() * 2;
	//			int roomWidth = dice() * 2;
	//			int roomPosX = room_dice();
	//			int roomPosY = room_dice();

	//			levelArray[y][x] = room_dice();

	//			if (levelArray[y][x] == 1)
	//			{
	//				
	//				GenerateRoom(roomLength, roomWidth, sf::Vector2i(roomPosX, roomPosY));
	//			}
	//			else 
	//			{				
	//				levelArray[y][x] = 0;
	//			}
	//		}
	//	}



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
			levelArray[y][mapX - 1] = 1;
		}
		for (int x = 0; x < mapX; x++)
		{
			levelArray[mapY - 1][x] = 1;
		}


		levelArray[2][2] = 8;
		levelArray[20][50] = 9;

		/*auto t1 = std::chrono::high_resolution_clock::now();
		CheckMapSolvable();
		auto t2 = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

		std::cout << "Maze took " << duration << " to solve" << std::endl;*/
	//} while (!CheckMapSolvable());
	
}

std::vector<sf::RectangleShape> Map::DrawMap()
{

	
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
	std::cout << "Number of Steps: " << numberSteps << std::endl;
	std::cout << "No Solution Found!" << std::endl;
	return false;
}

void Map::GenerateRoom(int length, int width, sf::Vector2i roomOrigin)
{
	//Top line of room
	for (int x = 0; x < width; x++)
	{
		if ((roomOrigin.x + x) < mapX && roomOrigin.x > (mapX - mapX))
		{
			levelArray[roomOrigin.y][roomOrigin.x + x] = 1;
		}
	}
	//Bottom line of room
	for (int x = 0; x < width; x++)
	{
		if ((roomOrigin.x + x) < mapX && (roomOrigin.y + length) < mapY)
		{
			levelArray[roomOrigin.y + length][roomOrigin.x + x] = 1;
		}
	}
	//Left side of room
	for (int x = 0; x < length; x++)
	{
		if ((roomOrigin.y + x) < mapY && roomOrigin.y > (mapY - mapY))
		{
			levelArray[roomOrigin.y + x][roomOrigin.x] = 1;
		}
	}
	//Right side of room
	for (int x = 0; x < length + 1; x++)
	{
		if ((roomOrigin.y + x) < mapY && (roomOrigin.y + x) > (mapY - mapY))
		{
			levelArray[roomOrigin.y + x][roomOrigin.x + width] = 1;
		}
	}

}

void Map::GenerateHallway(sf::Vector2i originPoint, sf::Vector2i endPoint)
{
	enum CardinalDirections
	{
		north = 1,
		south,
		east,
		west
	};

	std::default_random_engine generator;
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distribution(1, 10);

	int dice_roll = distribution(generator);

	auto dice = std::bind(distribution, generator);


	sf::Vector2i currentSpace = originPoint;
	std::vector <sf::Vector2i> previousSpaces;
	previousSpaces.push_back(sf::Vector2i(NULL, NULL));
	previousSpaces.push_back(sf::Vector2i(NULL, NULL));
	sf::Vector2i nextSpace;
	int stuckCounter = 0;
	bool deadEnd = false;
	
	int direction = random_int_in_range(north, west);
	while(deadEnd == false && stuckCounter < 50)
	{
		//Small chance that the hallway will change direction
		int changeDirection = dice();
		if (changeDirection == 7)
		{
			direction = random_int_in_range(north, west);
		}

		if (direction == north)
		{
			if (levelArray[currentSpace.y - 1][currentSpace.x] == 0)
			{
				nextSpace.x = currentSpace.x;
				nextSpace.y = currentSpace.y - 1;

				if (checkIfAdjancentSquares(currentSpace, nextSpace, previousSpaces))
				{
					levelArray[currentSpace.y - 1][currentSpace.x] = 1;
					previousSpaces.emplace(previousSpaces.begin(), currentSpace);
					if (previousSpaces.size() > 2)
						previousSpaces.pop_back();

					currentSpace = sf::Vector2i(currentSpace.x, currentSpace.y - 1);
					stuckCounter = 0;
				}
		
			}
			else
			{
				if (levelArray[currentSpace.y][currentSpace.x + 1] == 0 && levelArray[currentSpace.y][currentSpace.x - 1] == 0)
				{
					int turn = random_int_in_range(1, 2);
					if (turn == 1)
					{
						direction = east;
					}
					else
					{
						direction = west;
					}
				}
				else if (levelArray[currentSpace.y][currentSpace.x + 1] == 0)
				{
					direction = east;
				}
				else if (levelArray[currentSpace.y][currentSpace.x - 1] == 0)
				{
					direction = west;
				}
				else
				{
					//No possible spaces
					deadEnd = true;
				}

			}

		}
		else if (direction == south)
		{
			if (levelArray[currentSpace.y + 1][currentSpace.x] == 0)
			{
				nextSpace.x = currentSpace.x;
				nextSpace.y = currentSpace.y + 1;

				if (checkIfAdjancentSquares(currentSpace, nextSpace, previousSpaces))
				{
					levelArray[currentSpace.y + 1][currentSpace.x] = 1;
					previousSpaces.emplace(previousSpaces.begin(), currentSpace);
					if (previousSpaces.size() > 2)
						previousSpaces.pop_back();

					currentSpace = sf::Vector2i(currentSpace.x, currentSpace.y + 1);
					stuckCounter = 0;
				}
			
			}
			else
			{
				if (levelArray[currentSpace.y][currentSpace.x + 1] == 0 && levelArray[currentSpace.y][currentSpace.x - 1] == 0)
				{
					int turn = random_int_in_range(1, 2);
					if (turn == 1)
					{
						direction = east;
					}
					else
					{
						direction = west;
					}
				}
				else if (levelArray[currentSpace.y][currentSpace.x + 1] == 0)
				{
					direction = east;
				}
				else if (levelArray[currentSpace.y][currentSpace.x - 1] == 0)
				{
					direction = west;
				}
				else
				{
					//No possible spaces
					deadEnd = true;
				}

			}

		}
		else if (direction == east)
		{
			if (levelArray[currentSpace.y][currentSpace.x + 1] == 0)
			{
				nextSpace.x = currentSpace.x + 1;
				nextSpace.y = currentSpace.y;

				if (checkIfAdjancentSquares(currentSpace, nextSpace, previousSpaces))
				{
					levelArray[currentSpace.y][currentSpace.x + 1] = 1;
					previousSpaces.emplace(previousSpaces.begin(), currentSpace);
					if (previousSpaces.size() > 2)
						previousSpaces.pop_back();

					currentSpace = sf::Vector2i(currentSpace.x + 1, currentSpace.y);
					stuckCounter = 0;
				}
			
			}
			else
			{
				if (levelArray[currentSpace.y + 1][currentSpace.x] == 0 && levelArray[currentSpace.y - 1][currentSpace.x] == 0)
				{
					int turn = random_int_in_range(1, 2);
					if (turn == 1)
					{
						direction = north;
					}
					else
					{
						direction = south;
					}
				}
				else if (levelArray[currentSpace.y + 1][currentSpace.x] == 0)
				{
					direction = south;
				}
				else if (levelArray[currentSpace.y - 1][currentSpace.x] == 0)
				{
					direction = north;
				}
				else
				{
					//No possible spaces
					deadEnd = true;
				}

			}

		}
		else if (direction == west)
		{
			if (levelArray[currentSpace.y][currentSpace.x - 1] == 0)
			{
				nextSpace.x = currentSpace.x - 1;
				nextSpace.y = currentSpace.y;

				if (checkIfAdjancentSquares(currentSpace, nextSpace, previousSpaces))
				{
					levelArray[currentSpace.y][currentSpace.x - 1] = 1;
					previousSpaces.emplace(previousSpaces.begin(), currentSpace);
					if (previousSpaces.size() > 2)
						previousSpaces.pop_back();

					currentSpace = sf::Vector2i(currentSpace.x - 1, currentSpace.y);
					stuckCounter = 0;
				}
			
			}
			else
			{
				if (levelArray[currentSpace.y + 1][currentSpace.x] == 0 && levelArray[currentSpace.y - 1][currentSpace.x] == 0)
				{
					int turn = random_int_in_range(1, 2);
					if (turn == 1)
					{
						direction = south;
					}
					else
					{
						direction = north;
					}
				}
				else if (levelArray[currentSpace.y - 1][currentSpace.x] == 0)
				{
					direction = north;
				}
				else if (levelArray[currentSpace.y + 1][currentSpace.x] == 0)
				{
					direction = south;
				}
				else
				{
					//No possible spaces
					deadEnd = true;
				}

			}

		}
		if (currentSpace.x + 1 > mapX || currentSpace.x - 1 < (mapX - mapX) || currentSpace.y + 1 > mapY || currentSpace.y - 1 < (mapY - mapY))
		{
			std::cout << "Hit Border with hallway" << std::endl;
			direction = random_int_in_range(north, west);
		}
		stuckCounter++;
		std::cout << currentSpace.x << " " << currentSpace.y << std::endl;
	}
}

const int * Map::ReturnMap()
{
	return *levelArray;
}

bool Map::checkIfAdjancentSquares(sf::Vector2i currentSpace, sf::Vector2i nextSpace, std::vector <sf::Vector2i> previousSpaces)
{
	//Set the current space to 2 so we know which space is the only one that should already have a value
	//But it will be changed back at the end
	levelArray[currentSpace.y][currentSpace.x] = 2;
	if (previousSpaces[0].x != NULL)
	{
		for (int i = 0; i < previousSpaces.size(); i++)
		{
			levelArray[previousSpaces[i].y][previousSpaces[i].x] = 3;
		}
	}

	//Checks all adjancent squares to see whether any already have a square and also skips the current square
	if (   (levelArray[nextSpace.y - 1][nextSpace.x - 1] == 0 || levelArray[nextSpace.y - 1][nextSpace.x - 1] == 3) && (levelArray[nextSpace.y - 1][nextSpace.x] == 0 || levelArray[nextSpace.y - 1][nextSpace.x] == 2 || levelArray[nextSpace.y - 1][nextSpace.x] == 3)
		&& (levelArray[nextSpace.y - 1][nextSpace.x + 1] == 0 || levelArray[nextSpace.y - 1][nextSpace.x + 1] == 3) && (levelArray[nextSpace.y][nextSpace.x + 1] == 0 || levelArray[nextSpace.y][nextSpace.x + 1] == 2 || levelArray[nextSpace.y][nextSpace.x + 1] == 3)
		&& (levelArray[nextSpace.y + 1][nextSpace.x + 1] == 0 || levelArray[nextSpace.y + 1][nextSpace.x + 1] == 3) && (levelArray[nextSpace.y + 1][nextSpace.x] == 0 || levelArray[nextSpace.y + 1][nextSpace.x] == 2 || levelArray[nextSpace.y + 1][nextSpace.x] == 3)
		&& (levelArray[nextSpace.y + 1][nextSpace.x - 1] == 0 || levelArray[nextSpace.y + 1][nextSpace.x - 1] == 3) && (levelArray[nextSpace.y][nextSpace.x - 1] == 0 || levelArray[nextSpace.y][nextSpace.x - 1] == 2 || levelArray[nextSpace.y][nextSpace.x - 1] == 3))
	{
		levelArray[currentSpace.y][currentSpace.x] = 1;
		for (int i = 0; i < previousSpaces.size(); i++)
		{
			levelArray[previousSpaces[i].y][previousSpaces[i].x] = 1;
		}
		return true;
	}
	levelArray[currentSpace.y][currentSpace.x] = 1;
	for (int i = 0; i < previousSpaces.size(); i++)
	{
		levelArray[previousSpaces[i].y][previousSpaces[i].x] = 1;
	}
	return false;
}

int Map::random_int_in_range(int first, int last)
{
	/* This function implements the method recommended by the knowing
	* folks at comp.lang.c: http://c-faq.com/lib/randrange.html
	* Returns an integer in [first, last].
	*/
	unsigned int N = (last - first <= RAND_MAX)  /* Make sure the algorithm    */
		? (last - first + 1U)         /* terminates by keeping N    */
		: (RAND_MAX + 1U);            /* in rand()'s maximum range. */
	unsigned int x = (RAND_MAX + 1U) / N;
	unsigned int y = x * N;
	unsigned int r;
	do {
		r = rand();
	} while (r >= y);
	return r / x + first;
}