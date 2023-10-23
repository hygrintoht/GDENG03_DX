#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_impl_win32.h"

#include "window.h"
#include "UIScreenAbstract.h"

struct UINames
{
	const std::string PROFILER_SCREEN = "PROFILER_SCREEN";
	const std::string MENU_SCREEN = "MENU_SCREEN";
	const std::string INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const std::string HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
};

class UIManager
{
public:
	static UIManager* get();
	static void init(HWND windowHandle);
	static void destroy();

	void drawAllUI();

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator = (UIManager const&){}

	//static UIManager* sharedInstance;

	std::vector<UIScreenAbstract*> uiList;
	std::unordered_map<std::string, UIScreenAbstract*>uiTable;
};