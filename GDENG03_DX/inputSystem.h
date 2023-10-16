#pragma once
#include <unordered_set>
#include "inputListener.h"
#include "point.h"

class inputSystem
{
public:
	inputSystem();
	~inputSystem();

	void update();
	void addListener(inputListener* listener);
	void removeListener(inputListener* listener);

	void setCursorPosition(const point& position);
	void showCursor(bool show);

	bool isKeyDown(int key);

	static inputSystem* get();

private:
	std::unordered_set<inputListener*> m_set_listeners;

	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};

	point m_old_mouse_position;
	bool m_first_time = true;
};
