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
void _log(std::string_view prefix, TextColor color, std::format_string<Args...> fmt, Args&&... args) {
    std::string formatted_msg = std::format(fmt, std::forward<Args>(args)...);

    std::cout << TextColorTable[static_cast<int>(color)]
        << prefix << formatted_msg
        << "\033[0m\n";
}

// Inline wrappers

template <typename... Args>
inline void SD_TRACE(std::format_string<Args...> fmt, Args&&... args) {
    _log("TRACE: ", TextColor::GREEN, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void SD_WARN(std::format_string<Args...> fmt, Args&&... args) {
    _log("WARN: ", TextColor::YELLOW, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void SD_ERROR(std::format_string<Args...> fmt, Args&&... args) {
    _log("ERROR: ", TextColor::RED, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void SD_ASSERT(bool condition, std::format_string<Args...> fmt, Args&&... args) {
    if (!condition) {
        SD_ERROR(fmt, std::forward<Args>(args)...);
        SD_DEBUG_BREAK();
    }
}