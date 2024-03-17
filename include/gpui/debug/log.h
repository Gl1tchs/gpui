/*
 * include/gpui/debug/log.h
 *
 * defines log types and macros
 */

#pragma once

#include "gpui/defines.h"

namespace gpui {

enum class LogLevel {
	TRACE = 0,
	INFO,
	WARNING,
	ERROR,
	FATAL,
};

/**
 * logs a message into console buffer nicely
 */
GPUI_API void log(const LogLevel level, const std::string& fmt);

} //namespace gpui

#define GPUI_LOG_TRACE(...)                                                    \
	gpui::log(gpui::LogLevel::TRACE, std::format(__VA_ARGS__))
#define GPUI_LOG_INFO(...)                                                     \
	gpui::log(gpui::LogLevel::INFO, std::format(__VA_ARGS__))
#define GPUI_LOG_WARNING(...)                                                  \
	gpui::log(gpui::LogLevel::WARNING, std::format(__VA_ARGS__))
#define GPUI_LOG_ERROR(...)                                                    \
	gpui::log(gpui::LogLevel::ERROR, std::format(__VA_ARGS__))
#define GPUI_LOG_FATAL(...)                                                    \
	gpui::log(gpui::LogLevel::FATAL, std::format(__VA_ARGS__))
