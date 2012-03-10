#include "MonsterGenerator.hpp"
#include <algorithm>


MonsterGenerator::MonsterGenerator(int seed)
	: _maxId(0), _squadLevelSpeed(4), _nbSquads(0), _nbSquadsMax(10), _squadTime(10), _rand(seed), _elapsedTime(0),
	_inMaze(true), _tmpY(this->_y), _wallSize(180), _position(1), _mazeY(0)
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

void	MonsterGenerator::createWall(MonsterInfo const &info, int x, double y)
{
	this->addElem("spawnspawner", info.name, (x * this->_wallSize) - 100, y + 100, 0, 0, info.scrollable, false, -320);
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
	if (x - 1 >= 0 && this->_maze[y * 5 + x - 1] == EMPTY)
		this->_maze[y * 5 + x - 1] = WALL;
	if (x + 1 < 5 && this->_maze[y * 5 + x + 1] == EMPTY)
		this->_maze[y * 5 + x + 1] = WALL;
	if (y - 1 >= 0 && this->_maze[(y - 1) * 5 + x] == EMPTY)
		this->_maze[(y - 1) * 5 + x] = WALL;
	if (y + 1 < 3 && this->_maze[(y + 1) * 5 + x] == EMPTY)
		this->_maze[(y + 1) * 5 + x] = WALL;
}

bool	MonsterGenerator::thereIsFreeWay(int x, int y, int direction)
{
	return ((x - 1 >= 0 && this->_maze[y * 5 + x - 1] != HWALL && this->_maze[y * 5 + x - 1] != VWALL &&
		this->_maze[y * 5 + x - 1] != WAY && direction != 0) ||
		(x + 1 < 5 && this->_maze[y * 5 + x + 1] != HWALL && this->_maze[y * 5 + x + 1] != VWALL &&
		this->_maze[y * 5 + x + 1] != WAY && direction != 1) ||
		(y - 1 >= 0 && this->_maze[(y - 1) * 5 + x] != HWALL && this->_maze[(y - 1) * 5 + x] != VWALL &&
		this->_maze[(y - 1) * 5 + x] != WAY && direction != 2) ||
		(y + 1 < 3 && this->_maze[(y + 1) * 5 + x] != HWALL && this->_maze[(y + 1) * 5 + x] != VWALL &&
		this->_maze[(y + 1) * 5 + x] != WAY && direction != 3));
}

void	MonsterGenerator::chooseMovingWall(int x, int y, int direction)
{
		bool possibility[4] = {false, false, false, false};
		int mod = 0;

		if (x - 1 >= 0 && this->_maze[y * 5 + x - 1] != HWALL && this->_maze[y * 5 + x - 1] != VWALL && direction != 1 && this->thereIsFreeWay(x, y, 0))
		{
			possibility[0] = true;
			++mod;
		}
		if (x + 1 < 5 && this->_maze[y * 5 + x + 1] != HWALL && this->_maze[y * 5 + x + 1] != VWALL && direction != 0 && this->thereIsFreeWay(x, y, 1))
		{
			possibility[1] = true;
			++mod;
		}
		if (y - 1 >= 0 && this->_maze[(y - 1) * 5 + x] != HWALL && this->_maze[(y - 1) * 5 + x] != VWALL && direction != 3 && this->thereIsFreeWay(x, y, 2))
		{
			possibility[2] = true;
			++mod;
		}
		if (y + 1 < 3 && this->_maze[(y + 1) * 5 + x] != HWALL && this->_maze[(y + 1) * 5 + x] != VWALL && direction != 2 && this->thereIsFreeWay(x, y, 3))
		{
			possibility[3] = true;
			++mod;
		}
		int i = this->_rand() % mod;
		int j = -1;
		while (i >= 0)
		{
			++j;
			if (possibility[j])
				--i;
		}
		if (j == 0)
		{
			std::cout << "wall left" << std::endl;
			this->_maze[y * 5 + x] = HWALL;
			this->_maze[y * 5 + x - 1] = HWALL;
		}
		else if (j == 1)
		{
			std::cout << "wall right" << std::endl;
			this->_maze[y * 5 + x] = HWALL;
			this->_maze[y * 5 + x + 1] = HWALL;
		}
		else if (j == 2)
		{
			std::cout << "wall top" << std::endl;
			this->_maze[y * 5 + x] = VWALL;
			this->_maze[(y - 1) * 5 + x] = VWALL;
		}
		else
		{
			std::cout << "wall bottom" << std::endl;
			this->_maze[y * 5 + x] = VWALL;
			this->_maze[(y + 1) * 5 + x] = VWALL;
		}
}

void	MonsterGenerator::onLeft(int &x, int &y)
{
	std::cout << "left" << std::endl;
	if (this->_maze[y * 5 + x - 1] == WALL)
	{
		this->chooseMovingWall(x - 1, y, 0);
		//if (y + 1 < 3 && (this->_maze[(y + 1) * 5 + x - 1] == WAY || y - 1 < 0))
		//{
		//	this->_maze[y * 5 + x - 1] = VWALL;
		//	this->_maze[(y + 1) * 5 + x - 1] = VWALL;
		//}
		//else if (y - 1 >= 0)
		//{
		//	this->_maze[y * 5 + x - 1] = VWALL;
		//	this->_maze[(y - 1) * 5 + x - 1] = VWALL;
		//}
	}
	this->roundWall(x, y);
	--x;
}

void	MonsterGenerator::onRight(int &x, int &y)
{
	std::cout << "right" << std::endl;
	if (this->_maze[y * 5 + x + 1] == WALL)
	{
		this->chooseMovingWall(x + 1, y, 1);
		//if (y + 1 < 3 && (this->_maze[(y + 1) * 5 + x + 1] == WAY || y - 1 < 0))
		//{
		//	this->_maze[y * 5 + x + 1] = VWALL;
		//	this->_maze[(y + 1) * 5 + x + 1] = VWALL;
		//}
		//else if (y - 1 >= 0)
		//{
		//	this->_maze[y * 5 + x + 1] = VWALL;
		//	this->_maze[(y - 1) * 5 + x + 1] = VWALL;
		//}
	}
	this->roundWall(x, y);
	++x;
}

void	MonsterGenerator::onTop(int &x, int &y)
{
	std::cout << "top" << std::endl;
	if (this->_maze[(y - 1) * 5 + x] == WALL)
	{
		this->chooseMovingWall(x, y - 1, 2);
		//if (x + 1 < 5 && (this->_maze[(y - 1) * 5 + x + 1] == WAY || x - 1 < 0))
		//{
		//	this->_maze[(y - 1) * 5 + x] = HWALL;
		//	this->_maze[(y - 1) * 5 + x + 1] = HWALL;
		//}
		//else if (x - 1 >= 0)
		//{
		//	this->_maze[(y - 1) * 5 + x] = HWALL;
		//	this->_maze[(y - 1) * 5 + x - 1] = HWALL;
		//}
	}
	this->roundWall(x, y);
	--y;
}

void	MonsterGenerator::onBottom(int &x, int &y)
{
	std::cout << "bottom" << std::endl;
	if (this->_maze[(y + 1) * 5 + x] == WALL)
	{
		this->chooseMovingWall(x, y + 1, 3);
		//if (x + 1 < 5 && (this->_maze[(y + 1) * 5 + x + 1] == WAY || x - 1 < 0))
		//{
		//	this->_maze[(y + 1) * 5 + x] = HWALL;
		//	this->_maze[(y + 1) * 5 + x + 1] = HWALL;
		//}
		//else if (x - 1 >= 0)
		//{
		//	this->_maze[(y + 1) * 5 + x] = HWALL;
		//	this->_maze[(y + 1) * 5 + x - 1] = HWALL;
		//}
	}
	this->roundWall(x, y);
	++y;
}

void	MonsterGenerator::createMaze(double elapsed)
{
	for (int i = 0; i < 5 * 3; ++i)
		this->_maze[i] = EMPTY;
	int x = this->_position;
	int y = 2;
	while (y > 0)
	{
		if (this->_maze[y * 5 + x] == EMPTY || this->_maze[y * 5 + x] == WALL)
			this->_maze[y * 5 + x] = WAY;
		bool possibility[4] = {false, false, false, false};
		int mod = 0;

		if (x - 1 >= 0 && (this->_maze[y * 5 + x - 1] == EMPTY || this->_maze[y * 5 + x - 1] == WALL))
		{
			possibility[0] = true;
			++mod;
		}
		if (x + 1 < 5 && (this->_maze[y * 5 + x + 1] == EMPTY || this->_maze[y * 5 + x + 1] == WALL))
		{
			possibility[1] = true;
			++mod;
		}
		if (y - 1 >= 0 && (this->_maze[(y - 1) * 5 + x] == EMPTY || this->_maze[(y - 1) * 5 + x] == WALL))
		{
			possibility[2] = true;
			++mod;
		}
		if (y + 1 < 3 && (this->_maze[(y + 1) * 5 + x] == EMPTY || this->_maze[(y + 1) * 5 + x] == WALL))
		{
			possibility[3] = false/*true*/;
			//++mod;
		}
		int i = this->_rand() % mod;
		int j = -1;
		while (i >= 0)
		{
			++j;
			//j = (j + 1) % 4;
			if (possibility[j])
				--i;
		}
		if (j == 0)
			this->onLeft(x, y);
		else if (j == 1)
			this->onRight(x, y);
		else if (j == 2)
			this->onTop(x, y);
		else
			this->onBottom(x, y);
	}
	if (this->_maze[y * 5 + x] == EMPTY || this->_maze[y * 5 + x] == WALL)
		this->_maze[y * 5 + x] = WAY;
	this->_position = x;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			std::cout << " " << this->_maze[i * 5 + j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void	MonsterGenerator::addSideWalls(double elapsed)
{
	MonsterInfo const &info = this->_walls[0];
	this->_tmpY = this->_y + (elapsed - this->_wallSize);
	this->createWall(info, 0, this->_tmpY);
	this->createWall(info, 6, this->_tmpY);
}

void	MonsterGenerator::createWalls()
{
	for (int x = 0; x < 5; ++x)
	{
		int y = (2 - this->_mazeY);
		WallType type = this->_maze[y * 5 + x];
		if (type == WALL || type == EMPTY)
			this->createWall(this->_walls[0], x + 1, this->_tmpY);
		else if (type == HWALL)
		{
			this->createWall(this->_walls[1], x + 2, this->_tmpY);
			++x;
		}
		else if (type == VWALL && (y == 2 || this->_maze[(y + 1) * 5 + x] != VWALL))
			this->createWall(this->_walls[2], x + 1, this->_tmpY);
	}
}

void	MonsterGenerator::generate(double time)
{
	if (this->_inMaze)
	{
		double elapsed = this->_y - this->_tmpY;
		if (elapsed >= this->_wallSize)
		{
			this->addSideWalls(elapsed);
			if (this->_mazeY == 0)
				this->createMaze(elapsed);
			this->createWalls();
			this->_mazeY = (this->_mazeY + 1) % 3;
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
