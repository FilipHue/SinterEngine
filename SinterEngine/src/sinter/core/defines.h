#pragma once

// Internal
#include <sinter/core/platform.h>

#if defined(SE_COMPILER_MSVC)
	#define FORCE_INLINE __forceinline
	#define DEBUG_BREAK __debugbreak()
	#define __FUNC__ __FUNCTION__
#elif defined(SE_COMPILER_GCC) || defined(SE_COMPILER_CLANG)
	#define FORCE_INLINE __attribute__((always_inline))
	#define DEBUG_BREAK __builtin_trap()
	#define __FUNC__ __PRETTY_FUNCTION__
#else
	#error "Compiler not supported"
#endif // SE_COMPILER_MSVC

#define _TO_STRING_IMPL(x) #x
#define TO_STRING(x) _TO_STRING_IMPL(x)
#define _CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) _CONCAT_IMPL(x, y)

#define STATIC_CAST(type, expr) static_cast<type>(expr)
#define REINTERPRET_CAST(type, expr) reinterpret_cast<type>(expr)
#define INLINE inline

#define BIT(x) (1 << x)

#define DEFINE_ENUM_BITWISE_OPERATORS(EnumType) \
	INLINE EnumType operator|(EnumType a, EnumType b) { return STATIC_CAST(EnumType, STATIC_CAST(u32, a) | STATIC_CAST(u32, b)); } \
	INLINE EnumType operator&(EnumType a, EnumType b) { return STATIC_CAST(EnumType, STATIC_CAST(u32, a) & STATIC_CAST(u32, b)); } \
	INLINE EnumType operator~(EnumType a) { return STATIC_CAST(EnumType, ~STATIC_CAST(u32, a)); }

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define CLAMP(x, lower, higher) (MAX((lower), MIN((x), (higher))))

#define EXIT(x) std::exit(x)
#define NO_OP (void)0

#define BIND_EVENTCALLBACK(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define DEFAULT_CTOR(Class) Class() = default;
#define DEFAULT_DTOR(Class) ~Class() = default;

#define DEFAULT_COPY(Class) \
	Class(const Class&) = default; \
	Class& operator=(const Class&) = default;

#define DEFAULT_MOVE(Class) \
	Class(Class&&) = default; \
	Class& operator=(Class&&) = default;

#define RULE_OF_FIVE(Class) \
	DEFAULT_CTOR(Class) \
	DEFAULT_DTOR(Class) \
	DEFAULT_COPY(Class) \
	DEFAULT_MOVE(Class)

#define NO_DEFAULT_CTOR(ClassName) \
	ClassName() = delete;

#define NO_DEFAULT_DTOR(ClassName) \
	~ClassName() = delete;

#define NO_COPY(ClassName) \
	ClassName(const ClassName&) = delete; \
	ClassName& operator=(const ClassName&) = delete;

#define NO_MOVE(ClassName) \
	ClassName(ClassName&&) = delete; \
	ClassName& operator=(ClassName&&) = delete;
