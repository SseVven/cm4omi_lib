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

#include "../api/IMDSurfAnalyze.h"
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
	/*************************sphere***************************/
	//Plane plane_standard(Vec(0, 0, 1), Point(20, 30, 40));
	//Plane plane_actual(Vec(0.01293751, -0.0042886, 0.99990711), Point(20.00050656, 29.99811065, 40.00075931));
	IMDA_sphere_input_s* sp_input = new IMDA_sphere_input_s;
	IMDA_sphere_result_s* sp_result = new IMDA_sphere_result_s;
	sp_input->position_count = 9;
	double* sp_oringin_pts = new double[3 * sp_input->position_count];
	double* sp_detect_pts = new double[3 * sp_input->position_count];
	double* sp_detect_dir = new double[3 * sp_input->position_count];
	std::vector<std::vector<double>> sp_oringin_data = {
		{15.,         38.66025404, 57.32050808},
		{15.         ,21.33974596, 57.32050808},
		{30.         ,30.         ,57.32050808},
		{11.33974596 ,45.         ,50.},
		{11.33974596 ,15.         ,50.},
		{37.32050808 ,30.         ,50.},
		{10.         ,47.32050808 ,40.},
		{10.         ,12.67949192 ,40.},
		{40.         ,30.         ,40.        } };
	std::vector<std::vector<double>> sp_data = {
		{14.04142775, 40.32054988, 60.64109976},
		{14.2287793,  20.00395253, 59.99209494},
		{31.55368424, 30.        , 60.01156812},
		{9.49345686, 48.19786654, 52.13191103},
		{10.05898286, 12.78165323, 51.47889785},
		{39.91558581, 30.        , 51.49826883},
		{7.75785361, 51.20401954, 40.},
		{8.51546474, 10.10820142, 40.},
		{43.01383428, 30.       ,  40.} };
	for (int i = 0;i < sp_input->position_count;i++) {
		for (int j = 0;j < 3;j++) {
			sp_oringin_pts[i * 3 + j] = sp_oringin_data[i][j];
			sp_detect_pts[i * 3 + j] = sp_data[i][j];
		}
	}
	sp_input->oringin_pts = sp_oringin_pts;
	sp_input->detect_pts = sp_detect_pts;
	sp_input->detect_dir = sp_detect_dir;
	sp_input->sphere_root[0] = 20;
	sp_input->sphere_root[1] = 30;
	sp_input->sphere_root[2] = 40;
	sp_input->sphere_radius = 2.5;
	sp_input->probe_radius = 2.5;
	std::cout << "\nstart\n";

	IMDA_analyze_sphere(sp_input, sp_result);
	std::cout << "input_position_tol(max_error,min_error,square_error): " << sp_input->position_tol.max_error << ", " << sp_input->position_tol.min_error << ", " << sp_input->position_tol.square_error << "\n";
	std::cout << "result_position_tol(max_error,min_error,square_error): " << sp_result->position_tol.max_error << ", " << sp_result->position_tol.min_error << ", " << sp_result->position_tol.square_error << "\n";
	std::cout << "sphere_root: " << sp_result->sphere_root[0] << ", " << sp_result->sphere_root[1] << ", " << sp_result->sphere_root[2] << "\n";
	std::cout << "sphere_radius: " << sp_result->sphere_radius << "\n";
	std::cout << "concentricity_tol: " << sp_result->concentricity_tol << "\n";
	std::cout << "\nend\n";
	/*************************sphere***************************/

	/*************************平面***************************/
	//Plane plane_standard(Vec(0, 0, 1), Point(20, 30, 40));
	//Plane plane_actual(Vec(0.01293751, -0.0042886, 0.99990711), Point(20.00050656, 29.99811065, 40.00075931));
	IMDA_plane_input_s* pl_input = new IMDA_plane_input_s;
	IMDA_plane_result_s* pl_result = new IMDA_plane_result_s;
	pl_input->position_count = 9;
	double* pl_oringin_pts = new double[3 * pl_input->position_count];
	double* pl_detect_pts = new double[3 * pl_input->position_count];
	double* pl_detect_dir = new double[3 * pl_input->position_count];
	std::vector<std::vector<double>> pl_oringin_data_dir = {
		{0,0,-1},
		{0,0,-1},
		{0,0,-1},
		{0,0,-1},
		{0,0,-1},
		{0,0,-1},
		{0,0,-1},
		{0,0,-1},
		{0,0,-1}};
	std::vector<std::vector<double>> pl_oringin_data = {
		{30.0, 30.0, 40.0},
		{27.66044443118978, 36.42787609686539, 40.0},
		{21.736481776669304, 39.84807753012208, 40.0},
		{15.000000000000002, 38.66025403784439, 40.0},
		{10.603073792140917, 33.420201433256686, 40.0},
		{10.603073792140915, 26.579798566743314, 40.0},
		{14.999999999999996, 21.339745962155618, 40.0},
		{21.7364817766693, 20.151922469877917, 40.0},
		{27.660444431189777, 23.572123903134603, 40.0} };
	std::vector<std::vector<double>> pl_data = { 
		{30.0000000000000, 30.0000000000000, 42.3716190985404},
		{27.6604444311898, 36.4278760968654, 42.4294590940678},
		{21.7364817766693, 39.8480775301221, 42.5207767800347},
		{15.0000000000000, 38.6602540378444, 42.6028435962941},
		{10.6030737921409, 33.4202014332567, 42.63725956744748},
		{10.6030737921409, 26.5797985667433, 42.6079210781009},
		{15.0000000000000, 21.3397459621556, 42.5285559334803},
		{21.7364817766693, 20.1519224698779, 42.4362999668002},
		{27.6604444311898, 23.5721239031346, 42.3743207701799}};
	for (int i = 0;i < pl_input->position_count;i++) {
		for (int j = 0;j < 3;j++) {
			pl_detect_dir[i * 3 + j] = pl_oringin_data_dir[i][j];
			pl_oringin_pts[i * 3 + j] = pl_oringin_data[i][j];
			pl_detect_pts[i * 3 + j] = pl_data[i][j] + pl_oringin_data_dir[i][j] * 2.5;
		}
	}
	pl_input->oringin_pts = pl_oringin_pts;
	pl_input->detect_dir = pl_detect_dir;
	pl_input->detect_pts = pl_detect_pts;
	pl_input->plane_root[0] = 20;
	pl_input->plane_root[1] = 30;
	pl_input->plane_root[2] = 40;
	pl_input->plane_normal[0] = 0;
	pl_input->plane_normal[1] = 0;
	pl_input->plane_normal[2] = 1;
	pl_input->probe_radius = 2.5;
	std::cout << "\nstart\n";

	IMDA_analyze_plane(pl_input, pl_result);
	std::cout << "input_position_tol(max_error,min_error,square_error): " << pl_input->position_tol.max_error << ", " << pl_input->position_tol.min_error << ", " << pl_input->position_tol.square_error << "\n";
	std::cout << "result_position_tol(max_error,min_error,square_error): " << pl_result->position_tol.max_error << ", " << pl_result->position_tol.min_error << ", " << pl_result->position_tol.square_error << "\n";
	std::cout << "plane_root: " << pl_result->plane_root[0] << ", " << pl_result->plane_root[1] << ", " << pl_result->plane_root[2] << "\n";
	std::cout << "plane_normal: " << pl_result->plane_normal[0] << ", " << pl_result->plane_normal[1] << ", " << pl_result->plane_normal[2] << "\n";
	std::cout << "flatness_tol: " << pl_result->flatness_tol <<"\n";
	std::cout << "\nend\n";
	/*************************平面***************************/

	/*************************圆柱***************************/
	//Cylinder cylinder_standard(Point(20, 40, 30),Vec(0, 0, 1),20);
	//Cylinder cylinder_actual(Point(20.00003046,39.99976466,30.00097144),Vec(2.78216323e-03,- 7.11886407e-04,9.99995876e-01), 19.998);
	IMDA_cylinder_input_s* cy_input = new IMDA_cylinder_input_s;
	IMDA_cylinder_result_s* cy_result = new IMDA_cylinder_result_s;
	cy_input->position_count = 9;
	double* cy_oringin_pts = new double[3 * cy_input->position_count];
	double* cy_detect_pts = new double[3 * cy_input->position_count];
	double* cy_detect_dir = new double[3 * cy_input->position_count];
	std::vector<std::vector<double>> cy_data = {
		{35.926135098549544, 24.073864901450456, 40.0},
		{42.525935356767704, 40.0, 40.0},
		{35.91874358996205, 55.91874358996205, 40.0},
		{35.94359534534834, 24.056404654651658, 50.0},
		{42.55375363656873, 40.0, 50.0},
		{35.92906603137219, 55.92906603137219, 50.0},
		{35.961048856597365, 24.038951143402635, 60.0},
		{42.581569663776335, 40.0, 60.0},
		{35.93936928724671, 55.93936928724671, 60.0}};
	for (int i = 0;i < pl_input->position_count;i++) {
		for (int j = 0;j < 3;j++) {
			cy_oringin_pts[i * 3 + j] = cy_data[i][j];
			cy_detect_pts[i * 3 + j] = cy_data[i][j];
		}
	}
	cy_input->oringin_pts = cy_oringin_pts;
	cy_input->detect_pts = cy_detect_pts;
	cy_input->detect_dir = cy_detect_dir;
	cy_input->cly_root[0] = 20;
	cy_input->cly_root[1] = 40;
	cy_input->cly_root[2] = 30;
	cy_input->cly_axis[0] = 0;
	cy_input->cly_axis[1] = 0;
	cy_input->cly_axis[2] = 1;
	cy_input->cly_radius = 20;
	cy_input->probe_radius = 2.5;
	std::cout << "\nstart\n";

	IMDA_analyze_cylinder(cy_input, cy_result);
	std::cout << "input_position_tol(max_error,min_error,square_error): " << cy_input->position_tol.max_error << ", " << cy_input->position_tol.min_error << ", " << cy_input->position_tol.square_error << "\n";
	std::cout << "result_position_tol(max_error,min_error,square_error): " << cy_result->position_tol.max_error << ", " << cy_result->position_tol.min_error << ", " << cy_result->position_tol.square_error << "\n";
	std::cout << "cly_root: " << cy_result->cly_root[0] << ", " << cy_result->cly_root[1] << ", " << cy_result->cly_root[2] << "\n";
	std::cout << "cly_axis: " << cy_result->cly_axis[0] << ", " << cy_result->cly_axis[1] << ", " << cy_result->cly_axis[2] << "\n";
	std::cout << "cly_radius: " << cy_result->cly_radius << "\n";
	std::cout << "cylindricity_tol: " << cy_result->cylindricity_tol << "\n";
	std::cout << "\nend\n";
	/*************************圆柱***************************/

	/*************************cone***************************/
	//double s_height = 40;
	//Vec s_vec = Vec(0, 0, 1);
	//Point s_bp = Point(20, 40, 30); // 标称的圆锥底面中心
	//Point s_tp = s_bp + (s_vec * s_height); // 标称的圆锥锥点
	//Cone cone_standard(s_tp, s_vec, 0.927295218001612);
	//// 实际cone参数不参与运算，只给我们一个拟合后的对比参看
	//double a_height = 40;
	//Vec a_vec = Vec(0.010156064710623948, -0.004186331321546835, 0.9999396626695332);
	//Point a_bp = Point(20.000319169987822, 40.00045980044738, 29.99917131787309);
	//Point a_tp = a_bp + (a_vec * a_height);
	//Cone cone_actual(a_tp, a_vec, 0.929294217835695);
	IMDA_cone_input_s* cn_input = new IMDA_cone_input_s;
	IMDA_cone_result_s* cn_result = new IMDA_cone_result_s;
	cn_input->position_count = 9;
	double* cn_oringin_pts = new double[3 * cn_input->position_count];
	double* cn_detect_pts = new double[3 * cn_input->position_count];
	double* cn_detect_dir = new double[3 * cn_input->position_count];
	std::vector<std::vector<double>> cn_data = {
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
	std::vector<std::vector<double>> cn_oringin_data = {
		{26.66666666666667, 51.547005383792516, 43.33333333333333},
		{13.333333333333336, 51.547005383792516, 43.33333333333333},
		{6.666666666666664, 40.0, 43.33333333333333},
		{13.333333333333325, 28.452994616207484, 43.33333333333333},
		{26.66666666666667, 28.452994616207484, 43.33333333333333},
		{23.333333333333336, 45.773502691896255, 56.666666666666664},
		{16.666666666666668, 45.77350269189626, 56.666666666666664},
		{13.333333333333332, 40.0, 56.666666666666664},
		{16.666666666666664, 34.226497308103745, 56.666666666666664},
		{23.333333333333336, 34.226497308103745, 56.666666666666664},
	};
	for (int i = 0;i < cn_input->position_count;i++) {
		for (int j = 0;j < 3;j++) {
			cn_oringin_pts[i * 3 + j] = cn_oringin_data[i][j];
			cn_detect_pts[i * 3 + j] = cn_data[i][j];
		}
	}
	cn_input->oringin_pts = cn_oringin_pts;
	cn_input->detect_pts = cn_detect_pts;
	cn_input->detect_dir = cn_detect_dir;
	cn_input->cone_root[0] = 20;
	cn_input->cone_root[1] = 40;
	cn_input->cone_root[2] = 70;
	cn_input->cone_axis[0] = 0;
	cn_input->cone_axis[1] = 0;
	cn_input->cone_axis[2] = 1;
	cn_input->cone_angle = 0.927295218001612 / 2;
	cn_input->probe_radius = 2.5;

	IMDA_analyze_cone(cn_input, cn_result);
	std::cout << "input_position_tol(max_error,min_error,square_error): " << cn_input->position_tol.max_error << ", " << cn_input->position_tol.min_error << ", " << cn_input->position_tol.square_error << "\n";
	std::cout << "result_position_tol(max_error,min_error,square_error): " << cn_result->position_tol.max_error << ", " << cn_result->position_tol.min_error << ", " << cn_result->position_tol.square_error << "\n";
	std::cout << "cone_root: " << cn_result->cone_root[0] << ", " << cn_result->cone_root[1] << ", " << cn_result->cone_root[2] << "\n";
	std::cout << "cone_axis: " << cn_result->cone_axis[0] << ", " << cn_result->cone_axis[1] << ", " << cn_result->cone_axis[2] << "\n";
	std::cout << "cone_angle: " << cn_result->cone_angle << "\n";
	std::cout << "angularity_tool: " << cn_result->angularity_tool << "\n";
	std::cout << "\nend\n";
	system("pause");
	return 0;
	/*************************cone***************************/
}

