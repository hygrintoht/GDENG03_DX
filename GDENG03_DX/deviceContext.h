#pragma once
#include <d3d11.h>

class swapChain;
class vertexBuffer;
class indexBuffer;
class constantBuffer;
class vertexShader;
class pixelShader;

class deviceContext
{
public:
	deviceContext(ID3D11DeviceContext* device_context);
	~deviceContext();

	bool release();

	void clearRenderTargetColor(swapChain* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(vertexBuffer* vertex_buffer);
	void setIndexBuffer(indexBuffer* index_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void setViewPortSize(UINT width, UINT height);
	void setVertexShader(vertexShader* vertex_shader);
	void setPixelShader(pixelShader* pixel_shader);
	void setConstantBuffer(vertexShader* vertex_shader, constantBuffer* buffer);
	void setConstantBuffer(pixelShader* pixel_shader, constantBuffer* buffer);
	ID3D11DeviceContext* getDeviceContext();
private:
	ID3D11DeviceContext* m_device_context;

	friend class constantBuffer;
};