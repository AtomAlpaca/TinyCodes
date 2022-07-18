#include <iostream>
#include <chrono>
#include <thread>

inline void clear()
{
    std::cout << "\033c";
    return ;
}

class Cell
{
	private:
		bool isAlive;
		bool isNeedUpdate;
	public:
		Cell();
		Cell(bool alive);
		void updateCell();
		bool getIsAlive();
		void tagNeedUpdate(bool need);
		bool getIsNeedUpdate();
};

Cell::Cell()
{
	this -> isAlive = false;
	return ;
}

Cell::Cell(bool alive)
{
	(this -> isAlive) = alive;
	return ;
}

void Cell::updateCell()
{
	this -> isAlive = ! (this -> isAlive);
	return ;
}

bool Cell::getIsAlive()
{
	return (this -> isAlive);
}

void Cell::tagNeedUpdate(bool need)
{
	this -> isNeedUpdate = need;
	return ;
}

bool Cell::getIsNeedUpdate()
{
	return this -> isNeedUpdate;
}

struct Coordinate
{
	int x, y;
};

class Map
{
	private:
		const long defaultHeigth = 20;
		const long defaultLength = 20;
		long Heigth;
		long Length;
		Cell ** gameMap;
	public:
		Map();
		Map(int x, int y);
		~Map();
		int countCellAround(int x, int y);
		void checkMap();
		void updateMap();
		void printMap();
		void initMap(Coordinate * coordinates, int num);
};

Map::Map(int x, int y)
{
	this -> Length = y;
	this -> Heigth = x;
	this -> gameMap = new Cell * [y + 5];
	for (int index = 0; index < y + 5; ++index)
	{
		gameMap[index] = new Cell [x + 5];
	}
}

Map::Map()
{
	Heigth = defaultHeigth;
	Length = defaultLength;
	std::clog << "Using default settings" << std::endl;
	this -> gameMap = new Cell * [defaultLength + 5];
	for (int index = 0; index < defaultLength + 5; ++index)
	{
		gameMap[index] = new Cell [defaultHeigth + 5];
	}

}

Map::~Map()
{
	delete [] gameMap;
}

int Map::countCellAround(int x, int y)
{
	long sum = 0;
	sum += int(this -> gameMap[x - 1][y - 1].getIsAlive());
	sum += int(this -> gameMap[x - 1][y    ].getIsAlive());
	sum += int(this -> gameMap[x - 1][y + 1].getIsAlive());
	sum += int(this -> gameMap[x    ][y - 1].getIsAlive());
	sum += int(this -> gameMap[x    ][y + 1].getIsAlive());
	sum += int(this -> gameMap[x + 1][y - 1].getIsAlive());
	sum += int(this -> gameMap[x + 1][y    ].getIsAlive());
	sum += int(this -> gameMap[x + 1][y + 1].getIsAlive());
	return sum;
}

void Map::checkMap()
{
	for (int i = 1; i <= this -> Length; ++i)
	{
		for (int j = 1; j <= this -> Heigth; ++j)
		{
			const int  num 		= countCellAround(i, j);
			const bool alive 	= this -> gameMap[i][j].getIsAlive();
			if (   ( alive and num <  2)
				or ( alive and num >  3)
				or (!alive and num == 3))
			{
				this -> gameMap[i][j].tagNeedUpdate(true);
			}
			else
			{
				this -> gameMap[i][j].tagNeedUpdate(false);
			}
		}
	}
	return ;
}

void Map::updateMap()
{
	for (int i = 1; i <= this -> Length; ++i)
	{
		for (int j = 1; j <= this -> Heigth; ++j)
		{
			if (this -> gameMap[i][j].getIsNeedUpdate())
			{
				this -> gameMap[i][j].updateCell();
			}
		}
	}
	return ;
}

void Map::printMap()
{
	for (int i = 1; i <= (this -> Length); ++i)
	{
		for (int j = 1; j <= (this -> Heigth); ++j)
		{
			if (this -> gameMap[i][j].getIsAlive())
			{
				std::cout << '@';
			}
			else
			{
				std::cout << '.';
			}
		}
		std::cout << std::endl;
	}
	return ;
}

void Map::initMap(Coordinate * coordinates, int num)
{
	for (int i = 0; i < num; ++i)
	{
		gameMap[coordinates[i].y][coordinates[i].x].updateCell();
	}
	return ;
}

int main()
{
	Coordinate coor[25] = 
	{
		{5, 5},
		{6, 5},
		{7, 5},
		{6, 6},
		{6, 7},
		{5, 8},
		{6, 8},
		{7, 8},
		{5, 10},
		{6, 10},
		{7, 10},
		{5, 11},
		{6, 11},
		{7, 11},
		{5, 13},
		{6, 13},
		{7, 13},
		{6, 14},
		{6, 15},
		{5, 16},
		{6, 16},
		{7, 16}
	};

	Map map(11, 20);
	map.initMap(coor, 22);

	char ch;

	while (true)
	{
		clear();
		map.printMap();
		map.checkMap();
		map.updateMap();
		std::this_thread::sleep_for(std::chrono::microseconds(1000000));
	}

	return 0;
}
