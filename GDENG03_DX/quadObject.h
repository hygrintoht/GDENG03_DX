#pragma once
#include "mathUtils.h"
#include "d3d11.h"

class vertexBuffer;

class quadObject
{
public:
	quadObject();

	void init(vec3 _position);
	void release();

	vec3 position = {0, 0, 0};
	vertex list[4] = 
	{
		{-0.2f,-0.2f, 0.0f},
		{-0.2f, 0.2f, 0.0f},
		{ 0.2f,-0.2f, 0.0f},
		{ 0.2f, 0.2f, 0.0f}
	};

	void draw();

private:
	vertexBuffer* m_vertex_buffer;

	void* m_shader_byte_code = nullptr;
	UINT m_size_shader = 0;
};