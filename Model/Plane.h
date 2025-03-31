#pragma once
#include "Model.h"

#ifdef PLANE_LIBRARY_EXPORTS
#define PLANE_LIBRARY_API __declspec(dllexport)
#else
#define PLANE_LIBRARY_API __declspec(dllimport)
#endif

class PLANE_LIBRARY_API Plane: public Model
{
public:
	Plane();
	Plane(Vec, Point);
	~Plane();
	std::vector<double> modelError(const Plane&);
	std::string modelErrorStr(const Plane&);
public:
	inline	Vec		GetNormal() const { return normal; }
	inline	Point	GetPos()	const { return pos;}
	std::vector<double>	thetas() override;
private:
	Vec		normal;
	Point	pos;
};
