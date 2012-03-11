#include "MonsterGenerator.hpp"
#include <algorithm>


MonsterGenerator::MonsterGenerator(int seed)
	: _maxId(0), _leftFrequency(20), _rightFrequency(20), _upFrequency(1), _squadLevelSpeed(4), _nbSquads(0), _nbSquadsMax(10), _squadTime(10), _rand(seed), _elapsedTime(0),
	_inMaze(true), _tmpY(this->_y), _wallSize(180), _position(1), _lastPosition(_position), _mazeY(0)
{
}

MonsterGenerator::~MonsterGenerator()
{
}

Core::Resource    *MonsterGenerator::clone() const
{
	return (new MonsterGenerator(*this));
}

void	MonsterGenerator::move(double time)
{
	this->generate(time);
	this->Map::move(time);
}

void	MonsterGenerator::addRandomBoss(std::string const &name, bool scrollable, size_t level)
{
	this->_bosses.push_back(MonsterInfo(level, name, scrollable));
}

void	MonsterGenerator::addRandomMonster(std::string const &name, bool scrollable, size_t level)
{
	this->_randMonsters.push_back(MonsterInfo(level, name, scrollable));
	std::sort(this->_randMonsters.begin(), this->_randMonsters.end());
}

void	MonsterGenerator::addRandomWall(std::string const &name, bool scrollable, size_t level)
{
	this->_walls.push_back(MonsterInfo(level, name, scrollable));
	std::sort(this->_walls.begin(), this->_walls.end());
}

void	MonsterGenerator::addRandomBreakableWall(std::string const &name, bool scrollable, size_t level)
{
	this->_breakableWalls.push_back(MonsterInfo(level, name, scrollable));
	std::sort(this->_breakableWalls.begin(), this->_breakableWalls.end());
}

void	MonsterGenerator::createWall(MonsterInfo const &info, int x, int y)
{
	this->addElem("spawnspawner", info.name, (x * this->_wallSize) - 100, this->_tmpY + 100, 0, 0, info.scrollable, false, -320 - y * this->_wallSize);
}

void	MonsterGenerator::createMonster(MonsterInfo const &info)
{
	this->addElem("spawnspawner", info.name, this->_rand() % 1000/*x*/, this->_y + 100, 0, 0, info.scrollable, false, -100);
}

void	MonsterGenerator::updateId()
{
	for (; this->_maxId < this->_randMonsters.size() && this->_squadLevel >= this->_randMonsters[this->_maxId].level; ++this->_maxId);
}

void	MonsterGenerator::generateSquad(double time)
{
	if (this->_randMonsters.empty())
		return ;
	if (this->_maxId == 0)
	{
		this->_squadLevel = this->_randMonsters[0].level * 4;
		this->_maxId = 1;
		this->updateId();
	}
	size_t level = 0;

	size_t tmpMaxId = this->_maxId;
	do
	{
		while (tmpMaxId - 1 >= 0)
		{
			if (this->_squadLevel - level >= this->_randMonsters[tmpMaxId - 1].level)
				break;
			--tmpMaxId;
		}
		if (tmpMaxId - 1 < 0)
			return ;
		MonsterInfo &info = this->_randMonsters[this->_rand() % tmpMaxId];
		this->createMonster(info);
		level += info.level;
	} while (level < this->_squadLevel);
	this->_elapsedTime += this->_squadTime;
	++this->_nbSquads;
}

void	MonsterGenerator::generateBoss(double time)
{
	this->_nbSquads = 0;
	this->_squadLevel += this->_squadLevelSpeed;
	this->updateId();
}

void	MonsterGenerator::roundWall(int x, int y)
{
	if (x - 1 >= 0 && this->_maze[y * WIDTH + x - 1] == EMPTY)
		this->_maze[y * WIDTH + x - 1] = WALL;
	if (x + 1 < WIDTH && this->_maze[y * WIDTH + x + 1] == EMPTY)
		this->_maze[y * WIDTH + x + 1] = WALL;
	if (y - 1 >= 0 && this->_maze[(y - 1) * WIDTH + x] == EMPTY)
		this->_maze[(y - 1) * WIDTH + x] = WALL;
	if (y + 1 < HEIGHT && this->_maze[(y + 1) * WIDTH + x] == EMPTY)
		this->_maze[(y + 1) * WIDTH + x] = WALL;
}

bool	MonsterGenerator::thereIsFreeWay(int x, int y, int direction, int direction2)
{
	return ((x - 1 >= 0/* && this->_maze[y * WIDTH + x - 1] != HWALL && this->_maze[y * WIDTH + x - 1] != VWALL*/ &&
		this->_maze[y * WIDTH + x - 1] != WAY && direction != 0 && direction2 != 1) ||
		(x + 1 < WIDTH/* && this->_maze[y * WIDTH + x + 1] != HWALL && this->_maze[y * WIDTH + x + 1] != VWALL*/ &&
		this->_maze[y * WIDTH + x + 1] != WAY && direction != 1 && direction2 != 0) ||
		(y - 1 < 0 || (/*this->_maze[(y - 1) * WIDTH + x] != HWALL && this->_maze[(y - 1) * WIDTH + x] != VWALL &&*/
		this->_maze[(y - 1) * WIDTH + x] != WAY && direction != 2))/* ||
		(y + 1 < HEIGHT && this->_maze[(y + 1) * WIDTH + x] != HWALL && this->_maze[(y + 1) * WIDTH + x] != VWALL &&
		this->_maze[(y + 1) * WIDTH + x] != WAY && direction != 3)*/);
}

void	MonsterGenerator::chooseMovingWall(int x, int y, int direction)
{
		std::vector<MonsterGenerator::Direction> directions;

		if (x - 1 >= 0 && this->_maze[y * WIDTH + x - 1] != HWALL && this->_maze[y * WIDTH + x - 1] != VWALL && direction != 1 && this->thereIsFreeWay(x, y, 0, direction))
		{
			directions.push_back(LEFT);
			if (this->_maze[y * WIDTH + x - 1] == WAY)
			{
				directions.push_back(LEFT);
				directions.push_back(LEFT);
			}
		}
		if (x + 1 < WIDTH && this->_maze[y * WIDTH + x + 1] != HWALL && this->_maze[y * WIDTH + x + 1] != VWALL && direction != 0 && this->thereIsFreeWay(x, y, 1, direction))
		{
			directions.push_back(RIGHT);
			if (this->_maze[y * WIDTH + x + 1] == WAY)
			{
				directions.push_back(RIGHT);
				directions.push_back(RIGHT);
			}
		}
		if (y - 1 >= 0 && this->_maze[(y - 1) * WIDTH + x] != HWALL && this->_maze[(y - 1) * WIDTH + x] != VWALL && direction != 3 && this->thereIsFreeWay(x, y, 2, direction))
		{
			directions.push_back(TOP);
			if (this->_maze[(y - 1) * WIDTH + x] == WAY)
			{
				directions.push_back(TOP);
				directions.push_back(TOP);
			}
		}
		if (y + 1 < HEIGHT && this->_maze[(y + 1) * WIDTH + x] != HWALL && this->_maze[(y + 1) * WIDTH + x] != VWALL && direction != 2 && this->thereIsFreeWay(x, y, 3, direction))
		{
			directions.push_back(BOTTOM);
			if (this->_maze[(y + 1) * WIDTH + x] == WAY)
			{
				directions.push_back(BOTTOM);
				directions.push_back(BOTTOM);
			}
		}

		int i = this->_rand() % directions.size();

		if (directions[i] == LEFT)
		{
			//std::cout << "wall left" << std::endl;
			this->_maze[y * WIDTH + x] = HWALL;
			this->_maze[y * WIDTH + x - 1] = HWALL;
		}
		else if (directions[i] == RIGHT)
		{
			//std::cout << "wall right" << std::endl;
			this->_maze[y * WIDTH + x] = HWALL;
			this->_maze[y * WIDTH + x + 1] = HWALL;
		}
		else if (directions[i] == TOP)
		{
			//std::cout << "wall top" << std::endl;
			this->_maze[y * WIDTH + x] = VWALL;
			this->_maze[(y - 1) * WIDTH + x] = VWALL;
		}
		else
		{
			//std::cout << "wall bottom" << std::endl;
			this->_maze[y * WIDTH + x] = VWALL;
			this->_maze[(y + 1) * WIDTH + x] = VWALL;
		}
}

void	MonsterGenerator::onLeft(int &x, int &y)
{
	//std::cout << "left" << std::endl;
	if (this->_maze[y * WIDTH + x - 1] == WALL)
		this->chooseMovingWall(x - 1, y, 0);
	this->roundWall(x, y);
	--x;
}

void	MonsterGenerator::onRight(int &x, int &y)
{
	//std::cout << "right" << std::endl;
	if (this->_maze[y * WIDTH + x + 1] == WALL)
		this->chooseMovingWall(x + 1, y, 1);
	this->roundWall(x, y);
	++x;
}

void	MonsterGenerator::onTop(int &x, int &y)
{
	//std::cout << "top" << std::endl;
	if (this->_maze[(y - 1) * WIDTH + x] == WALL)
		this->chooseMovingWall(x, y - 1, 2);
	this->roundWall(x, y);
	--y;
}

void	MonsterGenerator::onBottom(int &x, int &y)
{
	//std::cout << "bottom" << std::endl;
	if (this->_maze[(y + 1) * WIDTH + x] == WALL)
		this->chooseMovingWall(x, y + 1, 3);
	this->roundWall(x, y);
	++y;
}

bool	MonsterGenerator::isMovable(int x, int y, int direction)
{
	int i = 0;
	bool	tab[] = {false, false, false};
	if (x - 1 >= 0 && this->_maze[y * WIDTH + x - 1] != WAY && direction != 0)
		tab[0] = true;
	if (x + 1 < WIDTH && this->_maze[y * WIDTH + x + 1] != WAY && direction != 1)
		tab[1] = true;
	if (y - 1 >= 0 && this->_maze[(y - 1) * WIDTH + x] != WAY && direction != 2)
		tab[2] = true;
	return ((x - 1 >= 0 && this->_maze[y * WIDTH + x - 1] != HWALL && this->_maze[y * WIDTH + x - 1] != VWALL &&
		(tab[1] || tab[2]) &&
		/*this->_maze[y * WIDTH + x - 1] != WAY &&*/ direction != 0) ||
		(x + 1 < WIDTH && this->_maze[y * WIDTH + x + 1] != HWALL && this->_maze[y * WIDTH + x + 1] != VWALL &&
		(tab[0] || tab[2]) &&
		/*this->_maze[y * WIDTH + x + 1] != WAY &&*/ direction != 1) ||
		(y - 1 >= 0 && this->_maze[(y - 1) * WIDTH + x] != HWALL && this->_maze[(y - 1) * WIDTH + x] != VWALL &&
		(tab[0] || tab[1]) &&
		/*this->_maze[(y - 1) * WIDTH + x] != WAY &&*/ direction != 2) ||
		(y + 1 < HEIGHT && this->_maze[(y + 1) * WIDTH + x] != HWALL && this->_maze[(y + 1) * WIDTH + x] != VWALL &&
		(tab[0] || tab[1] || tab[2]) &&
		/*this->_maze[(y + 1) * WIDTH + x] != WAY &&*/ direction != 3));
}

bool	MonsterGenerator::hWallIsTraversable(int x, int y, int direction)
{
	if (this->_maze[y * WIDTH + x] == HWALL)
	{
		if (direction == 0)
		{
			int i = 1;
			for (; x + i < WIDTH && this->_maze[y * WIDTH + x + i] == HWALL; ++i);
			return (i % 2 == 0);
		}
		else if (direction == 1)
		{
			int i = 1;
			for (; x - i >= 0 && this->_maze[y * WIDTH + x - i] == HWALL; ++i);
			return (i % 2 == 0);
		}
	}
	return (true);
}

bool	MonsterGenerator::vWallIsTraversable(int x, int y, int direction)
{
	if (this->_maze[y * WIDTH + x] == VWALL)
	{
		if (direction == 2)
		{
			int i = 1;
			for (; y + i < HEIGHT && this->_maze[(y + i) * WIDTH + x] == VWALL; ++i);
			return (i % 2 == 0);
		}
		else if (direction == 3)
		{
			int i = 1;
			for (; y - i >= 0 && this->_maze[(y - i) * WIDTH + x] == VWALL; ++i);
			return (i % 2 == 0);
		}
	}
	return (true);
}

void	MonsterGenerator::createMaze()
{
	for (int i = 0; i < WIDTH * HEIGHT; ++i)
		this->_maze[i] = EMPTY;
	int x = this->_position;
	int y = HEIGHT - 1;
	MonsterGenerator::Direction curDir = TOP;
	while (y >= 0)
	{
		if (this->_maze[y * WIDTH + x] == EMPTY || this->_maze[y * WIDTH + x] == WALL)
			this->_maze[y * WIDTH + x] = WAY;

		std::vector<MonsterGenerator::Direction> directions;

		if (curDir != RIGHT && x - 1 >= 0 && (this->_maze[y * WIDTH + x - 1] == EMPTY ||
			(this->_maze[y * WIDTH + x - 1] == HWALL && this->hWallIsTraversable(x, y, 0)) || this->_maze[y * WIDTH + x - 1] == VWALL ||
			(this->_maze[y * WIDTH + x - 1] == WALL && this->isMovable(x - 1, y, 1))))
		{
			for (size_t i = 0; i < this->_leftFrequency; ++i)
				directions.push_back(LEFT);
		}
		if (curDir != LEFT && x + 1 < WIDTH && (this->_maze[y * WIDTH + x + 1] == EMPTY ||
			(this->_maze[y * WIDTH + x + 1] == HWALL && this->hWallIsTraversable(x, y, 1)) || this->_maze[y * WIDTH + x + 1] == VWALL ||
			(this->_maze[y * WIDTH + x + 1] == WALL && this->isMovable(x + 1, y, 0))))
		{
			for (size_t i = 0; i < this->_rightFrequency; ++i)
				directions.push_back(RIGHT);
		}
		if (y - 1 < 0 || (this->_maze[(y - 1) * WIDTH + x] == EMPTY ||
			this->_maze[(y - 1) * WIDTH + x] == HWALL || (this->_maze[(y - 1) * WIDTH + x] == VWALL && this->vWallIsTraversable(x, y, 2)) ||
			(this->_maze[(y - 1) * WIDTH + x] == WALL && this->isMovable(x, y - 1, 3))))
		{
			for (size_t i = 0; i < this->_upFrequency; ++i)
				directions.push_back(TOP);
		}
		if (y + 1 < HEIGHT && (this->_maze[(y + 1) * WIDTH + x] == EMPTY ||
			(this->_maze[(y + 1) * WIDTH + x] == WALL && this->isMovable(x, y + 1, 2))))
			/*directions.push_back(BOTTOM)*/;

		int i = this->_rand() % directions.size();

		if (directions[i] == LEFT)
			this->onLeft(x, y);
		else if (directions[i] == RIGHT)
			this->onRight(x, y);
		else if (directions[i] == TOP)
			this->onTop(x, y);
		else
			this->onBottom(x, y);
		curDir = directions[i];
	}
	if (this->_maze[y * WIDTH + x] == EMPTY || this->_maze[y * WIDTH + x] == WALL)
		this->_maze[y * WIDTH + x] = WAY;
	this->_position = x;

	// debug display maze
	//for (int i = 0; i < HEIGHT; ++i)
	//{
	//	for (int j = 0; j < WIDTH; ++j)
	//	{
	//		std::cout << " " << this->_maze[i * WIDTH + j];
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;
	/////
}

void	MonsterGenerator::addSideWalls(double elapsed)
{
	MonsterInfo const &info = this->_walls[0];
	this->_tmpY = this->_y + (elapsed - this->_wallSize);
	this->createWall(info, 0, 0);
	this->createWall(info, 6, 0);
}

void	MonsterGenerator::createWalls(int offset)
{
	for (int y = HEIGHT - 1; y >= 0; --y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			WallType type = this->_maze[y * WIDTH + x];
			if (type == WALL || type == EMPTY)
				this->createWall(this->_walls[0], x + 1, (HEIGHT - 1) - y + offset * HEIGHT + 1);
			else if (type == HWALL)
			{
				if (x % 2 == 0)
					this->createWall(this->_walls[1], x + 2, (HEIGHT - 1) - y + offset * HEIGHT + 1);
				else
					this->createWall(this->_walls[3], x + 1, (HEIGHT - 1) - y + offset * HEIGHT + 1);
				++x;
			}
			else if (type == VWALL && (y == HEIGHT - 1 || this->_maze[(y + 1) * WIDTH + x] != VWALL))
			{
				if (((HEIGHT - 1) - y + offset * HEIGHT) % 2 == 0)
					this->createWall(this->_walls[2], x + 1, (HEIGHT - 1) - y + offset * HEIGHT + 1);
				else
					this->createWall(this->_walls[4], x + 1, (HEIGHT - 1) - y + offset * HEIGHT + 1 + 1);
			}
			else if (type == VWALL)
				this->_maze[y  * WIDTH + x] = WALL;
			else if (!this->_breakableWalls.empty() && type == WAY &&
				((y == HEIGHT - 1 && this->_lastPosition == x) || /*this->_maze[(y + 1) * WIDTH + x] == VWALL ||
				this->_maze[(y + 1) * WIDTH + x] == HWALL ||*/
				(y != HEIGHT - 1 && this->_maze[(y + 1) * WIDTH + x] == WAY)))
				this->createWall(this->_breakableWalls[0], x + 1, (HEIGHT - 1) - y + offset * HEIGHT + 1);
		}
	}
}

void	MonsterGenerator::createDoor()
{
	for (int x = 0; x < WIDTH; ++x)
	{
		if (x != this->_position)
			this->createWall(this->_walls[0], x + 1, 0);
	}
}

void	MonsterGenerator::generate(double time)
{
	if (this->_inMaze)
	{
		double elapsed = this->_y - this->_tmpY;
		if (elapsed >= this->_wallSize)
		{
			int nbMaze = 1;
			this->addSideWalls(elapsed);
			if (this->_mazeY == 0)
			{
				this->createDoor();
				for (int offset = 0; offset < nbMaze; ++offset)
				{
					this->createMaze();
					this->createWalls(offset);
					this->_lastPosition = this->_position;
				}
			}
			this->_mazeY = (this->_mazeY + 1) % (HEIGHT * nbMaze + 1);
		}
	}
	else
	{
		if (this->_elapsedTime <= 0)
		{
			if (this->_nbSquads < this->_nbSquadsMax)
				this->generateSquad(time);
			else
				this->generateBoss(time);
		}
		else
			this->_elapsedTime -= time;
	}
}
