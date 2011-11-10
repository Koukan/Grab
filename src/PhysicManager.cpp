#include "PhysicManager.hpp"
#include "Game.hpp"

#define	CUTTIME		100

PhysicManager::PhysicManager()
{
	Game::get().loadManager(this);
}

PhysicManager::~PhysicManager()
{
}

void		PhysicManager::update(GameState &state, double elapsedTime)
{
  if (elapsedTime == 0)
    return ;

  collisionGroupsMap const	&collisionGroups = state.getCollisionGroups();
  groupsMap const		&groups = state.getGroups();
  double			time;

  for (; elapsedTime >= 0; elapsedTime -= CUTTIME)
  {
    time = (((static_cast<int>(elapsedTime) / CUTTIME) > 0) ? CUTTIME : elapsedTime) / 1000;
    this->move(groups, time);
    this->collide(groups, collisionGroups);
  }
}

void		PhysicManager::move(groupsMap const &groups, double time)
{
  std::set<GameObject*>::const_iterator		it1, it2;
  double					timeEffect;

  if (!groups.size())
	  return ;
  for (groupsMap::const_iterator itGroups = groups.begin();
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

void		PhysicManager::collide(groupsMap const &groups,
				       collisionGroupsMap const &collisionGroups)
{
  groupsMap::const_iterator			itGroups, temp;
  std::set<GameObject*>::const_iterator		it1, it2;

  for (collisionGroupsMap::const_iterator itCol = collisionGroups.begin();
       itCol != collisionGroups.end(); itCol++)
  {
    temp = groups.find(itCol->first.first);
    if (temp != groups.end())
    {
      for (it1 = temp->second->getObjects().begin();
		  it1 != temp->second->getObjects().end() && !(*it1)->isDelete(); it1++)
      {
		  itGroups = groups.find(itCol->first.second);
		  if (itGroups != groups.end())
			  itGroups->second->getQuadTree().collide(*static_cast<PhysicObject *>(*it1));
      }
    }
  }
  groups.begin()->second->getState().deleteObjects();
}
