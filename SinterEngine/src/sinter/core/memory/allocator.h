#pragma once

// Internal
#include "memory_utils.h"

#include <sinter/core/assert.h>
#include <sinter/core/logging/logger.h>

namespace sinter::core
{

	class IAllocatorBase
	{
	public:
		IAllocatorBase() = default;
		virtual ~IAllocatorBase() = default;

		virtual void Init(size_t size) = 0;
		virtual void Shutdown() = 0;
		virtual void Reset() = 0;
	};

	template <typename T>
	class TAllocator
	{
	public:
		TAllocator() = default;
		virtual ~TAllocator() = default;

		virtual T* Allocate(size_t size) = 0;
		virtual void Deallocate(T* ptr) = 0;
	};

	template <typename T>
	class LinearAllocator : public TAllocator<T>, public IAllocatorBase
	{
	public:
		LinearAllocator() = default;
		virtual ~LinearAllocator() = default;

		void Init(size_t size) override
		{
			Shutdown();

			m_memory = SafeMalloc<T>(size);
			m_size = size;
			m_offset = 0;
		}

		void Shutdown() override
		{
			SafeFree(m_memory);
			m_size = 0;
			m_offset = 0;
		}

		void Reset() override
		{
			m_offset = 0;
		}

		T* Allocate(size_t size) override
		{
			SE_ASSERT(m_memory != nullptr, "Allocator not initialized.");
			SE_ASSERT(size > 0, "Cannot allocate zero bytes.");

			size_t alignedSize = AlignSize<T>(size, alignof(std::max_align_t));
			if (m_offset + alignedSize > m_size)
			{
				SE_CORE_WARN("LinearAllocator: Out of memory. Requested size: {}, Available size: {}", alignedSize, m_size - m_offset);
				return nullptr;
			}
			T* ptr = REINTERPRET_CAST(T*, REINTERPRET_CAST(uintptr_t, m_memory) + m_offset);
			m_offset += alignedSize;
			return ptr;
		}

		void Deallocate(T* ptr) override
		{
			// Linear allocator does not support deallocation of individual objects.
			// Deallocation is done by resetting the allocator.
		}

	protected:
		T* m_memory = nullptr;
		size_t m_size = 0;
		size_t m_offset = 0;
	};

} // namespace sinter::core
