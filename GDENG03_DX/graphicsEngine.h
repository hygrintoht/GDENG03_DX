#pragma once
#include <d3d11.h>

class swapChain;
class deviceContext;
class vertexBuffer;
class constantBuffer;
class vertexShader;
class pixelShader;

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
	constantBuffer* createConstantBuffer();
	vertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	pixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);

	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();

private:
	deviceContext* m_imm_device_context;

	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

	ID3D11DeviceContext* m_imm_context;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	ID3DBlob* m_blob = nullptr;
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	friend class swapChain;
	friend class vertexBuffer;
	friend class constantBuffer;
	friend class vertexShader;
	friend class pixelShader;
};