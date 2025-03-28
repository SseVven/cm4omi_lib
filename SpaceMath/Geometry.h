//Geometry.h
#pragma once
#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_
#include <iostream>
#define	M_PI	3.14159265358979323846
#include <vector>

struct Vec
{ 
	double x, y, z;
	Vec(double x, double y, double z) :x(x), y(y), z(z) {}
	Vec() :x(0), y(0), z(0) {}
	Vec(const Vec& p) :x(p.x), y(p.y), z(p.z) {}
	bool operator= (const Vec& p)
	{
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}
	Vec operator+ (const Vec& p) const
	{
		Vec res;
		res.x = this->x + p.x;
		res.y = this->y + p.y;
		res.z = this->z + p.z;
		return res;
	}
	Vec operator- (const Vec& p) const
	{
		Vec res;
		res.x = this->x - p.x;
		res.y = this->y - p.y;
		res.z = this->z - p.z;
		return res;
	}
	Vec operator/ (double val) const
	{
		Vec res;
		res.x = this->x / val;
		res.y = this->y / val;
		res.z = this->z / val;
		return res;
	}
	Vec operator* (double val) const
	{
		Vec res;
		res.x = this->x * val;
		res.y = this->y * val;
		res.z = this->z * val;
		return res;
	}
	bool operator== (const Vec& p) const {
		return this->x == p.x && this->y == p.y && this->z == p.z;
	}
	friend std::ostream& operator<<(std::ostream& output, const Vec& vec)
	{
		output << "[ " << vec.x << ", " << vec.y << ", " << vec.z << "]";
		return output;
	}
	double dot(const Vec& p) const
	{
		double res = 0;
		res += this->x * p.x;
		res += this->y * p.y;
		res += this->z * p.z;
		return res;
	}
	Vec cross(const Vec& p) const
	{
		return Vec((this->y) * (p.z) - (this->z) * (p.y), -(this->x) * (p.z) + (this->z) * (p.x), (this->x) * (p.y) - (this->y) * (p.x));
	}
};
typedef Vec Point;
using Vector = std::vector<double>;
struct Matrix
{
	std::vector<Vector> data;
	Matrix(int n, int m) {
		data = std::vector<Vector>(n, Vector(m, 0));
	}
	Matrix(int n, Vector col) {
		data = std::vector<Vector>(n, col);
	}
	Matrix(const Matrix& mat) {
		int n = mat.data.size();
		int m = mat.data[0].size();
		data = std::vector<Vector>(n, Vector(m, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				this->data[i][j] = mat.val(i,j);
			}
		}
	}
	Vector& operator[] (int i) {
		return this->data[i];
	}
	void show() {
		for (auto& line : data) {
			for (auto item : line)
				std::cout << item << " ";
			std::cout << std::endl;
		}
	}
	void set(int i, int j, double val) {
		if (0 <= i and i < data.size() and 0 <= j and j < data[0].size())
			data[i][j] = val;
	}
	double val(int i, int j) const {
		return this->data[i][j];
	}
	Matrix transpose() {
		int n = this->data[0].size();
		int m = this->data.size();
		std::vector<Vector> newData = std::vector<Vector>(n, Vector(m, 0));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				newData[i][j] = this->data[j][i];
		this->data = newData;
		return *this;
	}
	// 矩阵乘法
	Matrix matmul(const Matrix& mB) const {
		auto A = this->data;
		auto B = mB.data;
		size_t rowsA = A.size();
		size_t colsA = A[0].size();
		size_t colsB = B[0].size();
		Matrix result(rowsA, Vector(colsB, 0.0));

		for (size_t i = 0; i < rowsA; ++i) {
			for (size_t j = 0; j < colsB; ++j) {
				for (size_t k = 0; k < colsA; ++k) {
					result[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		return result;
	}
	// 矩阵与向量乘法
	Vector matvecmul(const Vector& v) {
		auto A = this->data;
		size_t rows = A.size();
		size_t cols = A[0].size();
		Vector result(rows, 0.0);

		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j) {
				result[i] += A[i][j] * v[j];
			}
		}
		return result;
	}
	// 线性方程组求解
	Vector solveLinearSystem(const Vector& b) {
		size_t n = this->data.size();
		Matrix augmented = Matrix(*this);
		for (size_t i = 0; i < n; ++i) {
			augmented[i].push_back(b[i]);
		}

		// 高斯消元
		for (size_t i = 0; i < n; ++i) {
			// 归一化
			double pivot = augmented[i][i];
			for (size_t j = i; j < n + 1; ++j) {
				augmented[i][j] /= pivot;
			}

			// 消元
			for (size_t k = 0; k < n; ++k) {
				if (k != i) {
					double factor = augmented[k][i];
					for (size_t j = i; j < n + 1; ++j) {
						augmented[k][j] -= factor * augmented[i][j];
					}
				}
			}
		}

		// 提取解
		Vector x(n);
		for (size_t i = 0; i < n; ++i) {
			x[i] = augmented[i][n];
		}
		return x;
	}

};

namespace GEOMETRY
{
	void PrintHello();  //测试函数

	double Geom_PosDistance(const Point& point, const Point&);

	double Geom_VecInnerAngle(const Vec&, const Vec&);

	Point Geom_PointProjLine(const Point& point, const Vec&, const Point&);

	Point Geom_PointProjPlane(const Point& point, const Vec&, const Point&);

	double Geom_Point2LineDistance(const Point& point, const Vec&, const Point&);

	double Geom_Point2PlaneDistance(const Point& point, const Vec&, const Point&);

	Vec Geom_UnitVec(const Vec&);

	double Geom_VecLen(const Vec&) ;

	inline double Geom_Rad2Degree(double rad) { return rad / M_PI * 180; }
	inline double Geom_Degree2Rad(double deg) { return deg * M_PI / 180; }

	// 空间几何变换函数
	Vec Geom_VerticeVec(const Vec& vec);

	Point Geom_RotateAroundAxis(const Point& point, const Vec&, const Point&, double);

	//Vec Geom_Rotate
}

#endif
