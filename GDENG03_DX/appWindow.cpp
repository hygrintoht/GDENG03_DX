#include "appWindow.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_impl_win32.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "string"
#include "deviceContext.h"
#include "swapChain.h"
#include "constantBuffer.h"
#include "mathUtils.h"
#include "graphicsEngine.h"
#include "quadObject.h"
#include "vertexShader.h"
#include "pixelShader.h"
#include "Windows.h"
#include "engineTime.h"
#include "inputSystem.h"

#include "UIManager.h"

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
	window::onCreate();						//create window
	inputSystem::get()->addListener(this);	// add app window as listener (removed because on focus handles that)
	graphicsEngine::get()->init();			//initialize engine

	m_swap_chain = graphicsEngine::get()->createSwapChain(); // initialize swap chain

	const RECT rect = this->getClientWindowRect(); // get window data
	m_swap_chain->init(this->m_hwnd, rect.right - rect.left, rect.bottom - rect.top); //window setup

	m_world_camera.setTranslation(vector3(0, 0, -2));

	std::string temp;
	/*
	temp = "cube.obj";
	test0.loadObjFileData(temp);
	test0.loadObjDataToMemory();
	test0.init();
	test0.setPosition(vector3(0, 0, 1.0f));
	test0.setScale(vector3(0.1f, 0.1f, 0.1f));
	test0.changeAnimationType(-1.0f);
	*/

	test0.init();
	test0.setPosition(vector3(0, 0, 0));
	test0.setScale(vector3(1.0f, 1.0f, 1.0f));
	test0.changeSpeed(randomFloat(0.5f, 0.5f));

	temp = "cube.obj";
	test1.loadObjFileData(temp);
	test1.loadObjDataToMemory();
	test1.init();
	test1.setPosition(vector3(-1.5f, 1.0f, -3.0f));
	test1.setScale(vector3(1.0f, 1.0f, 1.0f));
	test1.changeAnimationType(-1);

	temp = "cube.obj";
	test2.loadObjFileData(temp);
	test2.loadObjDataToMemory();
	test2.init();
	test2.setPosition(vector3(0, 1.0f, 0));
	test2.setScale(vector3(1.0f, 1.0f, 1.0f));
	test2.changeAnimationType(-1);

	temp = "cube.obj";
	test3.loadObjFileData(temp);
	test3.loadObjDataToMemory();
	test3.init();
	test3.setPosition(vector3(2.6f,1.0f,2.0f));
	test3.setScale(vector3(1.0f, 1.0f, 1.0f));
	test3.changeAnimationType(-1);

	temp = "plane.obj";
	test4.loadObjFileData(temp);
	test4.loadObjDataToMemory();
	test4.init();
	test4.setPosition(vector3(0, 0.0f, 0));
	test4.setScale(vector3(10.0f, 10.0f, 10.0f));
	test4.changeAnimationType(-1);
	// multiple cubes
	for (int i = 0; i < m_cube_objects_size; i++)
	{
		m_cube_objects_list[i].init();
		m_cube_objects_list[i].setPosition(vector3(randFZeroToOne() - 0.5f, randFZeroToOne() - 0.5f, randFZeroToOne() - 0.5f));
		m_cube_objects_list[i].setScale(vector3(1.0f, 1.0f, 1.0f));
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
	test0.loadVertexBuffer(m_shader_byte_code, m_size_shader);
	test1.loadVertexBuffer(m_shader_byte_code, m_size_shader);
	test2.loadVertexBuffer(m_shader_byte_code, m_size_shader);
	test3.loadVertexBuffer(m_shader_byte_code, m_size_shader);
	test4.loadVertexBuffer(m_shader_byte_code, m_size_shader);
	for (int i = 0; i < m_cube_objects_size; i++)
	{
		m_cube_objects_list[i].loadVertexBuffer(m_shader_byte_code, m_size_shader);
	}
	graphicsEngine::get()->releaseCompiledShader();

	// compile pixel shader
	graphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &m_shader_byte_code, &m_size_shader);
	m_pixel_shader = graphicsEngine::get()->createPixelShader(m_shader_byte_code, m_size_shader);
	graphicsEngine::get()->releaseCompiledShader();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(graphicsEngine::get()->getD3D11Device(), graphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());

	UIManager::init(m_hwnd);
}

void appWindow::onUpdate()
{
	window::onUpdate(); // update window
	inputSystem::get()->update(); // update input system

	//clear
	graphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]); // clear window

	//update

	// (Your code process and dispatch Win32 messages)
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Scene Settings", &m_tool_active, ImGuiWindowFlags_None);
	ImGui::Text("Below are settings for configuring the scene");
	ImGui::Checkbox("Show demo window", &m_demo_window_active);
	ImGui::ColorEdit4("clear color", m_clear_color);
	if (ImGui::Button("pause animation"))
	{
		m_pause_game = !m_pause_game;
		engineTime::get()->togglePause();
		std::cout << "pause: " << m_pause_game << "\n";
	}
	ImGui::End();

	if (m_demo_window_active)
		ImGui::ShowDemoWindow(); // Show demo window! :)

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
	/*
	test0.update(world_camera_temp, rect.top, rect.bottom, rect.right, rect.left);
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, test0.getConstantBuffer());
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, test0.getConstantBuffer());
	test0.draw();
	*/
	/*
	test1.update(world_camera_temp, rect.top, rect.bottom, rect.right, rect.left);
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, test1.getConstantBuffer());
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, test1.getConstantBuffer());
	test1.draw();

	test2.update(world_camera_temp, rect.top, rect.bottom, rect.right, rect.left);
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, test2.getConstantBuffer());
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, test2.getConstantBuffer());
	test2.draw();

	test3.update(world_camera_temp, rect.top, rect.bottom, rect.right, rect.left);
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, test3.getConstantBuffer());
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, test3.getConstantBuffer());
	test3.draw();
	*/
	/*
	test4.update(world_camera_temp, rect.top, rect.bottom, rect.right, rect.left);
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, test4.getConstantBuffer());
	graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, test4.getConstantBuffer());
	test4.draw();
	*/
	
	for (int i = 0; i < m_cube_objects_size; i++)
	{
		m_cube_objects_list[i].update(world_camera_temp, rect.top, rect.bottom, rect.right, rect.left); //update object
		graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vertex_shader, m_cube_objects_list[i].getConstantBuffer()); // set constant buffer to object constant buffer
		graphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_pixel_shader, m_cube_objects_list[i].getConstantBuffer()); // set constant buffer to object constant buffer
		m_cube_objects_list[i].draw(); // draw object
	}
	
	

	// Rendering
	// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// (Your code calls swapchain's Present() function)

	UIManager::get()->drawAllUI();

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

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

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
	if (m_mouse_down)
	{
		int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
		int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

		m_rot_x += (mouse_position.m_y - (height / 2.0f)) * 0.005f;// * engineTime::get()->getDeltaTime();
		m_rot_y += (mouse_position.m_x - (width / 2.0f))  * 0.005f;// * engineTime::get()->getDeltaTime();

		inputSystem::get()->setCursorPosition(point((int)(width / 2.0f), (int)(height / 2.0f)));
	}
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
	m_mouse_down = true;
	inputSystem::get()->showCursor(false);	// show cursor
}

void appWindow::onRightMouseUp(const point& mouse_position)
{
	//m_scale_cube = 1.0f;
	m_mouse_down = false;
	inputSystem::get()->showCursor(true);	// show cursor
}
