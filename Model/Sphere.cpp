#include "pch.h"
#include "Sphere.h"

Sphere::Sphere()
	:Model(ModelType::SphereType), 
	center(Point()),
	radius(0)
{
}

Sphere::Sphere(Point center, double radius)
	:Model(ModelType::SphereType),
	center(center),
	radius(radius)
{
}

Sphere::~Sphere()
{
}

// 中心偏移距离，半径误差
// this 为真实的参数，model为预测的模型参数，输出为 model - this
std::vector<double> Sphere::modelError(const Sphere& model) {
	Point center = model.center;
	double centerDistance = GEOMETRY::Geom_PosDistance(this->center, center);
	double radiusError = model.radius - this->radius;
	return {centerDistance, radiusError};
}

std::string Sphere::modelErrorStr(const Sphere& model) {
	std::vector<double> data = this->modelError(model);
	std::string centerDistance = "center error:\t" + std::to_string(data[0]) + MODEL_LENGTH_UNIT + "\n";
	std::string radiusError = "radius error:\t" + std::to_string(data[1]) + MODEL_LENGTH_UNIT;
	return centerDistance + radiusError;
}

std::vector<double>	Sphere::thetas() {
	return { GetCenter().x, GetCenter().y, GetCenter().z, GetRadius() };
}
