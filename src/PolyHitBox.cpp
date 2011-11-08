#include "PolyHitBox.hpp"
#include "RectHitBox.hpp"
#include "CircleHitBox.hpp"


PolyHitBox::PolyHitBox(double x, double y, std::vector<std::pair<double, double> > &points)
	: HitBox(x, y), _poly(new CL_CollisionOutline())
{
	CL_Contour contour;
	for (std::vector<std::pair<double, double> >::iterator it = points.begin(); it != points.end(); ++it)
	{
		contour.get_points().push_back(CL_Pointf(it->first, it->second));
	}
	this->_poly->get_contours().push_back(contour);
	this->_poly->set_translation(x, y);
	this->_poly->calculate_radius();
	this->_poly->calculate_sub_circles();
}

PolyHitBox::~PolyHitBox(void)
{
	delete this->_poly;
}

CL_CollisionOutline &PolyHitBox::getPoly() const
{
	return (*this->_poly);
}

bool PolyHitBox::collideCircle(CircleHitBox &circle)
{
	return (HitBox::CircleCollidePoly(circle, *this));
}

bool PolyHitBox::collideRect(RectHitBox &rect)
{
	return(HitBox::RectCollidePoly(rect, *this));
}

bool PolyHitBox::collidePoly(PolyHitBox &poly)
{
	this->_poly->set_translation(this->_x, this->_y);
	poly.getPoly().set_translation(poly.getX(), poly.getY());
	return (this->_poly->collide(poly.getPoly()));
}

bool PolyHitBox::collide(HitBox &hitbox)
{
	return (hitbox.collidePoly(*this));
}
