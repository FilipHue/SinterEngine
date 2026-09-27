#pragma once

// Internal
#include "input_codes.h"

#include <sinter/core/defines.h>
#include <sinter/core/types/array.h>

namespace sinter::engine
{

	struct InputState
	{
		std::array<b8, MAX_KEY_COUNT> keys_current_frame{};
		std::array<b8, MAX_KEY_COUNT> keys_last_frame{};

		std::array<b8, MAX_MOUSE_BUTTON_COUNT> mouse_buttons_current_frame{};
		std::array<b8, MAX_MOUSE_BUTTON_COUNT> mouse_buttons_last_frame{};

		f32 mouse_x = 0.0f;
		f32 mouse_y = 0.0f;
		f32 mouse_x_prev = 0.0f;
		f32 mouse_y_prev = 0.0f;
		f32 mouse_delta_x = 0.0f;
		f32 mouse_delta_y = 0.0f;
		f32 mouse_scroll_x = 0.0f;
		f32 mouse_scroll_y = 0.0f;

		std::array<b8, MAX_GAMEPAD_BUTTON_COUNT> gamepad_buttons_current_frame{};
		std::array<b8, MAX_GAMEPAD_BUTTON_COUNT> gamepad_buttons_last_frame{};
		std::array<f32, MAX_GAMEPAD_AXIS_COUNT> gamepad_axes{};
	};

	constexpr InputState NULL_INPUT_STATE = {
		.keys_current_frame = {},
		.keys_last_frame = {},
		.mouse_buttons_current_frame = {},
		.mouse_buttons_last_frame = {},
		.mouse_x = 0.0f,
		.mouse_y = 0.0f,
		.mouse_x_prev = 0.0f,
		.mouse_y_prev = 0.0f,
		.mouse_delta_x = 0.0f,
		.mouse_delta_y = 0.0f,
		.mouse_scroll_x = 0.0f,
		.mouse_scroll_y = 0.0f,
		.gamepad_buttons_current_frame = {},
		.gamepad_buttons_last_frame = {},
		.gamepad_axes = {}
	};

} // namespace sinter::engine
