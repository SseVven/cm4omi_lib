#pragma once
#include "Model.h"
#ifdef SPHERE_LIBRARY_EXPORTS
#define SPHERE_LIBRARY_API __declspec(dllexport)
#else
#define SPHERE_LIBRARY_API __declspec(dllimport)
#endif

class SPHERE_LIBRARY_API Sphere : public Model
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
