#pragma once

#include "Map.hpp"
#include <vector>
#include <string>
#include <MTRand.hpp>

class MonsterGenerator : public Map
{
public:
	MonsterGenerator(int seed);
	~MonsterGenerator();

	virtual Core::Resource    *clone() const;
	virtual	void	move(double time);
	void	addRandomBoss(std::string const &name, bool scrollable, size_t level);
	void	addRandomMonster(std::string const &name, bool scrollable, size_t level);
	void	addRandomWall(std::string const &name, bool scrollable, size_t level);
	void	addRandomBreakableWall(std::string const &name, bool scrollable, size_t level);
	void	generate(double time);
	void	generateSquad(double time);
	void	generateBoss(double time);

private:
	struct MonsterInfo
	{
		MonsterInfo(size_t level, std::string const &name, bool scrollable)
			: level(level), name(name), scrollable(scrollable) {}

		bool	operator<(MonsterInfo const &info) const { return (this->level < info.level); }

		size_t		level;
		std::string	name;
		bool		scrollable;
	};

	enum WallType
	{
		EMPTY,
		WAY,
		WALL,
		HWALL,
		VWALL
	};

	enum Direction
	{
		LEFT = 0,
		RIGHT = 1,
		TOP = 2,
		BOTTOM = 3
	};

	enum MazeSize
	{
		WIDTH = 5,
		HEIGHT = 40
	};

	typedef std::vector<MonsterInfo>	Monsters;

	Monsters	_randMonsters;
	Monsters	_bosses;
	Monsters	_walls;
	Monsters	_breakableWalls;

	size_t		_maxId;
	size_t		_squadLevel;
	size_t		_leftFrequency;
	size_t		_rightFrequency;
	size_t		_upFrequency;
	size_t		_squadLevelSpeed;
	size_t		_nbSquads;
	size_t		_nbSquadsMax;
	size_t		_squadTime;
	Net::MTRand	_rand;
	double		_elapsedTime;
	bool		_inMaze;
	double		_tmpY;
	double		_wallSize;
	WallType	_maze[WIDTH * HEIGHT];
	int			_position;
	int			_mazeY;

	void	createMonster(MonsterInfo const &info);
	void	createWall(MonsterInfo const &info, int x, int y);
	void	createDoor();
	void	updateId();
	void	addSideWalls(double elapsed);
	void	chooseMovingWall(int x, int y, int direction);
	bool	hWallIsTraversable(int x, int y, int direction);
	bool	vWallIsTraversable(int x, int y, int direction);
	bool	thereIsFreeWay(int x, int y, int direction, int direction2);
	bool	isMovable(int x, int y, int direction);
	void	createWalls(int offset);
	void	createMaze();
	void	roundWall(int x, int y);
	void	onLeft(int &x, int &y);
	void	onRight(int &x, int &y);
	void	onTop(int &x, int &y);
	void	onBottom(int &x, int &y);
};
