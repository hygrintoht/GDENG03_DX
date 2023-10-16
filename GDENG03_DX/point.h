#pragma once

class point
{
public:
	point() :m_x(0), m_y(0) {}
	point(int x, int y) :m_x(x), m_y(y) {}
	point(const point& point) :m_x(point.m_x), m_y(point.m_y) {}
	~point() {}

	int m_x, m_y;
};