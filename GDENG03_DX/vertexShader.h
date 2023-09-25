#pragma once
#include "vertexBuffer.h"

class graphicsEngine;
class deviceContext;

class vertexShader
{
public:
	vertexShader();
	~vertexShader();

	void release();

private:
	bool init(const void* shader_byte_code, size_t byte_code_size);

	ID3D11VertexShader* m_vertex_shader;

	friend class graphicsEngine;
	friend class deviceContext;
};