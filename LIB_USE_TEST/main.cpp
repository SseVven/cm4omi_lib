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
	//// 模型原始阶段
	//Sphere sphere_standard(Point(20, 30, 40), 20);
	//Sphere sphere_actual(Point(19.99807462, 30.00129321, 41.0002376), 21.000190102613473);
	////std::cout << sphere_standard.modelErrorStr(sphere_actual) << "\n";

	//// 采样【根据CAD文件，设计采样点，指导探头进行测量】
	//SphereSampler sampler = SphereSampler();
	//std::vector<Point> sampleNodes = sampler.sample(sphere_standard, 9, Vec(1,0,0), M_PI / 3);
	//// 测量

	//// 拟合
	//// 输入拟合类型，拟合的数据点，和初始的预测参数
	//std::vector<std::vector<double>> data = { 
	//	{13.90945534, 40.5491328 , 61.09826561},
	//	{13.90974565, 19.45137004, 61.09725992},
	//	{32.18005038, 30.        , 61.09646609},
	//	{9.61367915 ,47.98963542 ,51.99309028},
	//	{9.61453703 ,12.01185047 ,51.99209968},
	//	{40.76957166, 30.        , 51.99131779},
	//	{8.25951173 ,50.33512219 ,40.},
	//	{8.26063173 , 9.6668177  ,40.},
	//	{43.4769685 , 30.        , 40.}};
	//
	//
	//std::cout << "\nstart\n";
	//// 
	//reconstructor rc(&sphere_standard, data);
	//std::vector<double> thetas = rc.fit();
	//for (double x : thetas) {
	//	std::cout << x << " ";
	//}
	//std::cout << "\nend\n";
	//return 0;

	/*************************平面***************************/
	//Plane plane_standard(Vec(0, 0, 1), Point(20, 30, 40));
	//Plane plane_actual(Vec(0.01293751, -0.0042886, 0.99990711), Point(20.00050656, 29.99811065, 40.00075931));

	//std::vector<std::vector<double>> data = { 
	//	{30.0000000000000, 30.0000000000000, 42.3716190985404},
	//	{27.6604444311898, 36.4278760968654, 42.4294590940678},
	//	{21.7364817766693, 39.8480775301221, 42.5207767800347},
	//	{15.0000000000000, 38.6602540378444, 42.6028435962941},
	//	{10.6030737921409, 33.4202014332567, 42.63725956744748},
	//	{10.6030737921409, 26.5797985667433, 42.6079210781009},
	//	{15.0000000000000, 21.3397459621556, 42.5285559334803},
	//	{21.7364817766693, 20.1519224698779, 42.4362999668002},
	//	{27.6604444311898, 23.5721239031346, 42.3743207701799}};
	//
	//std::cout << "\nstart\n";
	//// 
	//reconstructor rc(&plane_standard, data);
	//std::vector<double> thetas = rc.fit();
	//for (double x : thetas) {
	//	std::cout << x << " ";
	//}
	//std::cout << "\nend\n";
	//return 0;
	/*************************平面***************************/

	/*************************圆柱***************************/
	//Cylinder cylinder_standard(Point(20, 40, 30),Vec(0, 0, 1),20);
	//Cylinder cylinder_actual(Point(20.00003046,39.99976466,30.00097144),Vec(2.78216323e-03,- 7.11886407e-04,9.99995876e-01), 19.998);

	//std::vector<std::vector<double>> data = {
	//	{35.926135098549544, 24.073864901450456, 40.0},
	//	{42.525935356767704, 40.0, 40.0},
	//	{35.91874358996205, 55.91874358996205, 40.0},
	//	{35.94359534534834, 24.056404654651658, 50.0},
	//	{42.55375363656873, 40.0, 50.0},
	//	{35.92906603137219, 55.92906603137219, 50.0},
	//	{35.961048856597365, 24.038951143402635, 60.0},
	//	{42.581569663776335, 40.0, 60.0},
	//	{35.93936928724671, 55.93936928724671, 60.0}};
	//	
	//std::cout << "\nstart\n";
	//// 
	//reconstructor rc(&cylinder_standard, data);
	//std::vector<double> thetas = rc.fit();
	//for (double x : thetas) {
	//	std::cout << x << " ";
	//}
	//std::cout << "\nend\n";
	//return 0;
	/*************************圆柱***************************/

	/*************************cone***************************/
	double s_height = 40;
	Vec s_vec = Vec(0, 0, 1);
	Point s_bp = Point(20, 40, 30); // 标称的圆锥底面中心
	Point s_tp = s_bp + s_vec * s_height; // 标称的圆锥锥点
	Cone cone_standard(s_tp, s_vec, 0.927295218001612);
	// 实际cone参数不参与运算，只给我们一个拟合后的对比参看
	double a_height = 40;
	Vec a_vec = Vec(0.010156064710623948, -0.004186331321546835, 0.9999396626695332);
	Point a_bp = Point(20.000319169987822, 40.00045980044738, 29.99917131787309);
	Point a_tp = a_bp + a_vec * a_height;
	Cone cone_actual(a_tp, a_vec, 0.929294217835695);

	std::vector<std::vector<double>> data = {
		{28.08532736152396, 54.00419778598631, 43.33333333333333},
		{11.940997474310906, 53.958601832819426, 43.33333333333333},
		{3.8898525637580974, 40.0, 43.33333333333333},
		{11.922829647701983, 26.00993056843084, 43.33333333333333},
		{28.104301293563697, 25.962938399701507, 43.33333333333333},
		{24.754067652978776, 48.23428671757896, 56.666666666666664},
		{15.356232641332355, 48.04324100374229, 56.666666666666664},
		{10.743996175204051, 40.0, 56.666666666666664},
		{15.278321582379286, 31.821813083679515, 56.666666666666664},
		{24.834274728878956, 31.62679055183539, 56.666666666666664},
	};
	std::cout << "start\n";
	 
	reconstructor rc(&cone_standard, data);
	std::vector<double> thetas = rc.fit();
	for (double x : thetas) {
		std::cout << x << " ";
	}
	std::cout << "\nend\n";
	system("pause");
	return 0;
	/*************************cone***************************/
}

