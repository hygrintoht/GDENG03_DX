#include "vertexShader.h"
#include "graphicsEngine.h"

vertexShader::vertexShader()
{
}

vertexShader::~vertexShader()
{
}

bool vertexShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(graphicsEngine::get()->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vertex_shader)))
		return false;

	return true;
}

void vertexShader::release()
{
	m_vertex_shader->Release();
	delete this;
}
