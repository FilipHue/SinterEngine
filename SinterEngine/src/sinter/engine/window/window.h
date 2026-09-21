#pragma once

// Internal
#include "window_types.h"

#include <sinter/core/patterns/singleton.h>
#include <sinter/core/types/hashtable.h>

namespace sinter::engine
{

	class WindowSystem;

	class Window
	{
		friend class WindowSystem;

	public:
		Window() = default;
		virtual ~Window() = default;

		virtual void Init(const WindowConfiguration& p_configuration) = 0;
		virtual void Shutdown() = 0;
		virtual void PollEvents() = 0;

		virtual void SetTitle(const char* p_title) = 0;
		virtual void SetSize(u32 p_width, u32 p_height) = 0;
		virtual void SetPosition(i32 p_x, i32 p_y) = 0;

		virtual void SetCursorPosition(f32 p_x, f32 p_y) = 0;
		virtual void SetCursorMode(CursorModeFlags p_mode) = 0;
		virtual void SetWindowMode(WindowModeFlags p_mode) = 0;

		virtual void SetUserData(void* p_ptrData) = 0;

		const char* GetTitle() const { return m_state.title; }
		u32 GetWidth() const { return m_state.width; }
		u32 GetHeight() const { return m_state.height; }

		i32 GetPosX() const { return m_state.posX; }
		i32 GetPosY() const { return m_state.posY; }

		virtual void* GetUserData() = 0;

		b8 IsRunning() const { return m_state.isRunning; }
		b8 IsSuspended() const { return m_state.isSuspended; }
		b8 IsFocused() const { return m_state.isFocused; }
		b8 IsMinimized() const { return m_state.isMinimized; }
		b8 IsFullscreen() const { return m_state.isFullscreen; }

		b8 IsCursorLocked() const { return m_state.isCursorLocked; }

		const WindowConfiguration& GetConfig() const { return m_configuration; }
		const WindowState& GetState() const { return m_state; }

		const WindowRID& GetRID() const { return m_rid; }

	private:
		void SetRID(const WindowRID& p_rid) { m_rid = p_rid; }

	protected:
		WindowConfiguration m_configuration;
		WindowState m_state;
		WindowRID m_rid;
	};

	class WindowSystem : public core::Singleton<WindowSystem>
	{
		friend class Singleton<WindowSystem>;

	public:
		void Init();
		void Shutdown();

		Window* Create(const WindowConfiguration& p_refConfiguration);
		void Destroy(WindowRID p_rid);

		void SetWindowTitle(WindowRID p_rid, const char* p_title);
		void SetWindowSize(WindowRID p_rid, u32 p_width, u32 p_height);
		void SetWindowPosition(WindowRID p_rid, i32 p_x, i32 p_y);
		void SetWindowCursorMode(WindowRID p_rid, CursorModeFlags p_mode);

		void PollEvents();

	private:
		WindowSystem() = default;
		~WindowSystem() = default;

	private:
		struct WindowSlot
		{
			Window* window;
		};

		SEUnorderedMap<WindowRID, WindowSlot> m_windows;
		WindowSystemIntegrationType m_integrationType;
	};

} // namespace sinter::engine
