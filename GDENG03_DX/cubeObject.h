#pragma once
#include "gameObject.h"

class cubeObject : public gameObject
{
public:
	cubeObject();
	~cubeObject() override;

	void update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left) override;

	void changeSpeed(float speed);

private:
	float m_speed_multiplier = 0.55f;

	float m_pos = 0;
	float m_scale = 0;
	float m_rot = 0;
};

