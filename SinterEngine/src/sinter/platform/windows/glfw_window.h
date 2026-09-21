#pragma once

// Internal
#include <sinter/engine/window/window.h>

// External
#include <GLFW/glfw3.h>
#if defined(SINTER_PLATFORM_WINDOWS)
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#endif // SINTER_PLATFORM_WINDOWS

namespace sinter::platform
{

	using namespace sinter::engine;

	class GlfwWindow final : public Window
	{
	public:
		GlfwWindow() = default;
		~GlfwWindow() override = default;

		void Init(const WindowConfiguration& p_configuration) override;
		void Shutdown() override;

		void PollEvents() override;

		void SetTitle(const char* p_title) override;
		void SetSize(u32 p_width, u32 p_height) override;
		void SetPosition(i32 p_x, i32 p_y) override;

		void SetCursorPosition(f32 p_x, f32 p_y) override;
		void SetCursorMode(CursorModeFlags p_mode) override;
		void SetWindowMode(WindowModeFlags p_mode) override;

		void SetUserData(void* p_ptrData) override;

		void* GetUserData() override;

		static GlfwWindow* Create(const WindowConfiguration& p_configuration);

	private:
		void SetWindowCreationHints();

		void SetWindowCallbacks();
		void SetKeyboardCallbacks();
		void SetMouseCallbacks();

	private:
		struct WindowInternalState
		{
			HINSTANCE instance_handle;
			HWND window_handle;
		};

		void* m_userData = nullptr;

		GLFWwindow* m_handle{ nullptr };
		GLFWmonitor* m_monitor{ nullptr };
		const GLFWvidmode* m_video_mode{ nullptr };
	};

} // namespace sinter::platform