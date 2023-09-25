#pragma once
#include <d3d11.h>

class graphicsEngine;
class deviceContext;

class pixelShader
{
public:
	pixelShader();
	~pixelShader();

	void release();

private:
	bool init(const void* shader_byte_code, size_t byte_code_size);

	ID3D11PixelShader* m_pixel_shader;

	friend class graphicsEngine;
	friend class deviceContext;
};