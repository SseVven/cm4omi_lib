#pragma once
#include "../SpaceMath/Geometry.h"
#include <vector>

class Sampler
{
public:
	enum SamplerType
	{
		PlaneType = 0,
		SphereType,
		CylinderType,
		ConeType
	};
	Sampler(SamplerType type) : type(type) {};
	~Sampler() {};
	inline	SamplerType	modelType() const { return type; }
private:
	SamplerType	type;
};
