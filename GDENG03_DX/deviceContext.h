#pragma once
#include <d3d11.h>

class swapChain;
class vertexBuffer;

class deviceContext
{
public:
	deviceContext(ID3D11DeviceContext* device_context);
	~deviceContext();

	bool release();

	void clearRenderTargetColor(swapChain* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(vertexBuffer* vertex_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void setViewPortSize(UINT width, UINT height);

private:
	ID3D11DeviceContext* m_device_context;

};