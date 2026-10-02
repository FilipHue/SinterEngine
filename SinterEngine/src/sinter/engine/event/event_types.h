#pragma once

// Internal
#include <sinter/core/defines.h>

#include <sinter/engine/application/application_types.h>
#include <sinter/engine/input/input_codes.h>
#include <sinter/engine/window/window_types.h>

// STL
#include <functional>
#include <ostream>

namespace sinter::engine
{

	enum class EventType : u32
	{
		None = 0,

		AppInit,
		AppUpdate,
		AppStateChange,
		AppClose,

		WindowMoved,
		WindowResize,
		WindowClose,
		WindowRefresh,
		WindowFocus,
		WindowIconify,
		WindowMaximize,
		WindowContentScale,

		KeyPressed,
		KeyReleased,
		KeyTyped,

		MouseMoved,
		MouseEnter,
		MouseLeave,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseScrolled,

		Count
	};

	INLINE constexpr const char* EventTypeToString(EventType p_type)
	{
		switch (p_type)
		{
		case EventType::None: return "None";

		case EventType::AppInit:				return "AppInit";
		case EventType::AppUpdate:				return "AppUpdate";
		case EventType::AppStateChange:			return "AppStateChange";
		case EventType::AppClose:				return "AppClose";

		case EventType::WindowMoved:			return "WindowMoved";
		case EventType::WindowResize:			return "WindowResize";
		case EventType::WindowClose:			return "WindowClose";
		case EventType::WindowFocus:			return "WindowFocus";
		case EventType::WindowIconify:			return "WindowIconify";
		case EventType::WindowMaximize:			return "WindowMaximize";
		case EventType::WindowContentScale:		return "WindowContentScale";

		case EventType::KeyPressed:				return "KeyPressed";
		case EventType::KeyReleased:			return "KeyReleased";
		case EventType::KeyTyped:				return "KeyTyped";

		case EventType::MouseMoved:				return "MouseMoved";
		case EventType::MouseEnter:				return "MouseEnter";
		case EventType::MouseLeave:				return "MouseLeave";
		case EventType::MouseButtonPressed:		return "MouseButtonPressed";
		case EventType::MouseButtonReleased:	return "MouseButtonReleased";
		case EventType::MouseScrolled:			return "MouseScrolled";

		default:								return "Unknown";
		}
	}

	union EventData
	{
		u8 raw[16]{};

		struct { f32 delta_time; }									app_update;
		struct { ApplicationState state; }							app_state_change;

		struct { i32 x, y; }										window_moved;
		struct { i32 width, height; }								window_resize;
		struct { b8 focused; }										window_focus;
		struct { b8 iconified; }									window_iconify;
		struct { b8 maximized; }									window_maximize;
		struct { f32 x, y; }										window_content_scale;

		struct { KeyCode keycode; i32 scancode; KeyModCode mods; }	key;
		struct { u32 codepoint; }									key_typed;

		struct { f32 x, y; }										mouse_moved;
		struct { MouseButtonCode button; KeyModCode mods; }			mouse_button;
		struct { f32 delta_x, delta_y; }							mouse_scrolled;
	};

	struct EventContext
	{
		EventData data{};
		EventType type{ EventType::None };
		WindowRID window_rid{ InvalidWindowRID };
		b8 handled{ false };

		const char* GetName() const { return EventTypeToString(type); }

		// Application
		static EventContext AppInit() { return Make(EventType::AppInit); }

		static EventContext AppUpdate(f32 p_deltaTime)
		{
			EventContext l_event = Make(EventType::AppUpdate);
			l_event.data.app_update = { p_deltaTime };
			return l_event;
		}

		static EventContext AppStateChange(ApplicationState p_state)
		{
			EventContext l_event = Make(EventType::AppStateChange);
			l_event.data.app_state_change = { p_state.isRunning, p_state.isSuspended };
			return l_event;
		}

		static EventContext AppClose() { return Make(EventType::AppClose); }

		// Window
		static EventContext WindowMoved(WindowRID p_rid, i32 p_x, i32 p_y)
		{
			EventContext l_event = Make(EventType::WindowMoved, p_rid);
			l_event.data.window_moved = { p_x, p_y };
			return l_event;
		}

		static EventContext WindowResize(WindowRID p_rid, i32 p_width, i32 p_height)
		{
			EventContext l_event = Make(EventType::WindowResize, p_rid);
			l_event.data.window_resize = { p_width, p_height };
			return l_event;
		}

		static EventContext WindowClose(WindowRID p_rid) { return Make(EventType::WindowClose, p_rid); }

		static EventContext WindowFocus(WindowRID p_rid, b8 p_focused)
		{
			EventContext l_event = Make(EventType::WindowFocus, p_rid);
			l_event.data.window_focus = { p_focused };
			return l_event;
		}

		static EventContext WindowIconify(WindowRID p_rid, b8 p_iconified)
		{
			EventContext l_event = Make(EventType::WindowIconify, p_rid);
			l_event.data.window_iconify = { p_iconified };
			return l_event;
		}

		static EventContext WindowMaximize(WindowRID p_rid, b8 p_maximized)
		{
			EventContext l_event = Make(EventType::WindowMaximize, p_rid);
			l_event.data.window_maximize = { p_maximized };
			return l_event;
		}

		static EventContext WindowContentScale(WindowRID p_rid, f32 p_x, f32 p_y)
		{
			EventContext l_event = Make(EventType::WindowContentScale, p_rid);
			l_event.data.window_content_scale = { p_x, p_y };
			return l_event;
		}

		// Keyboard
		static EventContext KeyPressed(WindowRID p_rid, KeyCode p_key, i32 p_scancode, KeyModCode p_mods)
		{
			EventContext l_event = Make(EventType::KeyPressed, p_rid);
			l_event.data.key = { p_key, p_scancode, p_mods };
			return l_event;
		}

		static EventContext KeyReleased(WindowRID p_rid, KeyCode p_key, i32 p_scancode, KeyModCode p_mods)
		{
			EventContext l_event = Make(EventType::KeyReleased, p_rid);
			l_event.data.key = { p_key, p_scancode, p_mods };
			return l_event;
		}

		static EventContext KeyTyped(WindowRID p_rid, u32 p_codepoint)
		{
			EventContext l_event = Make(EventType::KeyTyped, p_rid);
			l_event.data.key_typed = { p_codepoint };
			return l_event;
		}

		// Mouse
		static EventContext MouseMoved(WindowRID p_rid, f32 p_x, f32 p_y)
		{
			EventContext l_event = Make(EventType::MouseMoved, p_rid);
			l_event.data.mouse_moved = { p_x, p_y };
			return l_event;
		}

		static EventContext MouseEnter(WindowRID p_rid) { return Make(EventType::MouseEnter, p_rid); }

		static EventContext MouseLeave(WindowRID p_rid) { return Make(EventType::MouseLeave, p_rid); }

		static EventContext MouseButtonPressed(WindowRID p_rid, MouseButtonCode p_button, KeyModCode p_mods)
		{
			EventContext l_event = Make(EventType::MouseButtonPressed, p_rid);
			l_event.data.mouse_button = { p_button, p_mods };
			return l_event;
		}

		static EventContext MouseButtonReleased(WindowRID p_rid, MouseButtonCode p_button, KeyModCode p_mods)
		{
			EventContext l_event = Make(EventType::MouseButtonReleased, p_rid);
			l_event.data.mouse_button = { p_button, p_mods };
			return l_event;
		}

		static EventContext MouseScrolled(WindowRID p_rid, f32 p_deltaX, f32 p_deltaY)
		{
			EventContext l_event = Make(EventType::MouseScrolled, p_rid);
			l_event.data.mouse_scrolled = { p_deltaX, p_deltaY };
			return l_event;
		}

	private:
		static EventContext Make(EventType type, WindowRID p_rid = InvalidWindowRID)
		{
			EventContext l_event{};
			l_event.type = type;
			l_event.window_rid = p_rid;
			return l_event;
		}
	};

	using SubscriptionID = core::UUID;
	INLINE constexpr SubscriptionID InvalidSubscriptionID = core::UUID(0);

	// Return true to mark the event as handled and stop propagation.
	using EventCallbackFn = std::function<b8(EventContext&)>;

	INLINE std::ostream& operator<<(std::ostream& os, const EventContext& e)
	{
		return os << e.GetName();
	}

} // namespace sinter::engine