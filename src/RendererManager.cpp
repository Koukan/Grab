#include "RendererManager.hpp"
#include "GameObjectManager.hpp"
#include "DrawableObject.hpp"

RendererManager::RendererManager(void)
{
}

RendererManager::~RendererManager(void)
{
}

void RendererManager::update(GameState &state, int elapsedTime)
{
	groupsMap::const_iterator it;
	std::set<GameObject*>::const_iterator it2;

	for (it = state.getGroups().begin(); it != state.getGroups().end(); ++it)
	{
		if ((*it).second.drawable)
		{
			for (it2 = (*it).second.objects.begin(); it2 != (*it).second.objects.end(); ++it2)
			{
				static_cast<DrawableObject *>((*it2))->draw();
			}
		}
	}
}