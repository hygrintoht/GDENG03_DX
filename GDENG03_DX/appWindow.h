#pragma once
//#include "quadObject.h"
#include "window.h"

class swapChain;
class vertexBuffer;
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

	void drawObject();

private:
	swapChain* m_swap_chain;
	vertexBuffer* m_vertex_buffer;
	constantBuffer* m_constant_buffer;
	vertexShader* m_vertex_shader;
	pixelShader* m_pixel_shader;

	void* m_shader_byte_code = nullptr;
	size_t m_size_shader = 0;

	
	//unsigned long m_old_time = 0;
	//float m_delta_time = 0;

	float m_angle = 0;

	//quadObject test1;
	//quadObject test2;
	//quadObject test3;
};