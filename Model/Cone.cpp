#include "pch.h"
#include "Cone.h"

Cone::Cone()
	:Model(ModelType::ConeType),
	vertex(Point()),
	axis(Vec(0, 0, 1)),
	angle(0)
{
}

Cone::Cone(Point vertex, Vec axis, double angle)
	:Model(ModelType::ConeType),
	vertex(vertex),
	axis(axis),
	angle(angle)
{
}

Cone::~Cone()
{
}

// 顶点的位置偏差，轴向的夹角, 顶角的角度差
// this 为真实的参数，model为预测的模型参数，输出为 model - this
std::vector<double> Cone::modelError(const Cone& model) {
	double vertexDistance = GEOMETRY::Geom_PosDistance(this->vertex, model.vertex);
	double axisIncludeAngle = GEOMETRY::Geom_VecInnerAngle(this->axis, model.axis);
	double angleError = model.angle - this->angle;
	return { vertexDistance, axisIncludeAngle, angleError};
}

std::string Cone::modelErrorStr(const Cone& model) {
	std::vector<double> data = this->modelError(model);
	std::string vertexDistance = "vertex error:\t" + std::to_string(data[0]) + MODEL_LENGTH_UNIT + "\n";
	std::string axisError = "axis error:\t" + std::to_string(data[1])
		+ "(" + std::to_string(GEOMETRY::Geom_Rad2Degree(data[1])) + "°)\n";
	std::string angleError = "angle error:\t" + std::to_string(data[2])
		+ "(" + std::to_string(GEOMETRY::Geom_Rad2Degree(data[2])) + "°)";
	return vertexDistance + axisError + angleError;
}

std::vector<double>	Cone::thetas() {
	return { GetVertex().x, GetVertex().y, GetVertex().z, GetAxis().x, GetAxis().y, GetAxis().z, GetAngle() };
}
