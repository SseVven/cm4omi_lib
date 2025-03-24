#pragma once
#include "Model.h"

class Cylinder : public Model
{
public:
	Cylinder();
	Cylinder(Point pos, Vec axis, double radius);
	~Cylinder();
	std::vector<double> modelError(const Cylinder&);
	std::string modelErrorStr(const Cylinder&);
public:
	inline	Point	GetPos()	const { return pos; }
	inline	Vec		GetAxis()	const { return axis; }
	inline	double	GetRadius()	const { return radius; }
	std::vector<double>	thetas() override;
private:
	Point	pos;
	Vec		axis;
	double	radius;
};
