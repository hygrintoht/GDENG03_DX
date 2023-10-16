#pragma once
#include "point.h"

class inputListener
{
public:
	inputListener() {}
	virtual ~inputListener() {}

	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	virtual void onMouseMove(const point& mouse_position) = 0;
	virtual void onLeftMouseDown(const point& mouse_position) = 0;
	virtual void onLeftMouseUp(const point& mouse_position) = 0;
	virtual void onRightMouseDown(const point& mouse_position) = 0;
	virtual void onRightMouseUp(const point& mouse_position) = 0;
};