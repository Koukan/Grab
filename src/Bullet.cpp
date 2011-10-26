#include "Bullet.hpp"

Bullet::Bullet(BulletMLParser *state, CL_ResourceManager &resource)
	: BulletMLRunner(state)
{
  _sprite = new Sprite("bullet", resource);
}

Bullet::~Bullet()
{
}

double		Bullet::getBulletDirection()
{
  return 1;
}

double		Bullet::getAimDirection()
{
  return 1;
}

double		Bullet::getBulletSpeed()
{
  return 1;
}

double		Bullet::getDefaultSpeed()
{
  return 1;
}

double		Bullet::getRank()
{
  return 1;
}

void		Bullet::createSimpleBullet(double direction, double speed)
{
}

void		Bullet::createBullet(BulletMLState* state,
				     double direction, double speed)
{
}

int		Bullet::getTurn()
{
  return 1;
}

void		Bullet::doVanish()
{
}

void		Bullet::draw()
{
  _sprite->draw(_x, _y);
}
