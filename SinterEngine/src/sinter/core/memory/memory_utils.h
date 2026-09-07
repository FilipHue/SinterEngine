#pragma once

// Internal
#include <sinter/core/assert.h>

namespace sinter::core
{

	template <typename T>
	FORCE_INLINE void AlignAddress(T*& address, size_t alignment)
	{
		uintptr_t addr = REINTERPRET_CAST(uintptr_t, address);
		uintptr_t alignedAddr = (addr + alignment - 1) & ~(alignment - 1);
		address = REINTERPRET_CAST(T*, alignedAddr);
	}

	template <typename T>
	FORCE_INLINE size_t AlignSize(size_t size, size_t alignment)
	{
		return (size + alignment - 1) & ~(alignment - 1);
	}

	template <typename T>
	T* SafeMalloc(size_t size)
	{
		T* ptr = static_cast<T*>(malloc(size));
		SE_ASSERT(ptr != nullptr, "Memory allocation failed.");
		return ptr;
	}

	template <typename T>
	T* SafeCalloc(size_t num, size_t size)
	{
		T* ptr = static_cast<T*>(calloc(num, size));
		SE_ASSERT(ptr != nullptr, "Memory allocation failed.");
		return ptr;
	}

	template <typename T>
	T* SafeRealloc(T* ptr, size_t newSize)
	{
		ptr = static_cast<T*>(realloc(ptr, newSize));
		SE_ASSERT(ptr != nullptr, "Memory reallocation failed.");
		return ptr;
	}

	template <typename T>
	void SafeDelete(T*& ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}

	template <typename T>
	void SafeDeleteArray(T*& ptr)
	{
		if (ptr)
		{
			delete[] ptr;
			ptr = nullptr;
		}
	}

	template <typename T>
	void SafeFree(T*& ptr)
	{
		if (ptr)
		{
			free(ptr);
			ptr = nullptr;
		}
	}

} // namespace sinter::core
