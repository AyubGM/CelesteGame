#include "BumpAllocator.h"
#include "Logger.h"

namespace CelesteGame
{
	BumpAllocator::BumpAllocator(size_t size)
	{
		m_Memory = new std::byte[size]();
		m_Capacity = size;
	}
	BumpAllocator::~BumpAllocator()
	{
		delete[] m_Memory;
	}
	void* BumpAllocator::alloc(size_t size)
	{
		size_t alignedSize = (size + 7) & ~7;

		if (m_Used + alignedSize <= m_Capacity)
		{
			void* result = m_Memory + m_Used;
			m_Used += alignedSize;
			return result;
		}

		SD_ASSERT(false, "BumpAllocator is full! Requested: {}, Available: {}",
			alignedSize, m_Capacity - m_Used);
		return nullptr;
	}
}