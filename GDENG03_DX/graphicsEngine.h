#pragma once
#include <d3d11.h>

class swapChain;
class deviceContext;
class vertexBuffer;

class graphicsEngine
{
public:

	graphicsEngine();
	~graphicsEngine();

	bool init();
	bool release();

	static graphicsEngine* get();

	swapChain* createSwapChain();
	deviceContext* getImmediateDeviceContext();
	vertexBuffer* createVertexBuffer();

	bool createShaders();
	bool setShaders();
	void getShaderBufferAndSize(void** bytecode, UINT* size);

private:
	deviceContext* m_imm_device_context;

	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

	ID3D11DeviceContext* m_imm_context;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	friend class swapChain;
	friend class vertexBuffer;
};