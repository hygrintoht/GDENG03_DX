#pragma once
#include "gameObject.h"

class cubeObject : public gameObject
{
public:
	cubeObject();
	~cubeObject() override;

	void update(float top, float bottom, float right, float left) override;

	void changeSpeed(float speed);

private:
	float m_speed_multiplier = 0.55f;

	float m_pos;
	float m_scale;
	float m_rot;
};

