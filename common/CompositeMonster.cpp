#include "CompositeMonster.hpp"

CompositeMonster::CompositeMonster()
{}

CompositeMonster::~CompositeMonster()
{}

Core::Resource    *CompositeMonster::clone() const
{
	return (new CompositeMonster(*this));
}

void    	CompositeMonster::addMonster(CompositeMonsterProvider::monster &m)
{
	monsters.push_back(m);
}

