#pragma once
#include "vector3.h"
#include "matrix4x4.h"

struct vertex
{
	vector3 position;
	vector3 color;
	vector3 color1;
};

__declspec(align(16))
struct constant
{
	matrix4x4 m_world;
	matrix4x4 m_view;
	matrix4x4 m_proj;
	unsigned int m_time;
};

// returns a float between 0 and 1, then multiplied by scale, then shifts by shift
inline float randomFloat(float scale, float shift)
{
	return (float)rand() / (float)RAND_MAX * scale + shift;
}

inline float randFZeroToOne()
{
	return randomFloat(1.0f, 0);
}

inline float randFNOneToOne()
{
	return randomFloat(2.0f, -1.0f) ;
}

inline float lerp(float a, float b, float t)
{
	return (1.0f - t) * a + b * t;
}