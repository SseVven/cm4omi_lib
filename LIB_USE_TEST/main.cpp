#include <iostream>
#include <random>
#include "../SpaceMath/Geometry.h"
#include "../Model/Sphere.h"
#include "../Model/Plane.h"
#include "../Model/Cone.h"
#include "../Model/Cylinder.h"
#include "../Sample/SphereSampler.h"

#include "../Reconstruction/leastsq.h"
#include "../Reconstruction/reconstructor.h"

double getRandom(double a, double b) {
	// 定义随机数范围 {a, b}
	// 随机数引擎：使用 Mersenne Twister 算法
	std::random_device rd;  // 用于生成随机种子
	std::mt19937 gen(rd()); // 初始化随机数引擎
	// 定义均匀分布
	std::uniform_real_distribution<double> dist(a, b);
	double random_value = dist(gen); // 生成随机数
	return random_value;
}

std::vector<double> getRandomPoint(Point center, double radius) {
	double rph = getRandom(0, M_PI);
	double theta = getRandom(0, 2 * M_PI);
	return {center.x + radius * sin(rph) * cos(theta), 
		center.y + radius * sin(rph) * sin(theta), 
		center.z + radius * cos(rph)};
}

int main() {
	// 模型原始阶段
	Sphere sphere_standard(Point(20, 30, 40), 20);
	Sphere sphere_actual(Point(19.99807462, 30.00129321, 41.0002376), 21.000190102613473);
	//std::cout << sphere_standard.modelErrorStr(sphere_actual) << "\n";

	// 采样【根据CAD文件，设计采样点，指导探头进行测量】
	SphereSampler sampler = SphereSampler();
	std::vector<Point> sampleNodes = sampler.sample(sphere_standard, 9, Vec(1,0,0), M_PI / 3);
	// 测量

	// 拟合
	// 输入拟合类型，拟合的数据点，和初始的预测参数
	std::vector<std::vector<double>> data = { 
		{13.90945534, 40.5491328 , 61.09826561},
		{13.90974565, 19.45137004, 61.09725992},
		{32.18005038, 30.        , 61.09646609},
		{9.61367915 ,47.98963542 ,51.99309028},
		{9.61453703 ,12.01185047 ,51.99209968},
		{40.76957166, 30.        , 51.99131779},
		{8.25951173 ,50.33512219 ,40.},
		{8.26063173 , 9.6668177  ,40.},
		{43.4769685 , 30.        , 40.}};
	std::cout << "\nstart\n";
	// 
	reconstructor rc(&sphere_standard, data);
	std::vector<double> thetas = rc.fit();
	for (double x : thetas) {
		std::cout << x << " ";
	}
	std::cout << "\nend\n";
	return 0;
}

