#pragma once
#include "../SpaceMath/Geometry.h"
#include <vector>
#include <string>

constexpr auto MODEL_LENGTH_UNIT = "mm";
constexpr auto PROBE_RADIUS = 2.5;

class Model
{
public:
	enum ModelType
	{
		PlaneType = 0,
		SphereType,
		CylinderType,
		ConeType
	};
	Model(ModelType type) : type(type) {};
	~Model() {};
	inline	ModelType	modelType() const { return type; }
	virtual std::vector<double>	thetas() { return{}; };
private:
	ModelType	type;
};
