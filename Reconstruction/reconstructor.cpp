#include "pch.h"
#include "reconstructor.h"

reconstructor::reconstructor(Model* model, std::vector<std::vector<double>> data)
	:model(model), data(data)
{

}

reconstructor::~reconstructor() {
	
}

std::vector<double> reconstructor::fit(double tol, int maxIter) {
	std::cout << "1" << std::endl;
	// ����ģ�͵��������������+�뾶����
	Model::ModelType mtype = model->modelType();
	std::vector<double> iter_thetas = model->thetas();
	std::vector<std::vector<double>> iter_process = { iter_thetas };
	for (int i = 0; i < maxIter; i++) {
		std::cout << "iter " << i + 1 << "\t";
		// �뾶����+���
		leastsq lq(mtype, radiusCompensate(iter_thetas, mtype), iter_thetas);
		// �²���
		iter_thetas = lq.fit();
		// �жϲ����ı仯�ݲ�Ƿ�����
		int len = iter_thetas.size();
		bool flag = true;
		for (int j = 0; j < len; j++) {
			if (abs(iter_thetas[j] - iter_process[i][j]) > tol) {
				flag = false;
			}
			std::cout << iter_thetas[j] << " ";
		}
		std::cout << "\n";

		iter_process.emplace_back(iter_thetas);
		if (flag) {
			std::cout << "reconstructor Converged after " << i + 1 << " iterations." << std::endl;
			break;
		}
	}
	return iter_thetas;
}


std::vector<std::vector<double>> reconstructor::radiusCompensate(std::vector<double> iter_thetas, Model::ModelType type) {
	if (type == Model::PlaneType) {
		return planeComp(iter_thetas);
	}else if (type == Model::SphereType) {
		return sphereComp(iter_thetas);
	}
	else if (type == Model::CylinderType) {
		return cylinderComp(iter_thetas);
	}
	else if (type == Model::ConeType) {
		return coneComp(iter_thetas);
	}
	return std::vector<std::vector<double>>();
}
std::vector<std::vector<double>> reconstructor::planeComp(std::vector<double> iter_thetas) {
	std::vector<std::vector<double>> res;
	Point planeVec(iter_thetas[0], iter_thetas[1], iter_thetas[2]);
	for (auto& point : data) {
		Point p(point[0], point[1], point[2]);
		Vec compVec = GEOMETRY::Geom_UnitVec(Point(0,0,0) - planeVec);
		Point np = p + compVec * PROBE_RADIUS;
		std::vector<double> tmp({ np.x, np.y, np.z });
		res.emplace_back(tmp);
	}
	return res;
}
std::vector<std::vector<double>> reconstructor::sphereComp(std::vector<double> iter_thetas) {
	std::vector<std::vector<double>> res;
	Point Center(iter_thetas[0], iter_thetas[1], iter_thetas[2]);
	for (auto& point : data) {
		Point p(point[0], point[1], point[2]);
		Vec compVec = GEOMETRY::Geom_UnitVec(Center - p);
		Point np = p + compVec * PROBE_RADIUS;
		std::vector<double> tmp({ np.x, np.y, np.z });
		res.emplace_back(tmp);
	}
	return res;
}
std::vector<std::vector<double>> reconstructor::cylinderComp(std::vector<double> iter_thetas) {
	std::vector<std::vector<double>> res;
	Point pointOnAxis(iter_thetas[0], iter_thetas[1], iter_thetas[2]);
	Vec axis(iter_thetas[3], iter_thetas[4], iter_thetas[5]);
	double radius = iter_thetas[6];
	for (auto& point : data) {
		Point p(point[0], point[1], point[2]);
		Point proj_p2axis(GEOMETRY::Geom_PointProjLine(p, axis, pointOnAxis));	//���ݵ�ͶӰ��������
		Vec compVec = GEOMETRY::Geom_UnitVec(proj_p2axis - p);//�˴�Ϊ���ݵ㴹ֱָ�����ߵĵ�λ����
		Point np = p + compVec * PROBE_RADIUS;
		std::vector<double> tmp({ np.x, np.y, np.z });
		res.emplace_back(tmp);
	}
	return res;
}

std::vector<std::vector<double>> reconstructor::coneComp(std::vector<double> iter_thetas) {
	return std::vector<std::vector<double>>();

}