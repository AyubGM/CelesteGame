#pragma once
#include "File.h"
#include "Logger.h"
#include <sys/stat.h>
#include <cstdio>
#include <cstring>

namespace CelesteGame
{
    // Uses stat to get last modified time
    long long GetTimestamp(const char* filePath)
    {
        struct stat file_stat = {};
        if (stat(filePath, &file_stat) == 0)
        {
            return static_cast<long long>(file_stat.st_mtime);
        }
        return 0;
    }

    // Faster than opening/closing: check access rights
    bool FileExists(const char* filePath)
    {
        SD_ASSERT(filePath, "No filePath supplied!");
        struct stat buffer;
        return (stat(filePath, &buffer) == 0);
    }

    long GetFileSize(FILE* file)
    {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        return size;
    }

    static char* ReadFileInternal(FILE* file, long size, int* out_fileSize, char* buffer)
    {
        size_t bytesRead = fread(buffer, 1, size, file);
        buffer[bytesRead] = '\0';

        if (out_fileSize) *out_fileSize = static_cast<int>(bytesRead);

        fclose(file);
        return buffer;
    }

    char* ReadFile(const char* filePath, int* out_fileSize, char* buffer)
    {
        FILE* file = nullptr;
        fopen_s(&file,filePath, "rb");
        if (!file) {
            SD_ERROR("Failed opening File: {}", filePath);
            return nullptr;
        }
        long size = GetFileSize(file);
        return ReadFileInternal(file, size, out_fileSize, buffer);
    }

    // 3. Public: Read using Allocator
    char* ReadFile(const char* filePath, int* out_fileSize, BumpAllocator& bumpAllocator)
    {
        FILE* file = nullptr;
        fopen_s(&file, filePath, "rb");
        if (!file) {
            SD_ERROR("Failed opening File: {}", filePath);
            return nullptr;
        }

        long size = GetFileSize(file);

        char* buffer = static_cast<char*>(bumpAllocator.alloc(size + 1));
        if (!buffer) {
            fclose(file);
            return nullptr;
        }

        return ReadFileInternal(file, size, out_fileSize, buffer);
    }
    void WriteFile(const char* filePath, const char* buffer, int size)
    {
        SD_ASSERT(filePath, "No filePath supplied!");
        SD_ASSERT(buffer, "No buffer supplied!");

        FILE* file = nullptr;
        fopen_s(&file, filePath, "wb");
        if (!file)
        {
            SD_ERROR("Failed opening File for write: {}", filePath);
            return;
        }

        fwrite(buffer, 1, size, file);
        fclose(file);
    }

    bool CopyFile(const char* srcPath, const char* destPath, BumpAllocator& bumpAllocator)
    {
        int size = 0;
        char* data = ReadFile(srcPath, &size, bumpAllocator);

        if (data)
        {
            WriteFile(destPath, data, size);
            return true;
        }

        return false;
    }
}