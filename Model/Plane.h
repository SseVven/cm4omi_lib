#pragma once
#include "Model.h"

class Plane: public Model
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
