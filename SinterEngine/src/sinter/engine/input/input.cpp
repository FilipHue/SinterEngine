#include "sepch.h"
#include "input.h"

namespace sinter::engine
{

	void InputSystem::Init()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ENGINE_DEBUG("\tInputSystem initialized successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	void InputSystem::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		SE_ENGINE_DEBUG("\tInputSystem shutdown successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	b8 InputSystem::IsKeyPressed(WindowRID p_windowRID, KeyCode p_key)
	{
		return m_windowInputStates[p_windowRID].keys_current_frame[STATIC_CAST(u32, p_key)];
	}

	b8 InputSystem::IsKeyJustPressed(WindowRID p_windowRID, KeyCode p_key)
	{
		return m_windowInputStates[p_windowRID].keys_current_frame[STATIC_CAST(u32, p_key)] && !m_windowInputStates[p_windowRID].keys_last_frame[STATIC_CAST(u32, p_key)];
	}

	b8 InputSystem::IsKeyReleased(WindowRID p_windowRID, KeyCode p_key)
	{
		return !m_windowInputStates[p_windowRID].keys_current_frame[STATIC_CAST(u32, p_key)];
	}

	b8 InputSystem::IsKeyJustReleased(WindowRID p_windowRID, KeyCode p_key)
	{
		return !m_windowInputStates[p_windowRID].keys_current_frame[STATIC_CAST(u32, p_key)] && m_windowInputStates[p_windowRID].keys_last_frame[STATIC_CAST(u32, p_key)];
	}

	b8 InputSystem::IsMouseButtonPressed(WindowRID p_windowRID, MouseButtonCode p_button)
	{
		return m_windowInputStates[p_windowRID].mouse_buttons_current_frame[STATIC_CAST(u32, p_button)];
	}

	b8 InputSystem::IsMouseButtonJustPressed(WindowRID p_windowRID, MouseButtonCode p_button)
	{
		return m_windowInputStates[p_windowRID].mouse_buttons_current_frame[STATIC_CAST(u32, p_button)] && !m_windowInputStates[p_windowRID].mouse_buttons_last_frame[STATIC_CAST(u32, p_button)];
	}

	b8 InputSystem::IsMouseButtonReleased(WindowRID p_windowRID, MouseButtonCode p_button)
	{
		return !m_windowInputStates[p_windowRID].mouse_buttons_current_frame[STATIC_CAST(u32, p_button)];
	}

	b8 InputSystem::IsMouseButtonJustReleased(WindowRID p_windowRID, MouseButtonCode p_button)
	{
		return !m_windowInputStates[p_windowRID].mouse_buttons_current_frame[STATIC_CAST(u32, p_button)] && m_windowInputStates[p_windowRID].mouse_buttons_last_frame[STATIC_CAST(u32, p_button)];
	}

	f32 InputSystem::GetMouseX(WindowRID p_windowRID)
	{
		return m_windowInputStates[p_windowRID].mouse_x;
	}

	f32 InputSystem::GetMouseY(WindowRID p_windowRID)
	{
		return m_windowInputStates[p_windowRID].mouse_y;
	}

	f32 InputSystem::GetMouseDeltaX(WindowRID p_windowRID)
	{
		return m_windowInputStates[p_windowRID].mouse_delta_x;
	}

	f32 InputSystem::GetMouseDeltaY(WindowRID p_windowRID)
	{
		return m_windowInputStates[p_windowRID].mouse_delta_y;
	}

	f32 InputSystem::GetMouseScrollX(WindowRID p_windowRID)
	{
		return m_windowInputStates[p_windowRID].mouse_scroll_x;
	}

	f32 InputSystem::GetMouseScrollY(WindowRID p_windowRID)
	{
		return m_windowInputStates[p_windowRID].mouse_scroll_y;
	}

	b8 InputSystem::IsGamepadButtonPressed(WindowRID p_windowRID, GamepadButtonCode p_button)
	{
		return m_windowInputStates[p_windowRID].gamepad_buttons_current_frame[STATIC_CAST(u32, p_button)];
	}

	b8 InputSystem::IsGamepadButtonJustPressed(WindowRID p_windowRID, GamepadButtonCode p_button)
	{
		return m_windowInputStates[p_windowRID].gamepad_buttons_current_frame[STATIC_CAST(u32, p_button)] && !m_windowInputStates[p_windowRID].gamepad_buttons_last_frame[STATIC_CAST(u32, p_button)];
	}

	b8 InputSystem::IsGamepadButtonReleased(WindowRID p_windowRID, GamepadButtonCode p_button)
	{
		return !m_windowInputStates[p_windowRID].gamepad_buttons_current_frame[STATIC_CAST(u32, p_button)];
	}

	b8 InputSystem::IsGamepadButtonJustReleased(WindowRID p_windowRID, GamepadButtonCode p_button)
	{
		return !m_windowInputStates[p_windowRID].gamepad_buttons_current_frame[STATIC_CAST(u32, p_button)] && m_windowInputStates[p_windowRID].gamepad_buttons_last_frame[STATIC_CAST(u32, p_button)];
	}

	void InputSystem::AddWindowInputState(WindowRID p_windowRID)
	{
		m_windowInputStates[p_windowRID] = NULL_INPUT_STATE;
	}

	void InputSystem::RemoveWindowInputState(WindowRID p_windowRID)
	{
		m_windowInputStates.erase(p_windowRID);
	}

	void InputSystem::ProcessKeyEvent(WindowRID p_windowRID, KeyCode p_key, b8 p_isPressed)
	{
		if (m_windowInputStates[p_windowRID].keys_current_frame[STATIC_CAST(u32, p_key)] != p_isPressed)
		{
			m_windowInputStates[p_windowRID].keys_current_frame[STATIC_CAST(u32, p_key)] = p_isPressed;
		}
	}

	void InputSystem::ProcessMouseButtonEvent(WindowRID p_windowRID, MouseButtonCode p_button, b8 p_isPressed)
	{
		if (m_windowInputStates[p_windowRID].mouse_buttons_current_frame[STATIC_CAST(u32, p_button)] != p_isPressed)
		{
			m_windowInputStates[p_windowRID].mouse_buttons_current_frame[STATIC_CAST(u32, p_button)] = p_isPressed;
		}
	}

	void InputSystem::ProcessMouseMoveEvent(WindowRID p_windowRID, f32 p_x, f32 p_y)
	{
		if (m_windowInputStates[p_windowRID].mouse_x != p_x || m_windowInputStates[p_windowRID].mouse_y != p_y)
		{
			m_windowInputStates[p_windowRID].mouse_delta_x = p_x - m_windowInputStates[p_windowRID].mouse_x;
			m_windowInputStates[p_windowRID].mouse_delta_y = p_y - m_windowInputStates[p_windowRID].mouse_y;
			m_windowInputStates[p_windowRID].mouse_x_prev = m_windowInputStates[p_windowRID].mouse_x;
			m_windowInputStates[p_windowRID].mouse_y_prev = m_windowInputStates[p_windowRID].mouse_y;
			m_windowInputStates[p_windowRID].mouse_x = p_x;
			m_windowInputStates[p_windowRID].mouse_y = p_y;
		}
	}

	void InputSystem::ProcessMouseScrollEvent(WindowRID p_windowRID, f32 p_scrollX, f32 p_scrollY)
	{
		m_windowInputStates[p_windowRID].mouse_scroll_x = p_scrollX;
		m_windowInputStates[p_windowRID].mouse_scroll_y = p_scrollY;
	}

	void InputSystem::ProcessGamepadButtonEvent(WindowRID p_windowRID, GamepadButtonCode p_button, b8 p_isPressed)
	{
		m_windowInputStates[p_windowRID].gamepad_buttons_current_frame[STATIC_CAST(u32, p_button)] = p_isPressed;
	}

	void InputSystem::ProcessGamepadAxisEvent(WindowRID p_windowRID, i32 p_axisIndex, f32 p_value)
	{
		m_windowInputStates[p_windowRID].gamepad_axes[STATIC_CAST(u32, p_axisIndex)] = p_value;
	}

	void InputSystem::UpdateInputStates()
	{
		for (auto& [windowRID, inputState] : m_windowInputStates)
		{
			inputState.keys_last_frame = inputState.keys_current_frame;
			inputState.mouse_buttons_last_frame = inputState.mouse_buttons_current_frame;
			inputState.gamepad_buttons_last_frame = inputState.gamepad_buttons_current_frame;
			inputState.mouse_x_prev = inputState.mouse_x;
			inputState.mouse_y_prev = inputState.mouse_y;
			inputState.mouse_delta_x = 0.0f;
			inputState.mouse_delta_y = 0.0f;
			inputState.mouse_scroll_x = 0.0f;
			inputState.mouse_scroll_y = 0.0f;
		}
	}

} // namespace sinter::engine
