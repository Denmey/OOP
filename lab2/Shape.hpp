#pragma once
#include "Vectors.hpp"
#include <iostream>

class Shape
{
public:
	Shape()
	{
		static int _ID = 0;
		++_ID;
		ID = _ID;
	}
	const V3i& getColor() const;
	const V3d& getPos() const;
	double getAngle() const;
	int getID() const;
	void setColor(const V3i& newColor);
	virtual void setPos(const V3d& newPos);
	void setAngle(double newAngle);
	virtual void scale(double sc) = 0;
	virtual void print() const = 0;
	friend std::ostream& operator<<(std::ostream& ostr, const Shape& s);
protected:
	V3d Pos;
	V3i Color;
	double Angle;
private:
	int ID;
};
