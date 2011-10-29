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
  collisionGroupsMap::const_iterator			itCol;
  std::set<GameObject*>::const_iterator			it1, it2;
  int							time;
  for (; elapsedTime >= 0; elapsedTime -= CUTTIME)
  {
    time = (((elapsedTime / CUTTIME) > 0) ? CUTTIME : elapsedTime) / 5;
    for (itGroups = groups.begin(); itGroups != groups.end(); ++itGroups)
    {
      if ((*itGroups).second->getPhysic())
      {
	for (it1 = itGroups->second->getObjects().begin(); it1 != itGroups->second->getObjects().end();)
	{
	  it2 = it1++;
	  static_cast<PhysicObject*>(*it2)->move(time);
	}
        itGroups->second->deleteObjects();
      }
    }
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
	      itCol->second->call(*it1, *it2);
          }
	}
      }
    }
  }
}
