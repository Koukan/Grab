#include "MonsterGenerator.hpp"
#include <algorithm>
#include "GameState.hpp"
#include "GameCommand.hpp"
#include "CommandDispatcher.hpp"

MonsterGenerator::MonsterGenerator(int seed)
	: _maxId(0), _squadLevelSpeed(4), _mazeLevel(-1), _mazeEnemiesFrequency(0), _mazeBreakableWallsFrequency(1), _mazeNoObstacleFrequency(5),
	_leftFrequency(20), _rightFrequency(20), _upFrequency(1), _nbSquads(0), _nbSquadsMax(10), _squadTime(/*10*/5), _bossTime(10), _rand(seed), _elapsedTime(5.7),
	_inMaze(false), _tmpY(this->_y), _wallSize(185), _position(1), _lastPosition(_position), _mazeY(0),
	  _MazeEnemiesNb(0), _MazeBreakableWallsNb(0), _MazeMovableWallsNb(0), _MazeWallsNb(0), _y2(this->_y), _currentSound(0), _beginning(true),
	  _mode(Modes::SURVIVAL_SCORING)
{
	this->_sounds[0] = 0;
	this->_sounds[1] = 0;
}

MonsterGenerator::~MonsterGenerator()
{
	if (this->_sounds[0])
		delete this->_sounds[0];
	if (this->_sounds[1])
		delete this->_sounds[1];
}

Core::Resource    *MonsterGenerator::clone() const
{
	return (new MonsterGenerator(*this));
}

void	MonsterGenerator::move(double time)
{
	this->generate(time);
	this->Map::move(time);
	this->_y2 += this->_vy * time;
}

void	MonsterGenerator::addRandomBoss(std::string const &name, bool scrollable, size_t level, int min, int max, int ymin, int ymax)
{
	this->_bosses.push_back(MonsterInfo(level, name, scrollable, min, max, ymin, ymax));
}

void	MonsterGenerator::addRandomMonster(std::string const &name, bool scrollable, size_t level, int min, int max, int ymin, int ymax)
{
	this->_randMonsters.push_back(MonsterInfo(level, name, scrollable, min, max, ymin, ymax));
	std::sort(this->_randMonsters.begin(), this->_randMonsters.end());
}

void	MonsterGenerator::addMazeMonster(std::string const &name, bool scrollable, size_t level, int min, int max, int ymin, int ymax)
{
	this->_mazeMonsters.push_back(MonsterInfo(level, name, scrollable, min, max, ymin, ymax));
	std::sort(this->_mazeMonsters.begin(), this->_mazeMonsters.end());
}

void	MonsterGenerator::addRandomWall(std::string const &name, bool scrollable, size_t level, int min, int max, int ymin, int ymax)
{
	this->_walls.push_back(MonsterInfo(level, name, scrollable, min, max, ymin, ymax));
	std::sort(this->_walls.begin(), this->_walls.end());
}

void	MonsterGenerator::addRandomHWall(std::string const &name, bool scrollable, size_t level, int min, int max, int ymin, int ymax)
{
	this->_hWalls.push_back(MonsterInfo(level, name, scrollable, min, max, ymin, ymax));
	std::stable_sort(this->_hWalls.begin(), this->_hWalls.end());
}

void	MonsterGenerator::addRandomVWall(std::string const &name, bool scrollable, size_t level, int min, int max, int ymin, int ymax)
{
	this->_vWalls.push_back(MonsterInfo(level, name, scrollable, min, max, ymin, ymax));
	std::stable_sort(this->_vWalls.begin(), this->_vWalls.end());
}

void	MonsterGenerator::addRandomBreakableWall(std::string const &name, bool scrollable, size_t level, int min, int max, int ymin, int ymax)
{
	this->_breakableWalls.push_back(MonsterInfo(level, name, scrollable, min, max, ymin, ymax));
	std::sort(this->_breakableWalls.begin(), this->_breakableWalls.end());
}

void	MonsterGenerator::addSquadSound(std::string const &name, bool /*scrollable*/, size_t /*level*/, int /*min*/, int /*max*/, int /*ymin*/, int /*ymax*/)
{
	this->_squadSounds.push_back(name);
}

void	MonsterGenerator::addBossSound(std::string const &name, bool /*scrollable*/, size_t /*level*/, int /*min*/, int /*max*/, int ymin, int ymax)
{
	this->_bossSounds.push_back(name);
}

void	MonsterGenerator::spawnSideWall(int x, int y)
{
	Core::GameState	&gm = this->getGroup()->getState();

	while (this->_MazeWallsNb + 1 < this->_walls.size() && this->_walls[this->_MazeWallsNb + 1].level <= this->_mazeLevel)
		++this->_MazeWallsNb;
	int begin = this->_MazeWallsNb;
	while (begin - 1 >= 0 && this->_walls[begin - 1].level == this->_walls[begin].level)
		--begin;
	int i = this->_rand() % (this->_MazeWallsNb + 1 - begin);
	MonsterInfo const &info = this->_walls[begin + i];

	GameCommand	*cmd;
	cmd = new GameCommand("spawnspawner");
	cmd->y = static_cast<int16_t>((static_cast<size_t>(this->_y2 - (this->_tmpY + 110 + y * this->_wallSize))) - 320);
	cmd->x = static_cast<size_t>((x * this->_wallSize) - 100 + 200);
	cmd->vx = 0;
	cmd->vy = 0;
	if (info.scrollable)
		cmd->position = static_cast<float>(this->_vy);
	else
		cmd->position = 0;
	cmd->data = info.name;
	cmd->boolean = false;
	gm.pushCommand(*cmd, true);
}

void	MonsterGenerator::createWall(int x, int y)
{
	while (this->_MazeWallsNb + 1 < this->_walls.size() && this->_walls[this->_MazeWallsNb + 1].level <= this->_mazeLevel)
		++this->_MazeWallsNb;
	int begin = this->_MazeWallsNb;
	while (begin - 1 >= 0 && this->_walls[begin - 1].level == this->_walls[begin].level)
		--begin;
	int i = this->_rand() % (this->_MazeWallsNb + 1 - begin);
	MonsterInfo const &info = this->_walls[begin + i];
	this->addElem("spawnspawner", info.name, static_cast<size_t>((x * this->_wallSize) - 100 + 200),
		static_cast<size_t>((this->_tmpY - (this->_y2 - this->_y)) + 110 + y * this->_wallSize), 0, 0, info.scrollable, false, -320);
}

void	MonsterGenerator::createBreakableWall(int x, int y)
{
	while (this->_MazeBreakableWallsNb + 1 < this->_breakableWalls.size() &&
		this->_breakableWalls[this->_MazeBreakableWallsNb + 1].level <= this->_mazeLevel)
		++this->_MazeBreakableWallsNb;
	int begin = this->_MazeBreakableWallsNb;
	while (begin - 1 >= 0 && this->_breakableWalls[begin - 1].level == this->_breakableWalls[begin].level)
		--begin;
	int i = this->_rand() % (this->_MazeBreakableWallsNb + 1 - begin);
	MonsterInfo const &info = this->_breakableWalls[begin + i];
	this->addElem("spawnspawner", info.name, static_cast<size_t>((x * this->_wallSize) - 100 + 200),
		static_cast<size_t>((this->_tmpY - (this->_y2 - this->_y)) + 110 + y * this->_wallSize), 0, 0, info.scrollable, false, -320);
}

void	MonsterGenerator::createVWall(int x, int y, int direction)
{
	while (this->_MazeMovableWallsNb + 1 < this->_vWalls.size() && this->_vWalls[this->_MazeMovableWallsNb + 1].level <= this->_mazeLevel)
		++this->_MazeMovableWallsNb;
	int begin = this->_MazeMovableWallsNb;
	while (begin - 2 >= 0 && this->_vWalls[begin - 2].level == this->_vWalls[begin].level)
		begin -= 2;
	int i = this->_rand() % ((this->_MazeMovableWallsNb + 2 - begin) / 2);
	MonsterInfo const &info = this->_vWalls[begin + i * 2 - direction];
	this->addElem("spawnspawner", info.name, static_cast<size_t>((x * this->_wallSize) - 100 + 200),
		static_cast<size_t>(this->_tmpY - (this->_y2 - this->_y) + 110), 0, 0, info.scrollable, false, static_cast<int>(-320 - y * this->_wallSize));
}

void	MonsterGenerator::createHWall(int x, int y, int direction)
{
	while (this->_MazeMovableWallsNb + 1 < this->_hWalls.size() && this->_hWalls[this->_MazeMovableWallsNb + 1].level <= this->_mazeLevel)
		++this->_MazeMovableWallsNb;
	int begin = this->_MazeMovableWallsNb;
	while (begin - 2 >= 0 && this->_hWalls[begin - 2].level == this->_hWalls[begin].level)
		begin -= 2;
	int i = this->_rand() % ((this->_MazeMovableWallsNb + 2 - begin) / 2);
	MonsterInfo const &info = this->_hWalls[begin + i * 2 - direction];
	this->addElem("spawnspawner", info.name, static_cast<size_t>((x * this->_wallSize) - 100 + 200),
		static_cast<size_t>(this->_tmpY - (this->_y2 - this->_y) + 110), 0, 0, info.scrollable, false, static_cast<int>(-320 - y * this->_wallSize));
}

void	MonsterGenerator::createMazeMonster(int x, int y)
{
	while (this->_MazeEnemiesNb + 1 < this->_mazeMonsters.size() && this->_mazeMonsters[this->_MazeEnemiesNb + 1].level <= this->_mazeLevel)
		++this->_MazeEnemiesNb;
	int begin = this->_MazeEnemiesNb;
	while (begin - 1 >= 0 && this->_mazeMonsters[begin - 1].level == this->_mazeMonsters[begin].level)
		--begin;
	int i = this->_rand() % (this->_MazeEnemiesNb + 1 - begin);
	MonsterInfo const &info = this->_mazeMonsters[begin + i];
	this->addElem("spawnspawner", info.name, static_cast<size_t>((x * this->_wallSize) + 80),
		static_cast<size_t>(this->_tmpY - (this->_y2 - this->_y) - 80 + y * this->_wallSize + 200), 0, 0, info.scrollable, false, -320);
}

void	MonsterGenerator::createMonster(MonsterInfo const &info)
{
	this->addElem("spawnspawner", info.name, this->_rand() % (info.xmax - info.xmin) + info.xmin,
		static_cast<size_t>(this->_y/* + 100*/), 0, 0, info.scrollable, true, this->_rand() % (info.ymax - info.ymin) + info.ymin);
}

void	MonsterGenerator::createBoss(MonsterInfo const &info)
{
	this->addElem("spawnspawner", info.name, this->_rand() % (info.xmax - info.xmin) + info.xmin,
		static_cast<size_t>(this->_y + 100), 0, 0, info.scrollable, true, this->_rand() % (info.ymax - info.ymin) + info.ymin);
}

void	MonsterGenerator::createSquadSound()
{
	if (this->_squadSounds.empty())
		return ;
	Core::GameState	&gm = this->getGroup()->getState();

	int i = this->_rand() % this->_squadSounds.size();
	this->_currentSound = (this->_currentSound + 1) % 2;
	this->_sounds[this->_currentSound] = gm.getSound(this->_squadSounds[i]);
	if (this->_sounds[this->_currentSound])
		this->_sounds[this->_currentSound]->play();
}

void	MonsterGenerator::createBossSound()
{
	if (this->_bossSounds.empty())
		return ;
	Core::GameState	&gm = this->getGroup()->getState();

	int i = this->_rand() % this->_bossSounds.size();
	this->_currentSound = (this->_currentSound + 1) % 2;
	this->_sounds[this->_currentSound] = gm.getSound(this->_bossSounds[i]);
	if (this->_sounds[this->_currentSound])
		this->_sounds[this->_currentSound]->play();
}

void	MonsterGenerator::soundTransition(double elapsedTime)
{
	int i = (this->_currentSound + 1) % 2;
	double	speed = 50;
	if (this->_sounds[i])
	{
		double volume = this->_sounds[i]->getVolume() - speed * elapsedTime;
		if (volume <= 0)
		{
			delete this->_sounds[i];
			this->_sounds[i] = 0;
		}
		else
			this->_sounds[i]->setVolume(volume);
	}
}

void	MonsterGenerator::updateId()
{
	for (; this->_maxId < this->_randMonsters.size() && this->_squadLevel >= this->_randMonsters[this->_maxId].level; ++this->_maxId);
	//{
	//	//std::cout << "loop 3" << std::endl;
	//}
}

void	MonsterGenerator::generateSquad(double)
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
		//std::cout << "loop 1" << std::endl;
		while (tmpMaxId >= 1)
		{
			//std::cout << "loop 2" << std::endl;
			if (this->_squadLevel - level >= this->_randMonsters[tmpMaxId - 1].level)
				break;
			--tmpMaxId;
		}
		if (tmpMaxId < 1)
			return ;
		MonsterInfo &info = this->_randMonsters[this->_rand() % tmpMaxId];
		this->createMonster(info);
		level += info.level;
	} while (level < this->_squadLevel);
	if (this->_nbSquads + 1 < this->_nbSquadsMax)
		this->_elapsedTime /*+= this->_squadTime*/ = 1;
	++this->_nbSquads;
}

void	MonsterGenerator::generateBoss(double)
{
	if (!this->_bosses.empty())
	{
		int i = this->_rand() % this->_bosses.size();
		this->createBoss(this->_bosses[i]);
		this->_elapsedTime = this->_bossTime;
	}
}

void	MonsterGenerator::setSeed(uint32_t seed)
{
	this->_rand.seed(seed);
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
			//if (this->_maze[y * WIDTH + x - 1] == WAY)
			//{
			//	directions.push_back(LEFT);
			//	directions.push_back(LEFT);
			//}
		}
		if (x + 1 < WIDTH && this->_maze[y * WIDTH + x + 1] != HWALL && this->_maze[y * WIDTH + x + 1] != VWALL && direction != 0 && this->thereIsFreeWay(x, y, 1, direction))
		{
			directions.push_back(RIGHT);
			//if (this->_maze[y * WIDTH + x + 1] == WAY)
			//{
			//	directions.push_back(RIGHT);
			//	directions.push_back(RIGHT);
			//}
		}
		if (y - 1 >= 0 && this->_maze[(y - 1) * WIDTH + x] != HWALL && this->_maze[(y - 1) * WIDTH + x] != VWALL && direction != 3 && this->thereIsFreeWay(x, y, 2, direction))
		{
			directions.push_back(TOP);
			//if (this->_maze[(y - 1) * WIDTH + x] == WAY)
			//{
			//	directions.push_back(TOP);
			//	directions.push_back(TOP);
			//}
		}
		if (y + 1 < HEIGHT && this->_maze[(y + 1) * WIDTH + x] != HWALL && this->_maze[(y + 1) * WIDTH + x] != VWALL && direction != 2 && this->thereIsFreeWay(x, y, 3, direction))
		{
			directions.push_back(BOTTOM);
			//if (this->_maze[(y + 1) * WIDTH + x] == WAY)
			//{
			//	directions.push_back(BOTTOM);
			//	directions.push_back(BOTTOM);
			//}
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
		//if (y + 1 < HEIGHT && (this->_maze[(y + 1) * WIDTH + x] == EMPTY ||
			//(this->_maze[(y + 1) * WIDTH + x] == WALL && this->isMovable(x, y + 1, 2))))
			//directions.push_back(BOTTOM);

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
	this->_tmpY = this->_y2 - (elapsed - this->_wallSize);
	this->spawnSideWall(0, 0);
	this->spawnSideWall(WIDTH + 1, 0);
	//this->createWall(0, 0);
	//this->createWall(6, 0);
}

void	MonsterGenerator::createObstacle(int x, int y)
{
	std::vector<int> tab;

	if (!this->_breakableWalls.empty())
	{
		for (size_t i = 0; i < this->_mazeBreakableWallsFrequency; ++i)
			tab.push_back(0);
	}
	if (!this->_mazeMonsters.empty())
	{
		for (size_t i = 0; i < this->_mazeEnemiesFrequency; ++i)
			tab.push_back(1);
	}
	for (size_t i = 0; i < this->_mazeNoObstacleFrequency; ++i)
		tab.push_back(2);

	if (tab.size() == 0)
		return ;
	int i = this->_rand() % tab.size();
	if (tab[i] == 0)
		this->createBreakableWall(x, y);
	else if (tab[i] == 1)
		this->createMazeMonster(x, y);
}

void	MonsterGenerator::createWalls(int offset)
{
	for (int y = HEIGHT - 1; y >= 0; --y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			WallType type = this->_maze[y * WIDTH + x];
			if (type == WALL || type == EMPTY)
				this->createWall(x + 1, (HEIGHT - 1) - y + offset * HEIGHT + 1);
			else if (type == HWALL)
			{
				if (x % 2 == 0)
					this->createHWall(x + 2, (HEIGHT - 1) - y + offset * HEIGHT + 1, 1);
				else
					this->createHWall(x + 1, (HEIGHT - 1) - y + offset * HEIGHT + 1, 0);
				++x;
			}
			else if (type == VWALL && (y == HEIGHT - 1 || this->_maze[(y + 1) * WIDTH + x] != VWALL))
			{
				if (((HEIGHT - 1) - y + offset * HEIGHT) % 2 == 0)
					this->createVWall(x + 1, (HEIGHT - 1) - y + offset * HEIGHT + 1, 1);
				else
					this->createVWall(x + 1, (HEIGHT - 1) - y + offset * HEIGHT + 1 + 1, 0);
			}
			else if (type == VWALL)
				this->_maze[y  * WIDTH + x] = WALL;
			else if (type == WAY && ((y == HEIGHT - 1 && this->_lastPosition == x) ||
				(y != HEIGHT - 1 && this->_maze[(y + 1) * WIDTH + x] == WAY)))
				this->createObstacle(x + 1, (HEIGHT - 1) - y + offset * HEIGHT + 1);
		}
	}
}

void	MonsterGenerator::createDoor()
{
	for (int x = 0; x < WIDTH; ++x)
	{
		if (x != this->_position)
			this->createWall(x + 1, 0);
	}
}

void	MonsterGenerator::generate(double time)
{
	this->soundTransition(time);
	if (this->_inMaze)
	{
		double elapsed = this->_y2 - this->_tmpY;
		if (elapsed >= this->_wallSize)
		{
			int const nbMaze = 1;
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
			else if (this->_mazeY == HEIGHT * nbMaze + 1)
				this->createDoor();
			else if (this->_mazeY == HEIGHT * nbMaze + 9)
			{
				this->changeToBoss();
				this->generateBoss(time);
			}
			else if (this->_mazeY > HEIGHT * nbMaze + 9 && this->_nbPaused == 0/*this->_elapsedTime <= 0*/)
				this->changeToSquads();
			++this->_mazeY;
		}
	}
	else
	{
		if (this->_beginning)
		{
			this->createSquadSound();
			this->_beginning = false;
		}
		if (this->_elapsedTime <= 0 && this->_nbPaused == 0)
		{
			if (this->_nbSquads < this->_nbSquadsMax)
				this->generateSquad(time);
			else
				this->changeToMaze();
		}
	}
	this->_elapsedTime -= time;
}

void	MonsterGenerator::changeToSquads()
{
  if (_mode == Modes::SURVIVAL_SCORING)
    {
        GameCommand	*cmd = new GameCommand("eliminateLowerScore");

	if (this->getGroup())
	    this->getGroup()->getState().pushCommand(*cmd); 
    }
  std::cout << "change to squad" << std::endl;
  this->createSquadSound();
  this->_inMaze = false;
  this->_elapsedTime = 6;

  this->_nbSquads = 0;
  this->_squadLevel += this->_squadLevelSpeed;
  this->updateId();
}

void	MonsterGenerator::changeToMaze()
{
	std::cout << "change to maze" << std::endl;
	static struct {
		int left;
		int right;
		int up;
		int enemies;
		int breakableWalls;
		int empty;
	} const mazeStages[] =
	{
		{20, 20, 1, 0, 1, 0},
		{1, 1, 2, 1, 0, 2},
		{20, 20, 1, 1, 1, 1}
	};
	static int const size = sizeof mazeStages / sizeof *mazeStages;

	if (this->_flush.empty())
	{
		this->_flush.clear();
		for (int i = 0; i < size; ++i)
			this->_flush.push_back(i);
		for (int i = size - 1; i >= 0; --i)
		{
			int j = this->_rand() % (i + 1);
			int tmp = this->_flush[i];
			this->_flush[i] = this->_flush[j];
			this->_flush[j] = tmp;
		}
	}

	++this->_mazeLevel;
	int i = this->_flush[this->_flush.size() - 1];
	this->_flush.pop_back();
	this->_leftFrequency = mazeStages[i].left;
	this->_rightFrequency = mazeStages[i].right;
	this->_upFrequency = mazeStages[i].up;
	this->_mazeEnemiesFrequency = mazeStages[i].enemies;
	this->_mazeBreakableWallsFrequency = mazeStages[i].breakableWalls;
	this->_mazeNoObstacleFrequency = mazeStages[i].empty;

	this->_inMaze = true;
	this->_tmpY = this->_y2;
	this->_mazeY = 0;
}

void	MonsterGenerator::changeToBoss()
{
	this->createBossSound();
}

void	MonsterGenerator::setMode(Modes::Mode mode)
{
  _mode = mode;
}
