#pragma once

// Internal
#include <sinter/engine/window/window.h>

// Forward declaration of GLFW types to avoid exposing GLFW headers in the public interface of GlfwWindow
struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

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

		void Update() override;

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
		void* m_userData = nullptr;

		GLFWwindow* m_handle{ nullptr };
		GLFWmonitor* m_monitor{ nullptr };
		const GLFWvidmode* m_video_mode{ nullptr };
	};

} // namespace sinter::platform
