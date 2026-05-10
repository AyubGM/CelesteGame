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

inline constexpr std::string_view TextColorTable[] = {
    "\x1b[30m", "\x1b[31m", "\x1b[32m", "\x1b[33m",
    "\x1b[34m", "\x1b[35m", "\x1b[36m", "\x1b[37m",
    "\x1b[90m", "\x1b[91m", "\x1b[92m", "\x1b[93m",
    "\x1b[94m", "\x1b[95m", "\x1b[96m", "\x1b[97m"
};

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