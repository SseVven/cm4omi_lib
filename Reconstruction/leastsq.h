#pragma once
#include <vector>
#include "../Model/Model.h"

// 残差函数，输入预计参数和拟合数据
using residuals = std::vector<double>(*)(std::vector<double>, std::vector<std::vector<double>>);

class leastsq
{
public:
	leastsq(residuals, std::vector<std::vector<double>>, std::vector<double>);
	leastsq(Model::ModelType, std::vector<std::vector<double>>, std::vector<double>);
	~leastsq();
public:
	std::vector<double> fit(double tol = 1e-6, int maxIter = 100);
private:
	residuals m_func;
	std::vector<std::vector<double>> m_data;
	std::vector<double> m_params;
};
//int maxIter = 100;

