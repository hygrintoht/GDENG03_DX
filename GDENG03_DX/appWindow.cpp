#include "appWindow.h"

#include "deviceContext.h"
#include "swapChain.h"
#include "vertexBuffer.h"
#include "constantBuffer.h"
#include "mathUtils.h"
#include "graphicsEngine.h"
#include "quadObject.h"
#include "vertexShader.h"
#include "pixelShader.h"
#include "Windows.h"
#include "engineTime.h"

//#include "iostream"

appWindow::appWindow()
{
	
}

appWindow::~appWindow()
{
	
}


void appWindow::onCreate()
{	
	window::onCreate();				//create window
	graphicsEngine::get()->init();  //initialize engine

	m_swap_chain = graphicsEngine::get()->createSwapChain(); // initialize swap chain

	const RECT rect = this->getClientWindowRect(); // get window data
	m_swap_chain->init(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top); //window setup

	//create triangle(quad)
	vertex list[] =
	{
		{-0.5f,-0.5f,0.0f, -0.32f,-0.11f,0.0f,  0,0,0,  0,1,0 }, // POS1
		{-0.5f, 0.5f,0.0f, -0.11f, 0.78f,0.0f,  1,1,0,  0,1,1 }, // POS2
		{ 0.5f,-0.5f,0.0f,  0.75f,-0.73f,0.0f,  0,0,1,  1,0,0 }, // POS2
		{ 0.5f, 0.5f,0.0f,  0.88f, 0.77f,0.0f,  1,1,1,  0,0,1 }
	};	// list of vertices for quad (triangle strip with 4 vertices)

	UINT size_list = ARRAYSIZE(list); // size of list

	//test1.init({ 0,0,0 });
	//test2.init({ 0.5f,0.5f ,0 });
	//test3.init({ -0.5f,-0.5f ,0 });

	m_vertex_buffer = graphicsEngine::get()->createVertexBuffer(); //create vertex buffer
	
	graphicsEngine::get()->compileVertexShader(L"vertexShader.hlsl", "main", &m_shader_byte_code, &m_size_shader);
	m_vertex_shader = graphicsEngine::get()->createVertexShader(m_shader_byte_code, m_size_shader);
	m_vertex_buffer->load(list, sizeof(vertex), 4, m_shader_byte_code, m_size_shader); // load data to vertex buffer
	graphicsEngine::get()->releaseCompiledShader();

	graphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &m_shader_byte_code, &m_size_shader);
	m_pixel_shader = graphicsEngine::get()->createPixelShader(m_shader_byte_code, m_size_shader);
	graphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_constant_buffer = graphicsEngine::get()->createConstantBuffer();
	m_constant_buffer->load(&cc, sizeof(constant));
}

void appWindow::onUpdate()
{	
	window::onUpdate(); // update window

	//clear
	graphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 1, 0, 1); // clear window

	//update
	RECT rect = this->getClientWindowRect(); // get window rect data
	graphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(rect.right - rect.left, rect.bottom - rect.top); // update viewport

	/*
	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	//std::cout << "aw" << m_delta_time << std::endl;
	m_old_time = ::GetTickCount();
	*/

	m_angle += 1.57f * engineTime::get()->getDeltaTime();
	constant cc;
	cc.m_angle = m_angle;

	m_constant_buffer->update(graphicsEngine::get()->getImmediateDeviceContext(), &cc);

	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, m_constant_buffer);
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, m_constant_buffer);

	graphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vertex_shader);
	graphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_pixel_shader);

	//draw
	graphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer); // set vertex buffer
	graphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vertex_buffer->getSizeVertexList(), 0); // draw triangle strip

	//test1.draw();
	//test2.draw();
	//test3.draw();

	//present
	m_swap_chain->present(true);
}

void appWindow::onDestroy()
{
	window::onDestroy();
	//test1.release();
	//test2.release();
	//test3.release();
	m_vertex_shader->release();
	m_pixel_shader->release();
	m_vertex_buffer->release();
	m_swap_chain->release();
	graphicsEngine::get()->release();
}
