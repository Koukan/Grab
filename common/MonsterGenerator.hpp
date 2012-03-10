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

		bool	operator<(MonsterInfo const &info) { return (this->level < info.level); }

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

	typedef std::vector<MonsterInfo>	Monsters;

	Monsters	_randMonsters;
	Monsters	_bosses;
	Monsters	_walls;
	Monsters	_breakableWalls;

	size_t		_maxId;
	size_t		_squadLevel;
	size_t		_squadLevelSpeed;
	size_t		_nbSquads;
	size_t		_nbSquadsMax;
	size_t		_squadTime;
	Net::MTRand	_rand;
	double		_elapsedTime;
	bool		_inMaze;
	double		_tmpY;
	double		_wallSize;
	WallType	_maze[5 * 3];
	int			_position;
	int			_mazeY;

	void	createMonster(MonsterInfo const &info);
	void	createWall(MonsterInfo const &info, int x, double y);
	void	updateId();
	void	addSideWalls(double elapsed);
	void	chooseMovingWall(int x, int y, int direction);
	bool	thereIsFreeWay(int x, int y, int direction);
	void	createWalls();
	void	createMaze(double elapsed);
	void	roundWall(int x, int y);
	void	onLeft(int &x, int &y);
	void	onRight(int &x, int &y);
	void	onTop(int &x, int &y);
	void	onBottom(int &x, int &y);
};
