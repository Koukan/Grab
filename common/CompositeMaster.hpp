#pragma once

#include <map>
#include "BulletCommand.hpp"

class 	CompositeNode;

class	CompositeMaster : public Core::BulletCommand
{
	public:
			CompositeMaster(std::string const &script, Core::GameState &gstate);
			~CompositeMaster();

			void	notifyDeath(CompositeNode &node);
			void	registerCompositeNode(CompositeNode &node, std::list<std::string>  const &dependencies);
				
	private:
			std::map<std::string, std::list<std::string> >		_dependencies;
			Core::GameState										_state;
};
