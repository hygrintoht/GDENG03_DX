#pragma once
#include <string>

class UIManager;

class UIScreenAbstract
{
protected:
	UIScreenAbstract(std::string name);
	~UIScreenAbstract();

	std::string getName();
	virtual void drawUI() = 0;

	std::string name;

	friend class UIManager;
};