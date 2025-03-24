#include "pch.h"
#include "SphereSampler.h"

SphereSampler::SphereSampler()
	:Sampler(SamplerType::SphereType)
{
}

SphereSampler::~SphereSampler()
{
}

// ������ cnt ��
// �������ĵ� = �������� + sampleCenterVec * ����뾶
// �������ļнǵ�һ�� = sample Angle (0, pi]
std::vector<Point> SphereSampler::sample(const Sphere& model, int cnt, Vec sampleCenterVec, double sampleAngle) const {
	std::vector<Point> res;
	Point center = model.GetCenter();
	double radius = model.GetRadius();
	res.emplace_back(center + sampleCenterVec * radius);




	//for (Point &p : res) {
	//	std::cout << p.x << " " << p.y << " " << p.z << "\n";
	//}
	return res;
}
