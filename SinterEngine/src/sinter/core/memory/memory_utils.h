#pragma once

// Internal
#include <sinter/core/assert.h>

namespace sinter::core
{

	template <typename T>
	FORCE_INLINE size_t AlignSize(size_t p_size, size_t p_alignment)
	{
		return (p_size + p_alignment - 1) & ~(p_alignment - 1);
	}

	template <typename T>
	T* SafeMalloc(size_t p_size)
	{
		T* l_ptr = STATIC_CAST(T*, malloc(p_size));
		SE_ASSERT(l_ptr != nullptr, "Memory allocation failed.");
		return l_ptr;
	}

	template <typename T>
	T* SafeCalloc(size_t p_num, size_t p_size)
	{
		T* l_ptr = STATIC_CAST(T*, calloc(p_num, p_size));
		SE_ASSERT(l_ptr != nullptr, "Memory allocation failed.");
		return l_ptr;
	}

	template <typename T>
	T* SafeRealloc(T* p_ptrType, size_t p_newSize)
	{
		T* l_ptr = STATIC_CAST(T*, realloc(p_ptrType, p_newSize));
		SE_ASSERT(l_ptr != nullptr, "Memory reallocation failed.");
		return l_ptr;
	}

	template <typename T>
	void SafeDelete(T*& p_ptrType)
	{
		if (p_ptrType)
		{
			delete p_ptrType;
			p_ptrType = nullptr;
		}
	}

	template <typename T>
	void SafeDeleteArray(T*& p_ptrType)
	{
		if (p_ptrType)
		{
			delete[] p_ptrType;
			p_ptrType = nullptr;
		}
	}

	template <typename T>
	void SafeFree(T*& p_ptrType)
	{
		if (p_ptrType)
		{
			free(p_ptrType);
			p_ptrType = nullptr;
		}
	}

} // namespace sinter::core
