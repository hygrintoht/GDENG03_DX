#include "quadObject.h"
#include "vertexBuffer.h"
#include "graphicsEngine.h"
#include "deviceContext.h"

quadObject::quadObject()
{
}

void quadObject::init(vec3 _position)
{
	for (int i = 0; i < 4; i++) // set position of quad
	{
		list[i].position.x += _position.x;
		list[i].position.y += _position.y;
		list[i].position.z += _position.z;
	}
	// set vertex buffer
	m_vertex_buffer = graphicsEngine::get()->createVertexBuffer();
	graphicsEngine::get()->getShaderBufferAndSize(&m_shader_byte_code, &m_size_shader);
	m_vertex_buffer->load(list, sizeof(vertex), 4, m_shader_byte_code, m_size_shader);
}

void quadObject::release()
{
	m_vertex_buffer->release();
}


void quadObject::draw()
{	// draw the quad to window
	graphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	graphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vertex_buffer->getSizeVertexList(), 0);
}