#include "PhysicObject.hpp"

PhysicObject::PhysicObject(double x, double y) :
  DrawableObject(x, y), _vx(0), _vy(0)
{
}

PhysicObject::~PhysicObject(void)
{
}

double PhysicObject::getVx() const
{
	return (this->_vx);
}

double PhysicObject::getVy() const
{
	return (this->_vy);
}

void PhysicObject::setVx(double vx)
{
	this->_vx = vx;
}

void PhysicObject::setVy(double vy)
{
	this->_vy = vy;
}

bool PhysicObject::collide(PhysicObject &obj)
{
  PhysicObject *mvt;
  PhysicObject *other;

  if (obj.getVx() != 0 || obj.getVy() != 0)
    {
      mvt = &obj;
      other = this;
    }
  else
    {
      mvt = this;
      other = &obj;
    }
  int x1 = (_x - 238) / 75 * 75;
  int x2 = (mvt->getX() - 238) / 75 * 75;
  int y1 = _y / 75 * 75;
  int y2 = mvt->getY() / 75 * 75;

  // if ((mvt->getVx() > 0 && x2 >= x1 + 75 / 2 && x2 <= x1 + 75 && y2 >= y1 && y2 <= y1 + 75)/* ||
  //     (mvt->getVx() < 0 && x2 >= x1 && x2 <= x1 + 75 / 2 && y2 >= y1 && y2 <= y1 + 75) ||
  //      (mvt->getVy() > 0 && x2 >= x1 && x2 <= x1 + 75 && y2 >= y1 && y2 <= y1 + 75 / 2) ||
  //      (mvt->getVy() < 0 && x2 >= x1 && x2 <= x1 + 75 && y2 >= y1 + 75 / 2 && y2 <= y1 + 75)*/)
  //   return true;


   if (x2 >= x1 + 75 / 2 && x2 <= x1 + (75 / 3 * 2) &&
    y2 >= y1 && y2 <= y1 + 75 / 3)
    {
      return true;
    }
  return false;
}
