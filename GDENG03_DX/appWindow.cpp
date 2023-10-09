#include "appWindow.h"

#include "deviceContext.h"
#include "swapChain.h"
//#include "vertexBuffer.h"
//#include "indexBuffer.h"
#include "constantBuffer.h"
#include "mathUtils.h"
#include "graphicsEngine.h"
#include "quadObject.h"
#include "vertexShader.h"
#include "pixelShader.h"
#include "Windows.h"
//#include "engineTime.h"
//#include "vector3.h"
//#include "matrix4x4.h"
//#include "vector"
#include "iostream"

appWindow::appWindow()
{
	for(int i = 0; i < m_cube_objects_size; i++)
	{
		cubeObject cube_object;
		m_cube_objects_list.push_back(cube_object);
	}
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

	// cube initialize
	test1.init();
	test1.setPosition(vector3(randFNOneToOne(), randFNOneToOne(), randFNOneToOne()));
	test1.setScale(vector3(-0.3f, -0.3f, -0.3f));
	test1.changeSpeed(1.0f);

	// multiple cubes
	for (int i = 0; i < m_cube_objects_size; i++)
	{
		m_cube_objects_list[i].init();
		m_cube_objects_list[i].setPosition(vector3(randFNOneToOne(), randFNOneToOne(), randFNOneToOne()));
		m_cube_objects_list[i].setScale(vector3(-0.1f, -0.1f, -0.1f));
		m_cube_objects_list[i].changeSpeed(randomFloat(0.5f, 0.5f));
	}

	// set up constant buffer for shader compilation
	constant cc;
	cc.m_time = 0;
	m_constant_buffer = graphicsEngine::get()->createConstantBuffer();
	m_constant_buffer->load(&cc, sizeof(constant));

	// compile vertex shader
	graphicsEngine::get()->compileVertexShader(L"vertexShader.hlsl", "main", &m_shader_byte_code, &m_size_shader);
	m_vertex_shader = graphicsEngine::get()->createVertexShader(m_shader_byte_code, m_size_shader);
	test1.loadVertexBuffer(m_shader_byte_code, m_size_shader);
	for (int i = 0; i < m_cube_objects_size; i++)
	{
		m_cube_objects_list[i].loadVertexBuffer(m_shader_byte_code, m_size_shader);
	}
	graphicsEngine::get()->releaseCompiledShader();

	//compile pixel shader
	graphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &m_shader_byte_code, &m_size_shader);
	m_pixel_shader = graphicsEngine::get()->createPixelShader(m_shader_byte_code, m_size_shader);
	graphicsEngine::get()->releaseCompiledShader();
}

void appWindow::onUpdate()
{	
	window::onUpdate(); // update window

	//clear
	graphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.5f, 0.5f, 0.5f, 1); // clear window

	//update

	RECT rect = this->getClientWindowRect(); // get window rect data
	graphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(rect.right - rect.left, rect.bottom - rect.top); // update viewport

	// set shaders
	graphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vertex_shader);
	graphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_pixel_shader);

	// update cube
	test1.update(rect.top, rect.bottom, rect.right, rect.left);

	//draw

	// set constant buffer to object constant buffer
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, test1.getConstantBuffer());
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, test1.getConstantBuffer());

	// draw cube
	//test1.draw();

	for (int i = 0; i < m_cube_objects_size; i++)
	{
		m_cube_objects_list[i].update(rect.top, rect.bottom, rect.right, rect.left);
		graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, m_cube_objects_list[i].getConstantBuffer());
		graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, m_cube_objects_list[i].getConstantBuffer());
		m_cube_objects_list[i].draw();
	}

	//present
	m_swap_chain->present(true);
}

void appWindow::onDestroy()
{
	window::onDestroy();
	m_constant_buffer->release();

	m_vertex_shader->release();
	m_pixel_shader->release();
	
	m_swap_chain->release();

	test1.release(); // release cube

	graphicsEngine::get()->release();
}