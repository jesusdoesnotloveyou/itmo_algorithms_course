#include "MemoryManager.h"
#include <windows.h>

constexpr int CA_ALLOC_LIMIT = 10 * 1024 * 1024;
constexpr int FSA_ALLOC_LIMIT = 512;

MemoryAllocator::MemoryAllocator() 
	:	m_is_initialized{ false },
		m_block_size{ 0 },
		m_start_ptr{ nullptr },
		m_end_ptr{ nullptr }
{
}

void MemoryAllocator::init()
{
	if (m_is_initialized) return;



	m_start_ptr = nullptr;
	m_end_ptr = nullptr;
	VirtualAlloc(m_start_ptr, m_block_size, MEM_RESERVE, PAGE_NOACCESS);
}

MemoryAllocator::~MemoryAllocator()
{
	free(m_start_ptr);
}

void MemoryAllocator::dumpStat() const
{
	// stat per allocator
	//for ()
}

void MemoryAllocator::dumpBlocks() const
{
	// stat allocator
	//for ()
}

void* MemoryAllocator::alloc(size_t size)
{	
	if (size > m_block_size)
	{

	}

	if (size > CA_ALLOC_LIMIT) return VirtualAlloc(m_start_ptr, size, MEM_COMMIT, PAGE_READWRITE);
	
	if (size > FSA_ALLOC_LIMIT)
	{
		// CA alloc

		return nullptr;
	}
	
	return VirtualAlloc(m_start_ptr, size, MEM_COMMIT, PAGE_READWRITE);
}

void MemoryAllocator::destroy()
{
	if (!m_start_ptr) return;

	assert(m_start_ptr && "");
	VirtualFree(m_start_ptr, 0, MEM_FREE);
}

void MemoryAllocator::free(void* p)
{
	assert(p && "");

	std::free(p);
	p = nullptr;
}