#include "pch.h"
#include "Geometry.h"
#include <iostream>

void GEOMETRY::PrintHello() {
	std::cout << "HELLO GEOMETRY" << std::endl;
}
double GEOMETRY::Geom_PosDistance(const Point& a, const Point& b) {
	Point pDiff = a - b;
	return Geom_VecLen(pDiff);
}

double GEOMETRY::Geom_VecInnerAngle(const Vec& a, const Vec& b) {
	return acos(a.dot(b) / Geom_VecLen(a) / Geom_VecLen(b));
}

Point GEOMETRY::Geom_PointProjLine(const Point& p, const Vec& vec, const Point& fixedPoint) {
	Vec a = p - fixedPoint;
	double t = vec.dot(a) / vec.dot(vec);
	return vec * t + fixedPoint;
}

Point GEOMETRY::Geom_PointProjPlane(const Point& p, const Vec& vec, const Point& fixedPoint) {
	Point ProjOnVec = Geom_PointProjLine(p, vec, fixedPoint);
	Vec toPlaneVec = fixedPoint - ProjOnVec;
	return p + toPlaneVec;
}

double GEOMETRY::Geom_Point2LineDistance(const Point &p, const Vec &vec, const Point &fixedPoint) {
	Point projP = Geom_PointProjLine(p, vec, fixedPoint);
	return Geom_PosDistance(p, projP);
}

double GEOMETRY::Geom_Point2PlaneDistance(const Point& p, const Vec& vec, const Point& fixedPoint) {
	Point ProjOnVec = Geom_PointProjLine(p, vec, fixedPoint);
	return Geom_PosDistance(ProjOnVec, fixedPoint);
}

Vec GEOMETRY::Geom_UnitVec(const Vec& a) {
	return a / Geom_VecLen(a);
}

double GEOMETRY::Geom_VecLen(const Vec& a) {
	return sqrt(a.dot(a));
}

Vec GEOMETRY::Geom_VerticeVec(const Vec& vec) {
	if (vec.x == 0) return Vec(1, 0, 0);
	else if (vec.y == 0) return Vec(0, 1, 0);
	else if (vec.z == 0) return Vec(0, 0, 1);
	return Vec(1, - vec.x / vec.y , 0);
}

Point GEOMETRY::Geom_RotateAroundAxis(const Point& point, const Vec& vec, const Point& fp, double rad) {
	if (point == fp) return point;
	Point n_point = point - fp;
	// 新的坐标系的坐标轴
	Vec axis = Geom_UnitVec(vec);
	Vec newZ = axis;
	Vec newX = Geom_VerticeVec(newZ);
	Vec newY = newZ.cross(newX);
	// 在新的坐标系中被旋转 向量坐标
	double nX = Geom_VecLen(Geom_PointProjLine(n_point, newX, Vec(0, 0, 0)));
	double nY = Geom_VecLen(Geom_PointProjLine(n_point, newY, Vec(0, 0, 0)));
	double nZ = Geom_VecLen(Geom_PointProjLine(n_point, newZ, Vec(0, 0, 0)));
	double theta = nX != 0 ? atan(nY / nX) : M_PI / 2;
	if (nX < 0)
		theta += M_PI;
	theta += rad;
	double r = sqrt(nX * nX + nY * nY);
	double nnx = r * cos(theta);
	double nny = r * sin(theta);
	// 转换回原坐标系
	return fp + Geom_UnitVec(newX * nnx + newY * nny + newZ * nZ) * Geom_VecLen(n_point);
}