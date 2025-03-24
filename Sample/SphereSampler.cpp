#include "pch.h"
#include "SphereSampler.h"

SphereSampler::SphereSampler()
	:Sampler(SamplerType::SphereType)
{
}

SphereSampler::~SphereSampler()
{
}

// 采样点 cnt 个
// 采样中心点 = 球心坐标 + sampleCenterVec * 球体半径
// 采样区的夹角的一半 = sample Angle (0, pi]
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
