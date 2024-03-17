/*
 * include/gpui/defines.h
 *
 * defines some helper types as well as some macros
 */

#pragma once

#define GPUI_CONCAT(x, y) x##y

#define GPUI_MAKE_VERSION(major, minor, patch)                                 \
	(((major) << 16) | ((minor) << 8) | (patch))

#define GPUI_GET_MAJOR(version) (((version) >> 16) & 0xFF)
#define GPUI_GET_MINOR(version) (((version) >> 8) & 0xFF)
#define GPUI_GET_PATCH(version) ((version) & 0xFF)

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

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define GPUI_PLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif // _WIN64
#elif defined(__linux__) || defined(__gnu_linux__)
#define GPUI_PLATFORM_LINUX 1
#if defined(__ANDROID__)
#define GPUI_PLATFORM_ANDROID 1
#endif
#elif defined(__unix__)
#define GPUI_PLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
#define GPUI_PLATFORM_POSIX 1
#elif __APPLE__
#define GPUI_PLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
#define GPUI_PLATFORM_IOS 1
#define GPUI_PLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define GPUI_PLATFORM_IOS 1
#elif TARGET_OS_MAC
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif

#ifdef GPUI_EXPORT
#ifdef _MSC_VER
#define GPUI_API __declspec(dllexport)
#else
#define GPUI_API __attribute__((visibility("default")))
#endif // _MSC_VER
#else
#ifdef _MSC_VER
#define GPUI_API __declspec(dllimport)
#else
#define GPUI_API
#endif // _MSC_VER
#endif // GPUI_EXPORT
