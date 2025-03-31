#pragma once
#include "../Model/Model.h"
#include "leastsq.h"

// 负责 带半径补偿的迭代拟合
#ifdef RECONSTRUCTION_LIBRARY_EXPORTS
#define RECONSTRUCTION_LIBRARY_API __declspec(dllexport)
#else
#define RECONSTRUCTION_LIBRARY_API __declspec(dllimport)
#endif
class RECONSTRUCTION_LIBRARY_API reconstructor
{
public:
	reconstructor(Model* model, std::vector<std::vector<double>> data);
	~reconstructor();

	std::vector<double> fit(double tol=1e-4, int maxIter=10);
private:
	Model* model;
	std::vector<std::vector<double>> data;
private:
	std::vector<std::vector<double>> radiusCompensate(std::vector<double>, Model::ModelType);
	std::vector<std::vector<double>> planeComp(std::vector<double>);
	std::vector<std::vector<double>> sphereComp(std::vector<double>);
	std::vector<std::vector<double>> cylinderComp(std::vector<double>);
	std::vector<std::vector<double>> coneComp(std::vector<double>);
};
