#include <iostream>
#include <string_view>
#include <sstream>
#include <cstdio>

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
void _log(std::string_view prefix, TextColor color, std::string_view fmt, Args... args) {
    char buffer[1024];
    std::snprintf(buffer, sizeof(buffer), fmt.data(), args...);

    std::ostringstream oss;
    oss << TextColorTable[static_cast<int>(color)]
        << prefix << buffer
        << "\033[0m";

    std::cout << oss.str() << std::endl;
}

// Inline wrappers
template <typename... Args>
inline void SD_TRACE(std::string_view fmt, Args... args) {
    _log("TRACE: ", TextColor::GREEN, fmt, args...);
}

template <typename... Args>
inline void SD_WARN(std::string_view fmt, Args... args) {
    _log("WARN: ", TextColor::YELLOW, fmt, args...);
}

template <typename... Args>
inline void SD_ERROR(std::string_view fmt, Args... args) {
    _log("ERROR: ", TextColor::RED, fmt, args...);
}

template <typename... Args>
inline void SD_ASSERT(bool condition, std::string_view fmt, Args... args) {
    if (!condition)
    {
        SD_ERROR(fmt, args...);
        __debugbreak();
    }
}