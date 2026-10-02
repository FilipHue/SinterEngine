#pragma once

// Internal
#include "input_types.h"

#include <sinter/core/patterns/singleton.h>
#include <sinter/core/types/hashtable.h>
#include <sinter/core/types/object.h>

#include <sinter/engine/window/window_types.h>

namespace sinter::engine
{

	class InputSystem final : public core::Singleton<InputSystem>, public core::SEObject
	{
		friend class core::Singleton<InputSystem>;

	public:
		void Init();
		void Shutdown();

		b8 IsKeyPressed(WindowRID p_windowRID, KeyCode p_key);
		b8 IsKeyJustPressed(WindowRID p_windowRID, KeyCode p_key);
		b8 IsKeyReleased(WindowRID p_windowRID, KeyCode p_key);
		b8 IsKeyJustReleased(WindowRID p_windowRID, KeyCode p_key);

		b8 IsMouseButtonPressed(WindowRID p_windowRID, MouseButtonCode p_button);
		b8 IsMouseButtonJustPressed(WindowRID p_windowRID, MouseButtonCode p_button);
		b8 IsMouseButtonReleased(WindowRID p_windowRID, MouseButtonCode p_button);
		b8 IsMouseButtonJustReleased(WindowRID p_windowRID, MouseButtonCode p_button);

		f32 GetMouseX(WindowRID p_windowRID);
		f32 GetMouseY(WindowRID p_windowRID);
		f32 GetMouseDeltaX(WindowRID p_windowRID);
		f32 GetMouseDeltaY(WindowRID p_windowRID);
		f32 GetMouseScrollX(WindowRID p_windowRID);
		f32 GetMouseScrollY(WindowRID p_windowRID);

		b8 IsGamepadButtonPressed(WindowRID p_windowRID, GamepadButtonCode p_button);
		b8 IsGamepadButtonJustPressed(WindowRID p_windowRID, GamepadButtonCode p_button);
		b8 IsGamepadButtonReleased(WindowRID p_windowRID, GamepadButtonCode p_button);
		b8 IsGamepadButtonJustReleased(WindowRID p_windowRID, GamepadButtonCode p_button);

		void AddWindowInputState(WindowRID p_windowRID);
		void RemoveWindowInputState(WindowRID p_windowRID);

		void ProcessKeyEvent(WindowRID p_windowRID, KeyCode p_key, b8 p_isPressed);
		void ProcessMouseButtonEvent(WindowRID p_windowRID, MouseButtonCode p_button, b8 p_isPressed);
		void ProcessMouseMoveEvent(WindowRID p_windowRID, f32 p_x, f32 p_y);
		void ProcessMouseScrollEvent(WindowRID p_windowRID, f32 p_scrollX, f32 p_scrollY);
		void ProcessGamepadButtonEvent(WindowRID p_windowRID, GamepadButtonCode p_button, b8 p_isPressed);
		void ProcessGamepadAxisEvent(WindowRID p_windowRID, i32 p_axisIndex, f32 p_value);

		void UpdateInputStates();

	private:
		DEFAULT_CTOR_AND_DTOR(InputSystem);

	private:
		SEUnorderedMap<WindowRID, InputState> m_windowInputStates;
	};

} // namespace sinter::engine
