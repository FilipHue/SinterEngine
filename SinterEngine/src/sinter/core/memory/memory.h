#pragma once

// Internal
#include "memory_types.h"
#include "memory_utils.h"

#include <sinter/core/patterns/singleton.h>

namespace sinter::core
{

	class MemorySystem final : public Singleton<MemorySystem>
	{
		friend class Singleton<MemorySystem>;

	public:
		void Init();
		void Shutdown();

		void OnFrameStart();
		void OnFrameEnd();

		template<typename T>
		void CopyMem(T* p_ptrDestination, const T* p_ptrSource, size_t count)
		{
			std::memcpy(p_ptrDestination, p_ptrSource, sizeof(T) * count);
		}

		template<typename T>
		void SetMem(T* p_ptrDestination, u8 value, size_t count)
		{
			std::memset(p_ptrDestination, value, sizeof(T) * count);
		}

		template<typename T>
		void MoveMem(T* p_ptrDestination, const T* p_ptrSource, size_t count)
		{
			std::memmove(p_ptrDestination, p_ptrSource, sizeof(T) * count);
		}

		template<typename T>
		void ZeroMem(T* p_ptrDestination, size_t count)
		{
			SetMem(p_ptrDestination, 0, count);
		}

		template<typename T>
		i32 CompareMem(const T* p_ptrLhs, const T* p_ptrRhs, size_t count, i32* p_first_difference_index = nullptr)
		{
			const u8* l_lhsBytes = REINTERPRET_CAST(const u8*, p_ptrLhs);
			const u8* l_rhsBytes = REINTERPRET_CAST(const u8*, p_ptrRhs);
			size_t l_total_bytes = count * sizeof(T);

			i32 result;
			for (size_t i = 0; i < l_total_bytes; ++i)
			{
				if (l_lhsBytes[i] != l_rhsBytes[i])
				{
					result = (l_lhsBytes[i] < l_rhsBytes[i]) ? -1 : 1;
					if (p_first_difference_index)
					{
						*p_first_difference_index = i;
					}
					return result;

				}
			}

			result = 0;
			if (p_first_difference_index)
			{
				*p_first_difference_index = 0;
			}

			return result;
		}

		template<typename T>
		void FillMem(T* p_ptrDestination, u8 value, size_t count)
		{
			u8* l_destination_bytes = REINTERPRET_CAST(u8*, p_ptrDestination);
			std::memset(l_destination_bytes, value, count * sizeof(T));
		}

		template<typename T, typename Pattern>
		void FillMemPattern(T* p_ptrDestination, const Pattern& pattern, size_t count)
		{
			u8* l_destination_bytes = REINTERPRET_CAST(u8*, p_ptrDestination);
			const u8* l_pattern_bytes = REINTERPRET_CAST(const u8*, &pattern);
			size_t l_pattern_size = sizeof(Pattern);
			size_t l_total_size = count * sizeof(T);

			for (size_t i = 0; i < l_total_size; i += l_pattern_size)
			{
				size_t l_copy_size = MIN(l_pattern_size, l_total_size - i);
				std::memcpy(l_destination_bytes + i, l_pattern_bytes, l_copy_size);
			}
		}

		template<typename T, typename Callback>
		void FillMemCallback(T* p_ptrDestination, size_t count, Callback callback)
		{
			for (size_t i = 0; i < count; ++i)
			{
				p_ptrDestination[i] = callback(i);
			}
		}

		template<typename T>
		b8 IsAligned(const T* ptr, size_t alignment = alignof(T))
		{
			uintptr_t addr = REINTERPRET_CAST(uintptr_t, ptr);
			return (addr % alignment) == 0;
		}

		template<typename T>
		T* GetAligned(T* ptr, size_t alignment = alignof(T))
		{
			uintptr_t addr = REINTERPRET_CAST(uintptr_t, ptr);
			uintptr_t aligned = (addr + alignment - 1) & ~(alignment - 1);
			return REINTERPRET_CAST(T*, aligned);
		}

		template<typename T>
		T* ValidateAndAlign(T* ptr, size_t alignment = alignof(T))
		{
			if (!IsAligned(ptr, alignment))
			{
				SE_CORE_WARN("Pointer not aligned to {} bytes. Aligning...", alignment);
				return GetAligned(ptr, alignment);
			}
			return ptr;
		}

	private:
		MemorySystem() = default;
		~MemorySystem() = default;
	};

} // namespace sinter::core
