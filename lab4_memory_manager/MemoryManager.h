#pragma once
#define WIN32_LEAN_AND_MEAN
#include <cassert>
#include <iostream>
#include "LinkedList.h"

class alignas(8) FSAllocator
{
	struct FSABlock
	{};

	LinkedList< FSABlock > FreeList;
};

class alignas(8) CAllocator
{
	CAllocator* next;
	int size;
};

class alignas(8) OSAllocator
{

};

class MemoryAllocator
{
public:
	MemoryAllocator();
	virtual ~MemoryAllocator();

	void init();
	void* alloc(size_t size);

	void destroy();
	void free(void* firstbyte);

	void dumpStat() const;
	void dumpBlocks() const;

private:
	void* m_start_ptr;
	void* m_end_ptr;
	size_t m_block_size;
	size_t m_chunk_size;
	OSAllocator* os;
	FSAllocator fsa;
	CAllocator ca;
	bool m_is_initialized;
};