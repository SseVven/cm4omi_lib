#include "pch.h"
#include "Plane.h"

Plane::Plane()
	: Model(ModelType::PlaneType),
	normal(Vec(0, 0, 1)),
	pos(Point())
{
}
Plane::Plane(Vec vec, Point pos)
	: Model(ModelType::PlaneType),
	normal(vec),
	pos(pos)
{
}

Plane::~Plane()
{
}

// 法向与真实法向的夹角 rad
std::vector<double> Plane::modelError(const Plane& model) {
	return { GEOMETRY::Geom_VecInnerAngle(model.normal, this->normal) };
}

std::string Plane::modelErrorStr(const Plane& model) {
	std::vector<double> data = this->modelError(model);
	std::string normalError = "normal error:\t" + std::to_string(data[0]) 
		+ "(" + std::to_string(GEOMETRY::Geom_Rad2Degree(data[0])) + "°)";
	return normalError;
}

std::vector<double>	Plane::thetas() {
	return {GetNormal().x, GetNormal().y, GetNormal().z, GetPos().x, GetPos().y, GetPos().z };
}