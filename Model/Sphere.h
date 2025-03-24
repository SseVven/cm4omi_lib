#pragma once
#include "Model.h"

class Sphere : public Model
{
public:
	Sphere();
	Sphere(Point center, double radius);
	~Sphere();
	std::vector<double> modelError(const Sphere&);
	std::string modelErrorStr(const Sphere&);
public:
	inline	Point	GetCenter() const { return center; }
	inline	double	GetRadius() const { return radius; }
	std::vector<double>	thetas() override;
private:
	Point	center;
	double	radius;
};
