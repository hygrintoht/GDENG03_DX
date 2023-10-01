#include "graphicsEngine.h"
#include "d3dcompiler.h"
#include "swapChain.h"
#include "deviceContext.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "constantBuffer.h"
#include "vertexShader.h"
#include "pixelShader.h"

graphicsEngine::graphicsEngine()
{	
}

graphicsEngine::~graphicsEngine()
{
}

bool graphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; )
	{
		res = D3D11CreateDevice
		(
			NULL,
			driver_types[driver_type_index],
			NULL,
			NULL,
			feature_levels,
			num_feature_levels,
			D3D11_SDK_VERSION,
			&m_d3d_device,
			&m_feature_level,
			&m_imm_context
		);

		if (SUCCEEDED(res))
			break;

		++driver_type_index;
	}

	if (FAILED(res))
		return false;

	m_imm_device_context = new deviceContext(m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

bool graphicsEngine::release()
{
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->release();
	m_d3d_device->Release();
	return true;
}

graphicsEngine* graphicsEngine::get()
{
	static graphicsEngine engine;
	return &engine;
}

swapChain* graphicsEngine::createSwapChain()
{
	return new swapChain();
}

deviceContext* graphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

vertexBuffer* graphicsEngine::createVertexBuffer()
{
	return new vertexBuffer();
}

indexBuffer* graphicsEngine::createIndexBuffer()
{
	return new indexBuffer();
}

constantBuffer* graphicsEngine::createConstantBuffer()
{
	return new constantBuffer();
}

vertexShader* graphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	vertexShader* vertex_shader = new vertexShader();

	if (!vertex_shader->init(shader_byte_code, byte_code_size))
	{
		vertex_shader->release();
		return nullptr;
	}

	return vertex_shader;
}

pixelShader* graphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	pixelShader* pixel_shader = new pixelShader();

	if(!pixel_shader->init(shader_byte_code, byte_code_size))
	{
		pixel_shader->release();
		return nullptr;
	}

	return pixel_shader;
}

bool graphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool graphicsEngine::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void graphicsEngine::releaseCompiledShader()
{
	if (m_blob)m_blob->Release();
}