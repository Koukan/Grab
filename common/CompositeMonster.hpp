#pragma once

#include "Resource.hpp"
#include "CompositeMonsterProvider.hpp"

class	CompositeMonster : public Core::Resource
{
	public:
			CompositeMonster();
			~CompositeMonster();

			virtual	Core::Resource	*clone() const;
			void	addMonster(CompositeMonsterProvider::monster &m);

			std::list<CompositeMonsterProvider::monster>	monsters;
};
