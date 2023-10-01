#pragma once

class vector3
{
public:
	vector3() : m_x(0), m_y(0), m_z(0)
	{
	}
	vector3(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
	{
	}
	vector3(const vector3& vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
	{
	}
	~vector3()
	{
	}

	static vector3 lerp(const vector3& start, const vector3& end, float delta)
	{
		vector3 v;
		v.m_x = start.m_x * (1.0f - delta) + end.m_x * (delta);
		v.m_y = start.m_y * (1.0f - delta) + end.m_y * (delta);
		v.m_z = start.m_z * (1.0f - delta) + end.m_z * (delta);
		return v;
	}

	float m_x, m_y, m_z;
};