#include "pch.h"
#include "IMDSurfAnalyze.h"
#include "../SpaceMath/Geometry.h"
#include "../Model/Plane.h"
#include "../Model/Sphere.h"
#include "../Model/Cylinder.h"
#include "../Model/Cone.h"
#include "../Reconstruction/reconstructor.h"

extern "C" IMDSURFANALYZE_LIBRARY_API int IMDA_analyze_plane(IMDA_plane_input_s* input, IMDA_plane_result_s* result) {
	int n = input->position_count;
	std::vector<Vector> oringin_pts = IMDA::pos_set_trans(input->oringin_pts, n);
	std::vector<Vector> detect_pts = IMDA::pos_set_trans(input->detect_pts, n);
	std::vector<Vector> detect_dir = IMDA::pos_set_trans(input->detect_dir, n);
	double probe_radius = input->probe_radius;
	// 反向半径补偿
	for (int i = 0;i < n;i++) {
		Vec dir = GEOMETRY::Geom_UnitVec(Vec(detect_dir[i][0], detect_dir[i][1], detect_dir[i][2])) * probe_radius;
		Point new_p = Point(detect_pts[i][0], detect_pts[i][1], detect_pts[i][2]) - dir;
		detect_pts[i][0] = new_p.x;
		detect_pts[i][1] = new_p.y;
		detect_pts[i][2] = new_p.z;
	}
	// 反向半径补偿 end
	input->position_tol = IMDA::get_position_tols_s(oringin_pts, detect_pts);
	Plane plane_oringin = Plane(Vec(input->plane_normal), Point(input->plane_root));
	reconstructor rc(&plane_oringin, detect_pts, probe_radius);
	std::vector<double> thetas = rc.fit();
	std::vector<Vector> fit_pts = rc.getLastFit_RC_pts(thetas);
	result->position_tol = IMDA::get_position_tols_s(oringin_pts, fit_pts);
	result->plane_normal[0] = thetas[0];
	result->plane_normal[1] = thetas[1];
	result->plane_normal[2] = thetas[2];
	result->plane_root[0] = thetas[3];
	result->plane_root[1] = thetas[4];
	result->plane_root[2] = thetas[5];
	// flatness_tol: max_d - min_d
	std::vector<double> d_s;
	for (Vector p: fit_pts) {
		Point pp = Point(p[0], p[1], p[2]);
		double distance = GEOMETRY::Geom_Point2PlaneDistance(pp, Vec(thetas[0], thetas[1], thetas[2]), Point(thetas[3], thetas[4], thetas[5]));
		d_s.emplace_back(distance);
	}
	result->flatness_tol = *(std::max_element(d_s.begin(), d_s.end())) - *(std::min_element(d_s.begin(), d_s.end()));
	return 0;
}

extern "C" IMDSURFANALYZE_LIBRARY_API int IMDA_analyze_sphere(IMDA_sphere_input_s* input, IMDA_sphere_result_s* result) {
	int n = input->position_count;
	std::vector<Vector> oringin_pts = IMDA::pos_set_trans(input->oringin_pts, n);
	std::vector<Vector> detect_pts = IMDA::pos_set_trans(input->detect_pts, n);
	std::vector<Vector> detect_dir = IMDA::pos_set_trans(input->detect_dir, n);
	double probe_radius = input->probe_radius;
	// 反向半径补偿
	for (int i = 0;i < n;i++) {
		Vec dir = GEOMETRY::Geom_UnitVec(Vec(detect_dir[i][0], detect_dir[i][1], detect_dir[i][2])) * probe_radius;
		Point new_p = Point(detect_pts[i][0], detect_pts[i][1], detect_pts[i][2]) - dir;
		detect_pts[i][0] = new_p.x;
		detect_pts[i][1] = new_p.y;
		detect_pts[i][2] = new_p.z;
	}
	// 反向半径补偿 end
	input->position_tol = IMDA::get_position_tols_s(oringin_pts, detect_pts);
	Sphere sphere_oringin = Sphere(Point(input->sphere_root), input->sphere_radius);
	reconstructor rc(&sphere_oringin, detect_pts, probe_radius);
	std::vector<double> thetas = rc.fit();
	std::vector<Vector> fit_pts = rc.getLastFit_RC_pts(thetas);
	result->position_tol = IMDA::get_position_tols_s(oringin_pts, fit_pts);
	result->sphere_root[0] = thetas[0];
	result->sphere_root[1] = thetas[1];
	result->sphere_root[2] = thetas[2];
	result->sphere_radius = thetas[3];
	// concentricity_tol: max_d - min_d
	std::vector<double> d_s;
	for (Vector p : fit_pts) {
		Point pp = Point(p[0], p[1], p[2]);
		double distance = GEOMETRY::Geom_PosDistance(pp, Point(thetas[0], thetas[1], thetas[2])) - thetas[3];
		d_s.emplace_back(distance);
	}
	result->concentricity_tol = *(std::max_element(d_s.begin(), d_s.end())) - *(std::min_element(d_s.begin(), d_s.end()));
	return 0;
}

extern "C" IMDSURFANALYZE_LIBRARY_API int IMDA_analyze_cylinder(IMDA_cylinder_input_s* input, IMDA_cylinder_result_s* result) {
	int n = input->position_count;
	std::vector<Vector> oringin_pts = IMDA::pos_set_trans(input->oringin_pts, n);
	std::vector<Vector> detect_pts = IMDA::pos_set_trans(input->detect_pts, n);
	std::vector<Vector> detect_dir = IMDA::pos_set_trans(input->detect_dir, n);
	double probe_radius = input->probe_radius;
	// 反向半径补偿
	for (int i = 0;i < n;i++) {
		Vec dir = GEOMETRY::Geom_UnitVec(Vec(detect_dir[i][0], detect_dir[i][1], detect_dir[i][2])) * probe_radius;
		Point new_p = Point(detect_pts[i][0], detect_pts[i][1], detect_pts[i][2]) - dir;
		detect_pts[i][0] = new_p.x;
		detect_pts[i][1] = new_p.y;
		detect_pts[i][2] = new_p.z;
	}
	// 反向半径补偿 end
	input->position_tol = IMDA::get_position_tols_s(oringin_pts, detect_pts);
	Cylinder cylinder_oringin = Cylinder(Point(input->cly_root), Vec(input->cly_axis), input->cly_radius);
	reconstructor rc(&cylinder_oringin, detect_pts, probe_radius);
	std::vector<double> thetas = rc.fit();
	std::vector<Vector> fit_pts = rc.getLastFit_RC_pts(thetas);
	result->position_tol = IMDA::get_position_tols_s(oringin_pts, fit_pts);
	result->cly_root[0] = thetas[0];
	result->cly_root[1] = thetas[1];
	result->cly_root[2] = thetas[2];
	result->cly_axis[0] = thetas[3];
	result->cly_axis[1] = thetas[4];
	result->cly_axis[2] = thetas[5];
	result->cly_radius = thetas[6];
	// cylindricity_tol: max_d - min_d
	std::vector<double> d_s;
	for (Vector p : fit_pts) {
		Point pp = Point(p[0], p[1], p[2]);
		double distance = GEOMETRY::Geom_Point2LineDistance(pp, Vec(thetas[3], thetas[4], thetas[5]), Point(thetas[0], thetas[1], thetas[2])) - thetas[6];
		d_s.emplace_back(distance);
	}
	result->cylindricity_tol = *(std::max_element(d_s.begin(), d_s.end())) - *(std::min_element(d_s.begin(), d_s.end()));
	return 0;
}

extern "C" IMDSURFANALYZE_LIBRARY_API int IMDA_analyze_cylinder_hole(IMDA_cylinder_hole_input_s* input, IMDA_cylinder_hole_result_s* result) {
	int res = IMDA_analyze_cylinder(input, result);
	return res;
}

extern "C" IMDSURFANALYZE_LIBRARY_API int IMDA_analyze_cone(IMDA_cone_input_s* input, IMDA_cone_result_s* result) {
	int n = input->position_count;
	std::vector<Vector> oringin_pts = IMDA::pos_set_trans(input->oringin_pts, n);
	std::vector<Vector> detect_pts = IMDA::pos_set_trans(input->detect_pts, n);
	std::vector<Vector> detect_dir = IMDA::pos_set_trans(input->detect_dir, n);
	double probe_radius = input->probe_radius;
	// 反向半径补偿
	for (int i = 0;i < n;i++) {
		Vec dir = GEOMETRY::Geom_UnitVec(Vec(detect_dir[i][0], detect_dir[i][1], detect_dir[i][2])) * probe_radius;
		Point new_p = Point(detect_pts[i][0], detect_pts[i][1], detect_pts[i][2]) - dir;
		detect_pts[i][0] = new_p.x;
		detect_pts[i][1] = new_p.y;
		detect_pts[i][2] = new_p.z;
	}
	// 反向半径补偿 end
	input->position_tol = IMDA::get_position_tols_s(oringin_pts, detect_pts);
	Cone cone_oringin = Cone(Point(input->cone_root), Vec(input->cone_axis), 2 * (input->cone_angle));
	reconstructor rc(&cone_oringin, detect_pts, probe_radius);
	std::vector<double> thetas = rc.fit();
	std::vector<Vector> fit_pts = rc.getLastFit_RC_pts(thetas);
	result->position_tol = IMDA::get_position_tols_s(oringin_pts, fit_pts);
	result->cone_root[0] = thetas[0];
	result->cone_root[1] = thetas[1];
	result->cone_root[2] = thetas[2];
	double t_len = sqrt(thetas[3]* thetas[3] + thetas[4] * thetas[4]+ thetas[5] * thetas[5]);
	result->cone_axis[0] = thetas[3] / t_len;
	result->cone_axis[1] = thetas[4] / t_len;
	result->cone_axis[2] = thetas[5] / t_len;
	result->cone_angle  = thetas[6] / 2;
	// angularity_tool: max_a - min_a
	std::vector<double> d_s;
	for (Vector p : fit_pts) {
		Point pp = Point(p[0], p[1], p[2]);
		Vec vec = pp - Vec(thetas[0], thetas[1], thetas[2]);
		Vec axis = Vec(thetas[3], thetas[4], thetas[5]);
		double angle_d = GEOMETRY::Geom_VecInnerAngle(vec, axis) - result->cone_angle;
		d_s.emplace_back(angle_d);
	}
	result->angularity_tool = *(std::max_element(d_s.begin(), d_s.end())) - *(std::min_element(d_s.begin(), d_s.end()));
	return 0;
}
