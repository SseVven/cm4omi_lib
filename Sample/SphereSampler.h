#pragma once
#include "Sampler.h"
#include "../Model/Sphere.h" 

class SphereSampler : public Sampler
{
public:
	SphereSampler();
	~SphereSampler();
	std::vector<Point> sample(const Sphere& model, int cnt, Vec sampleCenterVec, double sampleAngle) const;
private:
};
