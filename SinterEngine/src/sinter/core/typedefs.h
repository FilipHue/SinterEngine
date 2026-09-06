#pragma once

// Internal
#include <sinter/core/assert.h>

// STL
#include <cstdint>

namespace sinter
{

	typedef unsigned char u8;
	typedef unsigned short u16;
	typedef unsigned int u32;
	typedef unsigned long long u64;

	typedef signed char i8;
	typedef signed short i16;
	typedef signed int i32;
	typedef signed long long i64;

	typedef float f32;
	typedef double f64;

	typedef bool b8;
	typedef int b32;

	constexpr auto I8MAX = INT8_MAX;
	constexpr auto I16MAX = INT16_MAX;
	constexpr auto I32MAX = INT32_MAX;
	constexpr auto I64MAX = INT64_MAX;
	constexpr auto U8MAX = UINT8_MAX;
	constexpr auto U16MAX = UINT16_MAX;
	constexpr auto U32MAX = UINT32_MAX;
	constexpr auto U64MAX = UINT64_MAX;

	constexpr auto I8MIN = INT8_MIN;
	constexpr auto I16MIN = INT16_MIN;
	constexpr auto I32MIN = INT32_MIN;
	constexpr auto I64MIN = INT64_MIN;
	constexpr auto U8MIN = 0;
	constexpr auto U16MIN = 0;
	constexpr auto U32MIN = 0;
	constexpr auto U64MIN = 0;

} // namespace sinter
