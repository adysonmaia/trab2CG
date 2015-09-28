#include "point.hpp"

Point3::Point3()
{
  this->X = (float) 0;
  this->Y = (float) 0;
  this->Z = (float) 0;
		
}

Point3::Point3(float X,float Y,float Z)
{
  this->X = X;
  this->Y = Y;
  this->Z = Z;
		
}

void Point3::setX(float X)
{
  this->X = X;

}

void Point3::setY(float Y)
{
  this->Y = Y;
}

void Point3::setZ(float Z)
{
  this->Z = Z;
}

float Point3::x() const
{
  return this->X; 
}

float Point3::y() const
{
  return this->Y;
}

float Point3::z() const
{
  return this->Z;
}

Point3 & Point3::operator*=(float fator)
{
  this->X *= fator;
  this->Y *= fator;
  this->Z *= fator;
  return *this;
}

Point3 & Point3::operator+= (const Point3 & point)
{
  this->X += point.X;
  this->Y += point.Y;
  this->Z += point.Z;
  return *this;
		
}

/*Vector3& Point3::operator-=(const Point3 & point)
{
  //Vector3 newvector(point,this);
  //return *newvector;
}*/

Point3 & Point3::operator/=(float divisor)
{
  this->X /= divisor;
  this->Y /= divisor;
  this->Z /= divisor;
  return *this;
}

Point3 & Point3::operator=(const Point3 & point)
{
  
	this->X = point.x();
        this->Y = point.y();
        this->Z = point.z();
	return *this;
		
}

bool Point3::operator==(const Point3 & point) const
{
  if(this->X == point.X && this->Y == point.Y && this->Z == point.Z )
    return true;
  return false;
}

bool Point3::operator!=(const Point3 & point) const
{
  if(this->X != point.X || this->Y != point.Y || this->Y != point.Y || this->Y != point.Y )
    return true;
  return false;
}





