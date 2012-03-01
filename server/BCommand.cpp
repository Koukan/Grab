#include <math.h>
#include "Resources.hpp"
#include "BCommand.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "ServerResourceManager.hpp"
#include "CircleHitBox.hpp"
#include "RectHitBox.hpp"
#include "GameLogic.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline static double dtor(double x) { return x * M_PI / 180; }
inline static double rtod(double x) { return x * 180 / M_PI; }

BCommand::BCommand(std::string const &parser, Core::GameState &gstate,
		  double x, double y, double vx, double vy, int life)
	: BulletCommand(parser, gstate, x, y, vx, vy), _elapsedTime(0), _life(life)
{
}

BCommand::BCommand(BulletMLParser &parser, Core::GameState &gstate,
		  double x, double y, double vx, double vy, int life)
	: BulletCommand(parser, gstate, x, y, vx, vy), _elapsedTime(0), _life(life)
{
}

BCommand::BCommand(BulletMLState &state, Core::GameState &gstate,
		  double x, double y, double vx, double vy, int life)
	: BulletCommand(state, gstate, x, y, vx, vy), _elapsedTime(0), _life(life)
{
}

BCommand::BCommand(BulletMLState &state, Core::GameState &gstate, Core::HitBox &box,
		  double vx, double vy, int life)
	: BulletCommand(state, gstate, box, vx, vy), _elapsedTime(0), _life(life)
{
}

BCommand::~BCommand()
{
}

void	BCommand::createSimpleBullet(double direction, double speed)
{
	Bullet		*bullet = 0;
	Core::HitBox		*box = 0;
	double		vx, vy;
	double		dir = dtor(direction);

	if (_shape == BulletCommand::Circle)
	  box = new Core::CircleHitBox(_x, _y,
			static_cast<double>(_width));
	else if (_shape == BulletCommand::Rectangle)
	  box = new Core::RectHitBox(_x, _y,
			static_cast<double>(_width),
			static_cast<double>(_height));
	vx = speed * cos(dir);
	vy = speed * sin(dir);
	if (box)
	{
		bullet = new Bullet(*box, vx, vy);
		this->_state.addGameObject(bullet, this->_simpleGroup);
		GameCommand		*cmd = new GameCommand("Spawn");
		cmd->idObject = bullet->getId();
		cmd->idResource = ServerResourceManager::get().getId(this->_simpleSprite);
		cmd->x = static_cast<int16_t>(this->_x);
		cmd->y = static_cast<int16_t>(this->_y);
		cmd->vx = static_cast<int16_t>(vx);
		cmd->vy = static_cast<int16_t>(vy);
		cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
		Core::CommandDispatcher::get().pushCommand(*cmd);
	}
}

void	BCommand::createBullet(BulletMLState *state,
				double direction, double speed)
{
	BCommand	*bullet = 0;
	Core::HitBox		*box = 0;
	double		vx, vy;
	double		dir = dtor(direction);

	if (state->getShape() == "circle")
	  box = new Core::CircleHitBox(_x, _y,
			static_cast<double>(state->getRadius()));
	else if (state->getShape() == "rectangle")
	  box = new Core::RectHitBox(_x, _y,
			static_cast<double>(state->getWidth()),
			static_cast<double>(state->getHeight()));
	vx = speed * cos(dir);
	vy = speed * sin(dir);
	if (box)
	{
		bullet = new BCommand(*state, _state, *box, vx, vy, ServerResourceManager::get().getId(state->getSprite()));
		this->_state.addGameObject(bullet, state->getGroup());
	}
	else
	{
		bullet = new BCommand(*state, _state, _x, _y, vx, vy, ServerResourceManager::get().getId(state->getSprite()));
		this->_state.addGameObject(bullet, state->getGroup());
	}
	if (bullet)
	{
		GameCommand		*cmd = new GameCommand("Spawn");
		cmd->idObject = bullet->getId();
		cmd->idResource = ServerResourceManager::get().getId(state->getSprite());
		cmd->x = static_cast<int16_t>(this->_x);
		cmd->y = static_cast<int16_t>(this->_y);
		cmd->vx = static_cast<int16_t>(vx);
		cmd->vy = static_cast<int16_t>(vy);
		cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
		Core::CommandDispatcher::get().pushCommand(*cmd);
	}
	delete state;
}

void	BCommand::move(double time)
{
	this->_turn += time * 50;
	this->_elapsedTime += time;
	this->run();
	if (!this->_end)
	{
		this->PhysicObject::move(time);
		if (this->_elapsedTime > 0.15)
		{
			this->_elapsedTime -= 0.15;
			GameCommand	*cmd = new GameCommand("Move");
			cmd->idObject = this->_id;
			cmd->x = static_cast<int16_t>(this->_x);
			cmd->y = static_cast<int16_t>(this->_y);
			cmd->vx = static_cast<int16_t>(this->_vx);
			cmd->vy = static_cast<int16_t>(this->_vy);
			cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
			Core::CommandDispatcher::get().pushCommand(*cmd);
		}
	}
	else
	{
		GameCommand	*cmd = new GameCommand("Destroy");
		cmd->idObject = this->_id;
		cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
		Core::CommandDispatcher::get().pushCommand(*cmd);
		this->erase();
	}
}

int			BCommand::getLife() const
{
	return this->_life;
}

void		BCommand::setLife(int life)
{
	this->_life = life;
}
