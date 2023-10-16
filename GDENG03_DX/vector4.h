#pragma once

class vector4
{
public:
	vector4() :m_x(0), m_y(0), m_z(0), m_w(0) {}
	vector4(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}
	vector4(const vector4& vector) :m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z), m_w(vector.m_w) {}
	~vector4() {}

	void cross(vector4& v1, vector4& v2, vector4& v3)
	{
		this->m_x =   v1.m_y * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) + v1.m_w * (v2.m_y * v3.m_z - v2.m_z * v3.m_y);
		this->m_y = -(v1.m_x * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_z - v3.m_x * v2.m_z));
		this->m_z =   v1.m_x * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) - v1.m_y * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_y - v3.m_x * v2.m_y);
		this->m_w = -(v1.m_x * (v2.m_y * v3.m_z - v3.m_y * v2.m_z) - v1.m_y * (v2.m_x * v3.m_z - v3.m_x * v2.m_z) + v1.m_z * (v2.m_x * v3.m_y - v3.m_x * v2.m_y));
	}

	float m_x, m_y, m_z, m_w;
};