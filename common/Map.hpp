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
		void	addMonster(std::string const &name, size_t x, size_t y, int vx, int vy);
		void    addDecoration(std::string const &name, size_t x, size_t y, int vx, int vy);

	protected:
		struct mapdata
		{
			std::string	name;
			size_t		x;
			int			vx;
			int			vy;
			int			vScrolling;
		};

		std::multimap<size_t, mapdata>		_monsters;
		std::multimap<size_t, mapdata>      _decorations;
};
