#pragma once

#include <map>
#include "Resource.hpp"
#include "PhysicObject.hpp"

class	Map : public Core::Resource, public Core::PhysicObject
{
	public:
		Map();
		virtual ~Map();

		virtual Core::Resource    *clone() const;
		virtual	void				move(double time);
		void	addEnd(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry = 0);
		void	addMonster(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry = 0);
		void	addCompositeMonster(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry = 0);
		void    addDecoration(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry = 0);
		void    addSound(std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry = 0);
		void	decreasePaused();
		void	increasePaused();
		virtual void	setScrollingSpeed(double vy);
		void	clear();

	protected:
	void    addElem(std::string const &command, std::string const &name, size_t x, size_t y, int vx, int vy, bool scrollable, bool pause, int spawnY, size_t ry = 0);

		struct mapdata
		{
			std::string command;
			std::string	name;
			size_t		x;
			int			y;
			int			vx;
			int			vy;
			int			vScrolling;
			bool		pause;
		};

		std::multimap<size_t, mapdata>		_monsters;
		std::multimap<size_t, mapdata>      _decorations;
		unsigned int						_nbPaused;
		int									_prevY;
};
