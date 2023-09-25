#include "pixelShader.h"
#include "graphicsEngine.h"

pixelShader::pixelShader()
{
}

pixelShader::~pixelShader()
{
}

bool pixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(graphicsEngine::get()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_pixel_shader)))
		return false;
	return true;
}

void pixelShader::release()
{
	m_pixel_shader->Release();
	delete this;
}
