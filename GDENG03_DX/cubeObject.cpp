#include "cubeObject.h"

#include "engineTime.h"
#include "graphicsEngine.h"
#include "constantBuffer.h"
#include "inputSystem.h"

cubeObject::cubeObject()
{
	vertex vertex_list[] =
	{
		//front vertices
		{ vector3(-0.5f, -0.5f, -0.5f), vector3(1, 0, 0), vector3(0.2f,    0,    0) },
		{ vector3(-0.5f,  0.5f, -0.5f), vector3(1, 1, 0), vector3(0.2f, 0.2f,    0) },
		{ vector3(0.5f,  0.5f, -0.5f), vector3(1, 1, 0), vector3(0.2f, 0.2f,    0) },
		{ vector3(0.5f, -0.5f, -0.5f), vector3(1, 0, 0), vector3(0.2f,    0,    0) },

		//back vertices
		{ vector3(0.5f, -0.5f,  0.5f), vector3(0, 1, 0), vector3(0, 0.2f,    0) },
		{ vector3(0.5f,  0.5f,  0.5f), vector3(0, 1, 1), vector3(0, 0.2f, 0.2f) },
		{ vector3(-0.5f,  0.5f,  0.5f), vector3(0, 1, 1), vector3(0, 0.2f, 0.2f) },
		{ vector3(-0.5f, -0.5f,  0.5f), vector3(0, 1, 0), vector3(0, 0.2f,    0) }
	};

	unsigned int index_list[] =
	{
		//front
		0,1,2,
		2,3,0,
		//back
		4,5,6,
		6,7,4,
		//top
		1,6,5,
		5,2,1,
		//bottom
		7,0,3,
		3,4,7,
		//right
		3,2,5,
		5,4,3,
		//left
		7,6,1,
		1,0,7
	};

	for (int i = 0; i < ARRAYSIZE(vertex_list); i++)
	{
		m_vertex_list.push_back(vertex_list[i]);
	}

	for (int i = 0; i < ARRAYSIZE(index_list); i++)
	{
		m_index_list.push_back(index_list[i]);
	}
}

cubeObject::~cubeObject()
{
}

void cubeObject::update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left)
{
	constant cc;
	cc.m_time = ::GetTickCount();

	m_pos += engineTime::get()->getDeltaTime() / 10.0f;
	if (m_pos > 1.0f)
		m_pos = 0;

	// temporary input
	float scale_mutiplier = 0;
	if (inputSystem::get()->isKeyDown('W'))
		scale_mutiplier = 2.0f;

	if (inputSystem::get()->isKeyDown('S'))
		scale_mutiplier = -2.0f;

	m_scale += 0;//(engineTime::get()->getDeltaTime() / m_speed_multiplier) * scale_mutiplier;

	matrix4x4 transform;
	transform.setIdentity();

	// world space
	cc.m_world.setIdentity();

	transform.setIdentity();
	transform.setRotationZ(m_scale);
	cc.m_world *= transform;

	transform.setIdentity();
	transform.setRotationY(m_scale);
	cc.m_world *= transform;

	transform.setIdentity();
	transform.setRotationX(m_scale);
	cc.m_world *= transform;

	cc.m_world *= m_transform;

	// view space
	cc.m_view = world_camera_temp;

	// projection
	int width = (right - left);
	int height = (bottom - top);
	
	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	m_constant_buffer->update(graphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void cubeObject::changeSpeed(float speed)
{
	m_speed_multiplier = speed;
}

