#include "UIManager.h"
#include "graphicsEngine.h"
#include "deviceContext.h"

UIManager::UIManager(HWND windowHandle)
{

}

UIManager::~UIManager()
{
}

UIManager* UIManager::get()
{
    return sharedInstance;
}

void UIManager::init(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
	// while ui list is not empty
	while (!sharedInstance->uiList.empty())
	{
		// get the name of ui window
		// remove from the ui table
		// delete ui window data
		// delete ui window
		// pop ui window from ui list
	}
}
