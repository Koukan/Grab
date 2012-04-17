#pragma once

#include "BulletCommand.hpp"

class	CompositeMaster;

class	CompositeNode : public Core::BulletCommand
{
	public:
			CompositeNode(CompositeMaster &parent, std::string const &name, std::string const &script, Core::GameState &gstate);
			~CompositeNode();
			void	createBullet(BulletMLState* state, double direction, double speed);
			void	erase();
			std::string	const &getName();
		
	private:
			CompositeMaster		&_parent;
			std::string			_name;	
};
