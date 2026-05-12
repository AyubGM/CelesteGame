#pragma once

#include <iostream>
#include <string_view>
#include <sstream>
#include <cstdio>

#if defined(_MSC_VER)
#define SD_DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#define SD_DEBUG_BREAK() __builtin_trap()
#else
#define SD_DEBUG_BREAK() std::abort()
#endif

enum class TextColor {
    BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,
    BRIGHT_BLACK, BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW,
    BRIGHT_BLUE, BRIGHT_MAGENTA, BRIGHT_CYAN, BRIGHT_WHITE,
    COUNT
};

extern const std::string_view TextColorTable[];

template <typename... Args>
void _SD_LOG_INTERNAL(std::string_view prefix, TextColor color, std::format_string<Args...> fmt, Args&&... args) {
    std::string formatted_msg = std::format(fmt, std::forward<Args>(args)...);

    std::cout << TextColorTable[static_cast<int>(color)]
        << prefix << formatted_msg
        << "\033[0m\n";
}

#define SD_DEBUG
#ifdef SD_DEBUG
#define SD_TRACE(fmt, ...) _SD_LOG_INTERNAL("TRACE: ", TextColor::GREEN, fmt, ##__VA_ARGS__)
#define SD_WARN(fmt, ...)  _SD_LOG_INTERNAL("WARN:  ", TextColor::YELLOW, fmt, ##__VA_ARGS__)
#define SD_ERROR(fmt, ...) _SD_LOG_INTERNAL("ERROR: ", TextColor::RED, fmt, ##__VA_ARGS__)

#define SD_ASSERT(condition, fmt, ...) \
        do { \
            if (!(condition)) { \
                SD_ERROR(fmt, ##__VA_ARGS__); \
                SD_DEBUG_BREAK(); \
            } \
        } while (0)
#else
#define SD_TRACE(fmt, ...)
#define SD_WARN(fmt, ...)
#define SD_ERROR(fmt, ...)
#define SD_ASSERT(condition, fmt, ...)
#endif