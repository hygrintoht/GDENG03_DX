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
//#include "iostream"
#include "engineTime.h"
#include "inputSystem.h"

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
	inputSystem::get()->addListener(this);	// add app window as listener (removed because on focus handles that)
	inputSystem::get()->showCursor(false);	// show cursor
	graphicsEngine::get()->init();  //initialize engine

	m_swap_chain = graphicsEngine::get()->createSwapChain(); // initialize swap chain

	const RECT rect = this->getClientWindowRect(); // get window data
	m_swap_chain->init(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top); //window setup

	m_world_camera.setTranslation(vector3(0, 0, -2));

	// cube initialize
	//test1.init();
	//test1.setPosition(vector3(randFNOneToOne(), randFNOneToOne(), randFNOneToOne()));
	//test1.setScale(vector3(-0.3f, -0.3f, -0.3f));
	//test1.changeSpeed(1.0f);

	// multiple cubes
	for (int i = 0; i < m_cube_objects_size; i++)
	{
		m_cube_objects_list[i].init();
		m_cube_objects_list[i].setPosition(vector3(randFNOneToOne(), randFNOneToOne(), 0));
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
	//test1.loadVertexBuffer(m_shader_byte_code, m_size_shader);
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
	inputSystem::get()->update(); // update input system

	//clear
	graphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.5f, 0.5f, 0.5f, 1); // clear window

	//update

	RECT rect = this->getClientWindowRect(); // get window rect data
	graphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(rect.right - rect.left, rect.bottom - rect.top); // update viewport

	// set shaders
	graphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vertex_shader);
	graphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_pixel_shader);

	// update camera
	matrix4x4 temp;
	matrix4x4 world_camera_temp; // view matrix
	world_camera_temp.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_camera_temp *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_camera_temp *= temp;

	vector3 new_pos = m_world_camera.getTranslation() + world_camera_temp.getZDirection() * (m_forward * 0.1f);

	new_pos = new_pos + world_camera_temp.getXDirection() * (m_right * 0.1f);

	world_camera_temp.setTranslation(new_pos);

	m_world_camera = world_camera_temp;

	world_camera_temp.inverse();

	// update cube
	//test1.update(rect.top, rect.bottom, rect.right, rect.left);

	//draw

	// set constant buffer to object constant buffer
	//graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, test1.getConstantBuffer());
	//graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, test1.getConstantBuffer());

	// draw cube
	//test1.draw();

	for (int i = 0; i < m_cube_objects_size; i++)
	{
		m_cube_objects_list[i].update(world_camera_temp, rect.top, rect.bottom, rect.right, rect.left); //update object
		graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, m_cube_objects_list[i].getConstantBuffer()); // set constant buffer to object constant buffer
		graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, m_cube_objects_list[i].getConstantBuffer()); // set constant buffer to object constant buffer
		m_cube_objects_list[i].draw(); // draw object
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

	//test1.release(); // release cube
	for (int i = 0; i < m_cube_objects_size; i++)
	{
		m_cube_objects_list[i].release();
	}

	graphicsEngine::get()->release();
}

void appWindow::onFocus()
{
	inputSystem::get()->addListener(this);
}

void appWindow::onKillFocus()
{
	inputSystem::get()->removeListener(this);
}

void appWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		m_forward = 1.0f;
	}
	if (key == 'S')
	{
		m_forward = -1.0f;
	}
	if (key == 'D')
	{
		m_right = 1.0f;
	}
	if (key == 'A')
	{
		m_right = -1.0f;
	}
}

void appWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_right = 0.0f;
}

void appWindow::onMouseMove(const point& mouse_position)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_rot_x += (mouse_position.m_y - (height / 2.0f)) * engineTime::get()->getDeltaTime() * 0.1f;
	m_rot_y += (mouse_position.m_x - (width / 2.0f)) * engineTime::get()->getDeltaTime() * 0.1f;

	inputSystem::get()->setCursorPosition(point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void appWindow::onLeftMouseDown(const point& mouse_position)
{
	//m_scale_cube = 0.5f;
}

void appWindow::onLeftMouseUp(const point& mouse_position)
{
	//m_scale_cube = 1.0f;
}

void appWindow::onRightMouseDown(const point& mouse_position)
{
	//m_scale_cube = 2.0f;
}

void appWindow::onRightMouseUp(const point& mouse_position)
{
	//m_scale_cube = 1.0f;
}
