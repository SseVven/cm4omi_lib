#pragma once

#ifdef IMDSURFANALYZE_LIBRARY_EXPORTS
#define IMDSURFANALYZE_LIBRARY_API __declspec(dllexport)
#else
#define IMDSURFANALYZE_LIBRARY_API __declspec(dllimport)
#endif
//#ifndef IMDSURFANALYZE_H_
//#define IMDSURFANALYZE_H_

/*
@info: 所有的 detect_dir 必须是单位向量，且从探头球心指向被测点
*/

/**
@struct IMDA_postion_tol_s
@brief 两组点集的误差定义
*/
struct IMDA_postion_tol_s
{
	double max_error;//!最大误差
	double min_error;//!最小误差
	double square_error;//!均方误差
};

/**
@struct IMDA_plane_input_s
@biref 平面的输入参数
*/
struct IMDA_plane_input_s
{
	int position_count;//!输入点的个数
	double* oringin_pts;//!原始点,个数为position_count
	double* detect_pts;//!检测点,与输入点一一对应
	double* detect_dir;//!检测方向,与原始点的法向相同
	IMDA_postion_tol_s position_tol;//!原始点与检测点的误差,@warning 由接口结算后返回

	double plane_root[3];//!输入平面原始点
	double plane_normal[3];//!输入平面法向

	double probe_radius;
};
/**
@struct IMDA_Plane_Result_s
@biref 平面的输出参数
*/
struct IMDA_plane_result_s
{
	IMDA_postion_tol_s position_tol;//!拟合后的拟合点集与原始点的误差 
	double plane_root[3];//!拟合平面的原始点
	double plane_normal[3];//!平面法向
	double flatness_tol;//!平面度
};
/**
@fn 平面拟合函数
@param input 输入参数,输入平面数据与测点数据
@param result 输出参数,输出拟合后的参数
@retvl 返回错误信息
*/
extern "C" IMDSURFANALYZE_LIBRARY_API int IMDA_analyze_plane(IMDA_plane_input_s* input, IMDA_plane_result_s* result);

//!圆柱输入参数
struct IMDA_cylinder_input_s
{
	int position_count;//!输入点的个数
	double* oringin_pts;//!原始点,个数为position_count
	double* detect_pts;//!检测点,与输入点一一对应
	double* detect_dir;//!检测方向,与原始点的法向相同
	IMDA_postion_tol_s position_tol;//!原始点与检测点的误差,@warning 由接口结算后返回

	double cly_root[3];//!原始点
	double cly_axis[3];//!圆柱轴向
	double cly_radius;//!圆柱半径

	double probe_radius;
};
//!圆柱输出参数
struct IMDA_cylinder_result_s
{
	IMDA_postion_tol_s position_tol;//!拟合后的拟合点集与原始点的误差 
	double cly_root[3];//!拟合后的原始点
	double cly_axis[3];//!拟合后的圆柱轴向
	double cly_radius;//!拟合后的圆柱半径
	double cylindricity_tol;//!圆柱度
};
/**
@fn 圆柱拟合接口
@param input 输入参数,输入圆柱数据与测点数据
@param result 输出参数,输出拟合后的参数
@retvl 返回错误信息
*/
extern "C" IMDSURFANALYZE_LIBRARY_API int IMDA_analyze_cylinder(IMDA_cylinder_input_s* input, IMDA_cylinder_result_s* result);

//!圆锥输入参数
struct IMDA_cone_input_s
{
	int position_count;//!输入点的个数
	double* oringin_pts;//!原始点,个数为position_count
	double* detect_pts;//!检测点,与输入点一一对应
	double* detect_dir;//!检测方向,与原始点的法向相同
	IMDA_postion_tol_s position_tol;//!原始点与检测点的误差,@warning 由接口结算后返回

	double cone_root[3];//!原始点
	double cone_axis[3];//!圆锥轴向

	double cone_angle;//!圆锥半空间角度

	double probe_radius;
};

//!圆锥输出参数
struct IMDA_cone_result_s
{
	IMDA_postion_tol_s position_tol;//!拟合后的拟合点集与原始点的误差 
	double cone_root[3];//!拟合后的原始点
	double cone_axis[3];//!拟合后的圆锥轴向
	//double cone_radius;//!拟合后的圆锥半径
	double cone_angle;//!拟合后的圆锥半空间角度

	double angularity_tool;//!角度公差
};
extern "C" IMDSURFANALYZE_LIBRARY_API int IMDA_analyze_cone(IMDA_cone_input_s* input, IMDA_cone_result_s* result);

//!球输入参数
struct IMDA_sphere_input_s
{
	int position_count;//!输入点的个数
	double* oringin_pts;//!原始点,个数为position_count
	double* detect_pts;//!检测点,与输入点一一对应
	double* detect_dir;//!检测方向,与原始点的法向相同
	IMDA_postion_tol_s position_tol;//!原始点与检测点的误差,@warning 由接口结算后返回

	double sphere_root[3];//!原始点
	double sphere_radius;//!球半径

	double probe_radius;
};
//!球输出参数
struct IMDA_sphere_result_s
{
	IMDA_postion_tol_s position_tol;//!拟合后的拟合点集与原始点的误差 
	double sphere_root[3];//!拟合后原始点
	double sphere_radius;//!拟合后球半径
	double concentricity_tol;//!同心度
};
extern "C" IMDSURFANALYZE_LIBRARY_API int IMDA_analyze_sphere(IMDA_sphere_input_s* input, IMDA_sphere_result_s* result);
//#endif // !IMDSURFANALYZE_H_

