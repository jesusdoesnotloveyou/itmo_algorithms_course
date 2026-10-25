#pragma once

#include "Utils.h"
#include <iostream>
#include <corecrt_malloc.h>

#define _MB(x) 1024 * 1024 * (x)
#define _KB(x) 1024 * (x)

namespace Scald
{
	// Allocator interface class
	class Allocator
	{
	public:
		Allocator(size_t initialSize, size_t alignment)
			: m_totalSize(initialSize)
			, m_alignment(alignment)
		{
		}

		virtual ~Allocator()
		{
			free(m_startPtr);
			m_startPtr = nullptr;
		}

		virtual void Init() = 0;
		virtual void* Allocate(size_t size) = 0;
		
	protected:
		size_t m_totalSize = 0u;
		size_t m_alignment = 0u;
		void* m_startPtr = nullptr;
	};

	class LinearAllocator final : public Allocator
	{
	public:
		LinearAllocator(size_t initialSize, size_t alignment = 16u)
			: Allocator(initialSize, alignment)
		{
			m_offset = 0u;
		}

		~LinearAllocator() override = default;

		void Reset()
		{
			m_offset = 0u;
		}

		// Debug
		void* GetCurrentOffset()
		{
			return reinterpret_cast<void*>(reinterpret_cast<size_t>(m_startPtr) + m_offset);
		}

		void* Allocate(size_t size) override
		{
			// lock if there is a multithreaded environment
			
			size_t newOffset = (m_alignment != 0u) ? (Utils::CalculateAlign(m_offset, m_alignment)) : m_offset;

			if (newOffset > m_totalSize || size > m_totalSize - newOffset)
			{
				// log error
				return nullptr;
			}

			m_offset = newOffset + size;
			
			const size_t currentAddress = reinterpret_cast<size_t>(m_startPtr) + newOffset;
			return reinterpret_cast<void*>(currentAddress);
		}

		void Init() override
		{
			if (m_startPtr)
			{
				free(m_startPtr);
				m_startPtr = nullptr;
			}
			m_startPtr = malloc(m_totalSize);

			std::cout << "Allocator initialized with start at memory address: " << m_startPtr << "\n";
		}

	private:
		size_t m_offset = 0u;
	};
}