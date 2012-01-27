#include "PhysicManager.hpp"

#define	CUTTIME		100

PhysicManager::PhysicManager() : GameStateObserver("PhysicManager")
{
	this->_targetRate = 20;
}

PhysicManager::~PhysicManager()
{
}

void		PhysicManager::init()
{
}

void		PhysicManager::update(double elapsedTime)
{
	if (elapsedTime == 0)
		return ;

	for (std::list<GameState*>::const_iterator it = this->_glist.begin();
		it != this->_glist.end(); it++)
		PhysicManager::apply(**it, elapsedTime);
}

void		PhysicManager::apply(GameState &state, double elapsedTime)
{
	if (elapsedTime == 0 && (state.getPaused() & GameState::PHYSIC) != 0)
		return ;
	double		time;
	double		tmptime;
	GameObjectManager::collisionGroupsMap const
	&collisionGroups = state.getCollisionGroups();
	GameObjectManager::groupsMap const			&groups = state.getGroups();

	tmptime = elapsedTime;
	for (; tmptime >= 0; tmptime -= CUTTIME)
	{
		time = (((static_cast<int>(tmptime) / CUTTIME) > 0) ? CUTTIME : tmptime) / 1000;
		PhysicManager::move(groups, time);
		PhysicManager::collide(groups, collisionGroups);
	}
}

void		PhysicManager::destroy()
{
}

void		PhysicManager::move(GameObjectManager::groupsMap const &groups, double time)
{
	std::set<GameObject*>::const_iterator	it1, it2;
	double									timeEffect;

	if (!groups.size())
		return ;
	for (GameObjectManager::groupsMap::const_iterator itGroups = groups.begin();
		 itGroups != groups.end(); ++itGroups)
	{
		if (itGroups->second->getPhysic())
		{
			timeEffect = time * itGroups->second->getTimeEffect();
			for (it1 = itGroups->second->getObjects().begin();
				 it1 != itGroups->second->getObjects().end();)
			{
				it2 = it1++;
				static_cast<PhysicObject*>(*it2)->move(timeEffect);
				if (!(*it2)->isDelete())
					itGroups->second->getQuadTree().move(*static_cast<PhysicObject *>(*it2));
			}
		}
	}
	groups.begin()->second->getState().deleteObjects();
}

void		PhysicManager::collide(GameObjectManager::groupsMap const &groups,
				       GameObjectManager::collisionGroupsMap const &collisionGroups)
{
	GameObjectManager::groupsMap::const_iterator	itGroups, temp;
	std::set<GameObject*>::const_iterator			it1, it2;

	for (GameObjectManager::collisionGroupsMap::const_iterator itCol = collisionGroups.begin();
		 itCol != collisionGroups.end(); itCol++)
	{
		temp = groups.find(itCol->first.first);
		if (temp != groups.end())
		{
			itGroups = groups.find(itCol->first.second);
			if (itGroups != groups.end())
				temp->second->getQuadTree().collide(itGroups->second->getQuadTree(), QuadTree::LEFT);
		}
	}
	if (groups.size() != 0)
	  groups.begin()->second->getState().deleteObjects();
}
