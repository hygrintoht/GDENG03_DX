#pragma once
#include "window.h"

#include "cubeObject.h"

class swapChain;
class vertexBuffer;
class indexBuffer;
class constantBuffer;
class vertexShader;
class pixelShader;

class appWindow : public  window
{
public:
	appWindow();
	~appWindow();

	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void onUpdate() override;

	swapChain* getSwapChain();
	vertexBuffer* getVertexBuffer();

private:
	swapChain* m_swap_chain;
	vertexBuffer* m_vertex_buffer;
	indexBuffer* m_index_buffer;
	constantBuffer* m_constant_buffer;
	vertexShader* m_vertex_shader;
	pixelShader* m_pixel_shader;

	void* m_shader_byte_code = nullptr;
	size_t m_size_shader = 0;

	float m_pos;
	float m_scale;
	float m_rot;

	cubeObject test1;

	std::vector<cubeObject> m_cube_objects_list;
	int m_cube_objects_size = 100;
};