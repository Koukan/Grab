#pragma once

#include "BulletCommand.hpp"
#include "Resource.hpp"
#include "CompositeMonsterProvider.hpp"

class	CompositeMonster : public Core::Resource
{
	public:
			CompositeMonster(std::string const &script);
			~CompositeMonster();

			virtual	Core::Resource	*clone() const;
			void	addMonster(CompositeMonsterProvider::monster &m);
			Core::BulletCommand	*getBulletCommand(Core::GameState &state);

	private:
			std::string		_bulletml;
			std::list<CompositeMonsterProvider::monster>	monsters;
};
