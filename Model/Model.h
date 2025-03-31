#pragma once
#include "../SpaceMath/Geometry.h"
#include <vector>
#include <string>

#ifdef MODEL_LIBRARY_EXPORTS
#define MODEL_LIBRARY_API __declspec(dllexport)
#else
#define MODEL_LIBRARY_API __declspec(dllimport)
#endif

constexpr auto MODEL_LENGTH_UNIT = "mm";
constexpr auto PROBE_RADIUS = 2.5;

class MODEL_LIBRARY_API Model
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
