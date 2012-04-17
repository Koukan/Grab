#pragma once

#include <map>
#include "BulletCommand.hpp"

class 	CompositeNode;

class	CompositeMaster : public Core::BulletCommand
{
	public:
			CompositeMaster(std::string const &script, Core::GameState &gstate);
			~CompositeMaster();

			void	createBullet(BulletMLState* state, double direction, double speed);
			void	notifyDeath(CompositeNode &node);
			void	registerCompositeNode(CompositeNode &node, std::list<std::string>  const &dependencies);
			Core::BulletCommand	*getBullet() const;
				
	private:
			std::map<CompositeNode*, std::list<std::string> >	_dependencies;
			Core::GameState										&_state;
			size_t												_count;
			Core::BulletCommand 								*_bullet;
};
