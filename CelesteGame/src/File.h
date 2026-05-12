#pragma once
#include "BumpAllocator.h"
#include <filesystem>
#include <span>

namespace CelesteGame
{
    long long GetTimestamp(std::filesystem::path& filePath);
    bool FileExists(std::filesystem::path& filePath);
    std::optional<std::span<char>> ReadFile(const std::filesystem::path& filePath, std::span<char> buffer);
    void WriteFile(std::filesystem::path& filePath, std::span<const char> buffer);
    bool CopyFile(const std::filesystem::path& srcPath, const std::filesystem::path& destPath);
}