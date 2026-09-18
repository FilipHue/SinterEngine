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

		template<typename T>
		void CopyMem(T* p_ptrDestination, const T* p_ptrSource, size_t p_count)
		{
			std::memcpy(p_ptrDestination, p_ptrSource, sizeof(T) * p_count);
		}

		template<typename T>
		void SetMem(T* p_ptrDestination, u8 value, size_t p_count)
		{
			std::memset(p_ptrDestination, value, sizeof(T) * p_count);
		}

		template<typename T>
		void MoveMem(T* p_ptrDestination, const T* p_ptrSource, size_t p_count)
		{
			std::memmove(p_ptrDestination, p_ptrSource, sizeof(T) * p_count);
		}

		template<typename T>
		void ZeroMem(T* p_ptrDestination, size_t p_count)
		{
			SetMem(p_ptrDestination, 0, p_count);
		}

		template<typename T>
		i32 CompareMem(const T* p_ptrLhs, const T* p_ptrRhs, size_t p_count, i32* p_firstDifferenceIndex = nullptr)
		{
			const u8* l_lhsBytes = REINTERPRET_CAST(const u8*, p_ptrLhs);
			const u8* l_rhsBytes = REINTERPRET_CAST(const u8*, p_ptrRhs);
			size_t l_total_bytes = p_count * sizeof(T);

			i32 l_result;
			for (size_t i = 0; i < l_total_bytes; ++i)
			{
				if (l_lhsBytes[i] != l_rhsBytes[i])
				{
					l_result = (l_lhsBytes[i] < l_rhsBytes[i]) ? -1 : 1;
					if (p_firstDifferenceIndex)
					{
						*p_firstDifferenceIndex = i;
					}
					return l_result;

				}
			}

			l_result = 0;
			if (p_firstDifferenceIndex)
			{
				*p_firstDifferenceIndex = 0;
			}

			return l_result;
		}

		template<typename T>
		void FillMem(T* p_ptrDestination, u8 value, size_t p_count)
		{
			u8* l_destination_bytes = REINTERPRET_CAST(u8*, p_ptrDestination);
			std::memset(l_destination_bytes, value, p_count * sizeof(T));
		}

		template<typename T, typename Pattern>
		void FillMemPattern(T* p_ptrDestination, const Pattern& pattern, size_t p_count)
		{
			u8* l_destination_bytes = REINTERPRET_CAST(u8*, p_ptrDestination);
			const u8* l_pattern_bytes = REINTERPRET_CAST(const u8*, &pattern);
			size_t l_pattern_size = sizeof(Pattern);
			size_t l_total_size = p_count * sizeof(T);

			for (size_t i = 0; i < l_total_size; i += l_pattern_size)
			{
				size_t l_copy_size = MIN(l_pattern_size, l_total_size - i);
				std::memcpy(l_destination_bytes + i, l_pattern_bytes, l_copy_size);
			}
		}

		template<typename T, typename Callback>
		void FillMemCallback(T* p_ptrDestination, size_t p_count, Callback p_callback)
		{
			for (size_t i = 0; i < p_count; ++i)
			{
				p_ptrDestination[i] = p_callback(i);
			}
		}

		template<typename T>
		b8 IsAligned(const T* p_ptrData, size_t p_alignment = alignof(T))
		{
			uintptr_t l_addr = REINTERPRET_CAST(uintptr_t, p_ptrData);
			return (l_addr % p_alignment) == 0;
		}

		template<typename T>
		T* GetAligned(T* p_ptrData, size_t p_alignment = alignof(T))
		{
			uintptr_t l_addr = REINTERPRET_CAST(uintptr_t, p_ptrData);
			uintptr_t l_aligned = (l_addr + p_alignment - 1) & ~(p_alignment - 1);
			return REINTERPRET_CAST(T*, l_aligned);
		}

		template<typename T>
		T* ValidateAndAlign(T* p_ptrData, size_t p_alignment = alignof(T))
		{
			if (!IsAligned(p_ptrData, p_alignment))
			{
				SE_CORE_WARN("Aligning pointer to {}", p_alignment);
				return GetAligned(p_ptrData, p_alignment);
			}
			return p_ptrData;
		}

	private:
		MemorySystem() = default;
		~MemorySystem() = default;
	};

} // namespace sinter::core
