#include "PolyHitBox.hpp"
#include "RectHitBox.hpp"
#include "CircleHitBox.hpp"


PolyHitBox::PolyHitBox(double x, double y, std::vector<std::pair<double, double> > &)
	: HitBox(x, y)//, _poly(new CL_CollisionOutline())
{
	//CL_Contour contour;
	//for (std::vector<std::pair<double, double> >::iterator it = points.begin(); it != points.end(); ++it)
	//{
		//contour.get_points().push_back(CL_Pointf(static_cast<float>(it->first), static_cast<float>(it->second)));
	//}
	//this->_poly->get_contours().push_back(contour);
	//this->_poly->set_translation(static_cast<float>(x), static_cast<float>(y));
	//this->_poly->calculate_radius();
	//this->_poly->calculate_sub_circles();
}

PolyHitBox::~PolyHitBox(void)
{
		//delete this->_poly;
}

//CL_CollisionOutline &PolyHitBox::getPoly() const
//{
		//return (*this->_poly);
//}

bool PolyHitBox::collideCircle(CircleHitBox &)
{
		//return (HitBox::CircleCollidePoly(circle, *this));
	return false;
}

bool PolyHitBox::collideRect(RectHitBox &)
{
		//return(HitBox::RectCollidePoly(rect, *this));
	return false;
}

bool PolyHitBox::collidePoly(PolyHitBox &)
{
	//this->_poly->set_translation(static_cast<float>(this->_x), static_cast<float>(this->_y));
	//poly.getPoly().set_translation(static_cast<float>(poly.getX()), static_cast<float>(poly.getY()));
	//return (this->_poly->collide(poly.getPoly()));
	return false;
}

bool PolyHitBox::collide(HitBox &)
{
	return false;
	//return (hitbox.collidePoly(*this));
}

int PolyHitBox::getWidth() const
{
	// a faire
	return (10);
}

int PolyHitBox::getHeight() const
{
	// a faire
	return (10);
}
