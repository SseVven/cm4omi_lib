#pragma once
#include "Model.h"
#ifdef CYLINDER_LIBRARY_EXPORTS
#define CYLINDER_LIBRARY_API __declspec(dllexport)
#else
#define CYLINDER_LIBRARY_API __declspec(dllimport)
#endif

class CYLINDER_LIBRARY_API Cylinder : public Model
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
