#include "pch.h"
#include "Cylinder.h"

Cylinder::Cylinder()
	:Model(ModelType::CylinderType),
	pos(Point()),
	axis(Vec(0,0,1)),
	radius(0)
{
}

Cylinder::Cylinder(Point pos, Vec axis, double radius)
	:Model(ModelType::CylinderType),
	pos(pos),
	axis(axis),
	radius(radius)
{
}

Cylinder::~Cylinder()
{
}

// 轴向的夹角，半径的误差
// this 为真实的参数，model为预测的模型参数，输出为 model - this
std::vector<double> Cylinder::modelError(const Cylinder& model) {
	double axisIncludeAngle = GEOMETRY::Geom_VecInnerAngle(this->axis, model.axis);
	double radiusError = model.radius - this->radius;
	return { axisIncludeAngle ,radiusError };
}

std::string Cylinder::modelErrorStr(const Cylinder& model) {
	std::vector<double> data = this->modelError(model);
	std::string axisError = "axis error:\t" + std::to_string(data[0])
		+ "(" + std::to_string(GEOMETRY::Geom_Rad2Degree(data[0])) + "°)\n";
	std::string radiusError = "radius error:\t" + std::to_string(data[1]) + MODEL_LENGTH_UNIT;
	return axisError + radiusError;
}

std::vector<double>	Cylinder::thetas() {
	return { GetPos().x, GetPos().y, GetPos().z, GetAxis().x, GetAxis().y, GetAxis().z, GetRadius() };
}
