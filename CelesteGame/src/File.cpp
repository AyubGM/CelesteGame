#pragma once
#include "File.h"
#include "Logger.h"

#include <fstream>
#include <optional>

#include <chrono>

namespace CelesteGame
{
    // Uses stat to get last modified time
    long long GetTimestamp(const std::filesystem::path& filePath)
    {
        std::error_code ec;
        auto ftime = std::filesystem::last_write_time(filePath, ec);

        if (ec) return 0;

        return std::chrono::duration_cast<std::chrono::seconds>(
            ftime.time_since_epoch()).count();
    }

    bool FileExists(const std::filesystem::path& filePath)
    {
        SD_ASSERT(!filePath.empty(), "No filePath supplied!");
        std::error_code ec;
        return std::filesystem::exists(filePath, ec);
    }

    std::optional<uintmax_t> GetFileSize(const std::filesystem::path& filePath)
    {
        std::error_code ec;
        auto size = std::filesystem::file_size(filePath, ec);
        if (ec) return std::nullopt;
        return size;
    }

    std::optional<std::span<char>> ReadFile(const std::filesystem::path& filePath, std::span<char> buffer)
    {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        if (!file)
        {
            SD_ERROR("Failed opening File: {}", filePath.string());
            return std::nullopt;
        }

        auto size = file.tellg();

        if (size < 0 || static_cast<size_t>(size) > buffer.size() - 1)
        {
            SD_ERROR("Buffer too small or invalid for File: {}", filePath.string());
            return std::nullopt;
        }

        file.seekg(0, std::ios::beg);
        if (file.read(buffer.data(), size))
        {
            buffer[size] = '\0';
            return buffer.first(size);
        }

        return std::nullopt;
    }


    inline void WriteFile(const std::filesystem::path& filePath, std::span<const char> buffer)
    {
        SD_ASSERT(!filePath.empty(), "No filePath supplied!");
        SD_ASSERT(!buffer.empty(), "No buffer supplied!");

        std::ofstream file(filePath, std::ios::binary);
        if (!file)
        {
            SD_ERROR("Failed opening File for write: {}", filePath.string());
            return;
        }

        file.write(buffer.data(), buffer.size());
    }

    inline bool CopyFile(const std::filesystem::path& srcPath, const std::filesystem::path& destPath)
    {
        std::error_code ec;
        return std::filesystem::copy_file(srcPath, destPath, std::filesystem::copy_options::overwrite_existing, ec);
    }
}