#pragma once

#include "gpui/debug/log.h"

#if _WIN32
#define DEBUGBREAK() __debugbreak()
#elif __linux__ || __ANDROID__
#include <signal.h>
#define DEBUGBREAK() raise(SIGTRAP)
#elif __APPLE__
#include <TargetConditionals.h>
#define DEBUGBREAK() __builtin_trap()
#else
#define DEBUGBREAK() exit(2)
#endif

#define GPUI_EXPAND_MACRO(x) x
#define GPUI_STRINGIFY_MACRO(x) #x

#define GPUI_INTERNAL_ASSERT_IMPL(check, msg, ...)                             \
	if (!(check)) {                                                            \
		GPUI_LOG_FATAL(msg, __VA_ARGS__);                              \
		DEBUGBREAK();                                                          \
	}

#define GPUI_INTERNAL_ASSERT_WITH_MSG(check, ...)                              \
	GPUI_INTERNAL_ASSERT_IMPL(check, "Assertion failed: {}", __VA_ARGS__)

#define GPUI_INTERNAL_ASSERT_NO_MSG(check)                                     \
	GPUI_INTERNAL_ASSERT_IMPL(check, "Assertion '{}' failed at {}:{}",         \
			GPUI_STRINGIFY_MACRO(check), __FILE__, __LINE__)

#define GPUI_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro

#define GPUI_INTERNAL_ASSERT_GET_MACRO(...)                                    \
	GPUI_EXPAND_MACRO(GPUI_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__,         \
			GPUI_INTERNAL_ASSERT_WITH_MSG, GPUI_INTERNAL_ASSERT_NO_MSG))

#define GPUI_ASSERT(...)                                                       \
	GPUI_EXPAND_MACRO(GPUI_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__))
