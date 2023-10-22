#include "gameObject.h"

#include "graphicsEngine.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "constantBuffer.h"
#include "deviceContext.h"
#include "iostream"

gameObject::gameObject()
{
}

gameObject::~gameObject()
{
}

void gameObject::init()
{
	//m_transform.setIdentity();

	m_vertex_buffer = graphicsEngine::get()->createVertexBuffer();
	m_index_buffer = graphicsEngine::get()->createIndexBuffer();
	m_constant_buffer = graphicsEngine::get()->createConstantBuffer();

	m_index_buffer->load(m_index_list.data() , m_index_list.size());

	constant cc;
	cc.m_time = 0;

	m_constant_buffer->load(&cc, sizeof(constant)); // default constant;
}

void gameObject::release()
{
	m_vertex_buffer->release();
	m_index_buffer->release();
	m_constant_buffer->release();
	//delete this
}

void gameObject::update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left)
{
	/*
	constant cc;
	cc.m_time = ::GetTickCount();

	matrix4x4 transform;
	transform.setIdentity();

	// world space
	cc.m_world.setIdentity();

	transform.setIdentity();
	cc.m_world *= transform;

	transform.setIdentity();
	cc.m_world *= transform;

	transform.setIdentity();
	cc.m_world *= transform;

	cc.m_world *= m_transform;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << m_transform.m_mat[i][j] << " ";
		}
		std::cout << "\n";
	}

	// view space
	cc.m_view = world_camera_temp;

	// projection
	int width = (right - left);
	int height = (bottom - top);

	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	m_constant_buffer->update(graphicsEngine::get()->getImmediateDeviceContext(), &cc);
	
	// default update for game objects
	constant cc;
	cc.m_time = ::GetTickCount();
	cc.m_world.setIdentity();
	cc.m_world *= m_transform;

	cc.m_view = world_camera_temp;

	int width = (right - left);
	int height = (bottom - top);

	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	m_constant_buffer->update(graphicsEngine::get()->getImmediateDeviceContext(), &cc);
	*/
}

void gameObject::draw()
{
	graphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	graphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_index_buffer);
	graphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_index_buffer->getSizeIndexList(), 0, 0);
}

void gameObject::loadVertexBuffer(void* shader_byte_code, size_t size_byte_shader)
{
	m_vertex_buffer->load(m_vertex_list.data(), sizeof(vertex), m_vertex_list.size(), shader_byte_code, size_byte_shader);
}

constantBuffer* gameObject::getConstantBuffer() const
{
	return m_constant_buffer;
}

void gameObject::setPosition(vector3 position)
{
	/*
	m_transform.m_mat[3][0] = position.m_x;
	m_transform.m_mat[3][1] = position.m_y;
	m_transform.m_mat[3][2] = position.m_z;
	*/
	m_transform.setTranslation(position);
}

void gameObject::setScale(vector3 scale)
{
	/*
	m_transform.m_mat[0][0] = scale.m_x;
	m_transform.m_mat[1][1] = scale.m_y;
	m_transform.m_mat[2][2] = scale.m_z;
	*/
	m_transform.setScale(scale);
}

void gameObject::setRotation(vector3 rotation)
{
	m_transform.setRotation(rotation);
}
