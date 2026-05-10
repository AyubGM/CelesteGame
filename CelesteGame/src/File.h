#pragma once
#include "BumpAllocator.h"

namespace CelesteGame
{
    long long GetTimestamp(const char* filePath);
    bool FileExists(const char* filePath);
    char* ReadFile(const char* filePath, int* out_fileSize, char* buffer);
    char* ReadFile(const char* filePath, int* out_fileSize, BumpAllocator& bumpAllocator);
    void WriteFile(const char* filePath, const char* buffer, int size);
    bool CopyFile(const char* srcPath, const char* destPath, BumpAllocator& bumpAllocator);
}