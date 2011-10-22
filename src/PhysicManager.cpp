#include "PhysicManager.hpp"
#include "PhysicObject.hpp"
#include "Game.hpp"

#define	CUTTIME		100

PhysicManager::PhysicManager()
{
	Game::get().loadManager(this);
}

PhysicManager::~PhysicManager()
{
}

void		PhysicManager::update(GameState &state, int elapsedTime)
{
  if ((state.getPaused() & GameState::DRAW) == GameState::DRAW)
    return ;

  collisionGroupsMap const				&collisionGroups = state.getCollisionGroups();
  groupsMap const					&groups = state.getGroups();
  groupsMap::const_iterator				itGroups,temp;
  collisionGroupsMap::const_iterator	itCol;
  std::set<GameObject*>::const_iterator	it1, it2;
  int time;
  for (; elapsedTime >= 0; elapsedTime -= CUTTIME)
  {
	  time = ((elapsedTime / CUTTIME) > 0) ? CUTTIME : elapsedTime;
    for (itCol = collisionGroups.begin(); itCol != collisionGroups.end(); itCol++)
    {
      temp = groups.find(itCol->first.first);
      if (temp != groups.end())
      {
	for (it1 = temp->second->getObjects().begin(); it1 != temp->second->getObjects().end(); it1++)
        {
	  itGroups = groups.find(itCol->first.second);
          for (it2 = itGroups->second->getObjects().begin(); it2 != itGroups->second->getObjects().end(); it2++)
          {
	    if ((static_cast<PhysicObject*>(*it1))->collide(*(static_cast<PhysicObject*>(*it2))))
	      itCol->second->callInstance(*it1, *it2);
          }
	}
      }
    }
    for (itGroups = groups.begin(); itGroups != groups.end(); ++itGroups)
    {
      if ((*itGroups).second->getPhysic())
      {
		for (it2 = itGroups->second->getObjects().begin(); it2 != itGroups->second->getObjects().end(); ++it2)
		{
			(*it2)->setX((*it2)->getX() + (static_cast<PhysicObject*>(*it2))->getVx() * time / 5);
			(*it2)->setY((*it2)->getY() + (static_cast<PhysicObject*>(*it2))->getVy() * time / 5);
		}
      itGroups->second->deleteObjects();
	  }
    }
  }
}
