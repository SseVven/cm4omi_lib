#include "pch.h"
#include "leastsq.h"
#include "../SpaceMath/Geometry.h"

std::vector<double> planeFit(std::vector<double> parmas, std::vector<std::vector<double>> data);
std::vector<double> sphereFit(std::vector<double> parmas, std::vector<std::vector<double>> data);
std::vector<double> cylinderFit(std::vector<double> parmas, std::vector<std::vector<double>> data);
std::vector<double> coneFit(std::vector<double> parmas, std::vector<std::vector<double>> data);

leastsq::leastsq(residuals func, std::vector<std::vector<double>> data, std::vector<double> p0)
	:m_func(func), m_data(data), m_params(p0)
{
}
leastsq::leastsq(Model::ModelType modeltype, std::vector<std::vector<double>> data, std::vector<double> p0)
	:m_data(data), m_params(p0)
{
	if (modeltype == Model::PlaneType) {
		m_func = planeFit;
	}
	else if (modeltype == Model::SphereType) {
		m_func = sphereFit;
	}
	else if (modeltype == Model::CylinderType) {
		m_func = cylinderFit;
	}
	else if (modeltype == Model::ConeType) {
		m_func = coneFit;
	}
	else {
		m_func = planeFit;
	}
}
leastsq::~leastsq() {
}

// leastsq python
// deving
std::vector<double> leastsq::fit(double tol, int maxIter) {
    double lambda = 0.01; // 初始阻尼因子
    size_t n = m_params.size(); // 参数个数
    size_t m = m_data.size();  // 数据点个数

    for (int iter = 0; iter < maxIter; ++iter) {
        // 计算残差
        Vector r = m_func(m_params, m_data);
        Matrix J(m, Vector(n)); // 雅可比矩阵

        // 数值法计算雅可比矩阵
        double eps = 1e-8; // 微小增量
        for (size_t j = 0; j < n; ++j) {
            Vector thetaPlus = m_params;
            thetaPlus[j] += eps;
            Vector rPlus = m_func(thetaPlus, m_data);

            for (size_t i = 0; i < m; ++i) {
                J[i][j] = (rPlus[i] - r[i]) / eps; // 有限差分法计算偏导数
            }
        }

        // 计算更新步长
        Matrix Jt = J.transpose();
        J.transpose();
        Matrix A = Jt.matmul(J);
        for (size_t i = 0; i < n; ++i) {
            A[i][i] += lambda; // 添加阻尼因子
        }
        Vector b = Jt.matvecmul(r);
        for (size_t i = 0; i < b.size(); ++i) {
            b[i] = -b[i]; // 取负号
        }
        Vector dTheta = A.solveLinearSystem(b);

        // 更新参数
        Vector thetaNew(n);
        for (size_t j = 0; j < n; ++j) {
            thetaNew[j] = m_params[j] + dTheta[j];
        }

        // 检查收敛条件
        double norm = 0.0;
        for (double val : dTheta) {
            norm += val * val;
        }
        norm = sqrt(norm);
        if (norm < tol) {
            std::cout << "Converged after " << iter + 1 << " iterations." << std::endl;
            return thetaNew;
        }

        // 更新阻尼因子
        Vector rNew = m_func(thetaNew, m_data);
        double rNorm = 0.0, rNewNorm = 0.0;
        for (double val : r) rNorm += val * val;
        for (double val : rNew) rNewNorm += val * val;
        rNorm = sqrt(rNorm);
        rNewNorm = sqrt(rNewNorm);

        if (rNewNorm < rNorm) {
            lambda /= 10; // 减小阻尼因子
            m_params = thetaNew;
        }
        else {
            lambda *= 10; // 增大阻尼因子
        }
    }

    std::cout << "Reached maximum iterations." << std::endl;
    return m_params;
}

// unchecked
// params: 6位，前三位法向，后三位平面上点
// data: 三维点数组
std::vector<double> planeFit(std::vector<double> parmas, std::vector<std::vector<double>> data) {
	// 0 = A * (x-x0) + B*(y-y0) + C*(z-z0) = Ax+By+Cz -Ax0 -By0 -Cz0
	// Ax + By + Cz = Ax0 + By0 + Cz0 = D
	// 计算点到平面的距离
	std::vector<double> res;
	Vec vec(parmas[0], parmas[1], parmas[2]);
	Point fp(parmas[3], parmas[4], parmas[5]);
	for (auto& point : data) {
		Point p(point[0], point[1], point[2]);
		res.push_back(GEOMETRY::Geom_Point2PlaneDistance(p, vec, fp));
	}
	return res;
}

// CHECK DONE!
// params: 四位，前三位球心位置，第四位球半径
std::vector<double> sphereFit(std::vector<double> parmas, std::vector<std::vector<double>> data) {
	std::vector<double> res;
	double radius = parmas[3];
	for (auto& point : data) {
		double x = point[0];
		double y = point[1];
		double z = point[2];
		res.push_back(radius - sqrt(pow((x - parmas[0]),2) + pow((y - parmas[1]), 2) + pow((z - parmas[2]), 2)));
	}
	return res;
}

std::vector<double> cylinderFit(std::vector<double> parmas, std::vector<std::vector<double>> data) {
	return {};
}

std::vector<double> coneFit(std::vector<double> parmas, std::vector<std::vector<double>> data) {
	return {};
}