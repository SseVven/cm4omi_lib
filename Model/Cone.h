#pragma once
#include "Model.h"

class Cone : public Model
{
public:
	Cone();
	Cone(Point vertex, Vec axis, double angle);
	~Cone();
	std::vector<double> modelError(const Cone&);
	std::string modelErrorStr(const Cone&);
public:
	inline	Point	GetVertex()	const { return vertex; }
	inline	Vec		GetAxis()	const { return axis; }
	inline	double	GetAngle()	const { return angle; }
	std::vector<double>	thetas() override;
private:
	Point	vertex;
	Vec		axis;
	double	angle;
};
