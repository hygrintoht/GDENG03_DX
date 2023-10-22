#pragma once

#include "tiny_obj_loader.h"

#include "gameObject.h"
#include "vector"

class cubeObject : public gameObject
{
public:
	cubeObject();
	~cubeObject() override;

	void update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left) override;

	void changeSpeed(float speed);

private:
	float m_speed_multiplier = 0.55f;

	float m_scale = 0;

	float m_animation_timer = 0;
	int m_animation_direction = 1;

	tinyobj::attrib_t* attrib = new tinyobj::attrib_t;	// obj atributes
	std::vector<tinyobj::shape_t>* shapes = new std::vector<tinyobj::shape_t>;	// list of shapes
};

