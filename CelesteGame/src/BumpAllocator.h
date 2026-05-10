#pragma once
//#include <stdlib.h>
#include <string.h>
#include <cstddef>

namespace CelesteGame {
	class BumpAllocator
	{
	public:
		explicit BumpAllocator(size_t size);
		~BumpAllocator();
		BumpAllocator(const BumpAllocator&) = delete;
		BumpAllocator& operator=(const BumpAllocator&) = delete;
		void* alloc(size_t size);
		void inline reset() { m_Used = 0; }
	private:
		size_t m_Capacity = 0;
		size_t m_Used = 0;
		std::byte* m_Memory = nullptr;
	};
}

//struct BumpAllocator
//{
//	size_t Capacity = 0;
//	size_t Used = 0;
//	char* Memory = nullptr;
//};
//
//BumpAllocator MakeBumpAllocator(size_t size)
//{
//	BumpAllocator ba = {};
//
//	ba.Memory = new char[size];
//
//	if (ba.Memory)
//	{
//		ba.Capacity = size;
//		memset(ba.Memory, 0, size);
//	}
//	else
//	{
//		SD_ASSERT(false, "Faild to allocate Memory!");
//	}
//
//	return ba;
//}
//
//char* BumpAlloc(BumpAllocator* bumpAllocator, size_t size)
//{
//	char* result = nullptr;
//
//	size_t allignedSize = (size + 7) & ~7;
//	if (bumpAllocator->Used + allignedSize <= bumpAllocator->Capacity)
//	{
//		result = bumpAllocator->Memory + bumpAllocator->Used;
//		bumpAllocator->Used += allignedSize;
//	}
//	else
//	{
//		SD_ASSERT(false, "BumpAllocator is full");
//	}
//
//	return result;
//}