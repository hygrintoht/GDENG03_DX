#include "inputSystem.h"
#include "appWindow.h"

inputSystem::inputSystem()
{
}

inputSystem::~inputSystem()
{
}

void inputSystem::update()
{
	POINT current_mouse_position = {};
	::GetCursorPos(&current_mouse_position);

	point current_mouse_position_local = point(current_mouse_position.x, current_mouse_position.y);

	// on first frame
	if (m_first_time)
	{
		m_old_mouse_position = current_mouse_position_local;
		m_first_time = false;
	}
	// update mouse position
	if (current_mouse_position.x != m_old_mouse_position.m_x || current_mouse_position.y != m_old_mouse_position.m_y)
	{
		//THERE IS MOUSE MOVE EVENT
		std::unordered_set<inputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end())
		{
			(*it)->onMouseMove(current_mouse_position_local);
			++it;
		}
	}
	m_old_mouse_position = current_mouse_position_local;

	//update keyboard and mouse buttons state
	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{	
			if (m_keys_state[i] & 0x80) // key is down
			{
				std::unordered_set<inputListener*>::iterator iterator = m_set_listeners.begin();

				while (iterator != m_set_listeners.end())
				{	
					if (i == VK_LBUTTON) // check l mouse down
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*iterator)->onLeftMouseDown(current_mouse_position_local);
					}
					else if (i == VK_RBUTTON) // check r mouse down
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*iterator)->onRightMouseDown(current_mouse_position_local);
					}
					else // keyboard key down
						(*iterator)->onKeyDown(i);

					++iterator;
				}
			}
			else // key is up
			{
				if(m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<inputListener*>::iterator iterator = m_set_listeners.begin();

					while (iterator != m_set_listeners.end())
					{
						if (i == VK_LBUTTON)
							(*iterator)->onLeftMouseUp(current_mouse_position_local);
						else if (i == VK_RBUTTON)
							(*iterator)->onRightMouseUp(current_mouse_position_local);
						else
							(*iterator)->onKeyUp(i);

						++iterator;
					}
				}
			}
		}
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void inputSystem::addListener(inputListener* listener)
{
	m_set_listeners.insert(listener);
}

void inputSystem::removeListener(inputListener* listener)
{
	m_set_listeners.erase(listener);
}

void inputSystem::setCursorPosition(const point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void inputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

bool inputSystem::isKeyDown(int key)
{
	if (m_keys_state[key] & 0x80) // key is down
		return true;

	return false;
}

inputSystem* inputSystem::get()
{
	static inputSystem system;
	return &system;
}