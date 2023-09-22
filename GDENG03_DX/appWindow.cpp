#include "appWindow.h"
#include "deviceContext.h"
#include "swapChain.h"
#include "vertexBuffer.h"
#include "mathUtils.h"
#include "graphicsEngine.h"
#include "quadObject.h"

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
	//m_vertex_buffer = graphicsEngine::get()->createVertexBuffer(); //create vertex buffer
	graphicsEngine::get()->createShaders(); // create shaders
	graphicsEngine::get()->getShaderBufferAndSize(&m_shader_byte_code, &m_size_shader); //get shader byte code and its size
	/*
	vertex list[] =
	{
		{-0.2f,-0.2f, 0.0f},
		{-0.2f, 0.2f, 0.0f},
		{ 0.2f,-0.2f, 0.0f},
		{ 0.2f, 0.2f, 0.0f}
	};	// list of vertices for quad (triangle strip with 4 vertices)

	UINT size_list = ARRAYSIZE(list); // size of list
	*/
	test1.init({ 0,0,0 });
	test2.init({ 0.5f,0.5f ,0 });
	test3.init({ -0.5f,-0.5f ,0 });


	//m_vertex_buffer->load(test.list, sizeof(vertex), 4, m_shader_byte_code, m_size_shader); // load data to vertex buffer
}

void appWindow::onUpdate()
{	
	window::onUpdate(); // update window

	//clear
	graphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 1, 0, 1); // clear window

	//update
	RECT rect = this->getClientWindowRect(); // get window rect data
	graphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(rect.right - rect.left, rect.bottom - rect.top); // update viewport
	graphicsEngine::get()->setShaders(); // set shaders
	//graphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer); // set vertex buffer

	//draw
	//graphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vertex_buffer->getSizeVertexList(), 0); // draw triangle list 
	//graphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vertex_buffer->getSizeVertexList(), 0); // draw triangle strip
	test1.draw();
	test2.draw();
	test3.draw();
	//present
	m_swap_chain->present(true);
}

void appWindow::onDestroy()
{
	window::onDestroy();
	test1.release();
	test2.release();
	test3.release();
	//m_vertex_buffer->release();
	m_swap_chain->release();
	graphicsEngine::get()->release();
}
