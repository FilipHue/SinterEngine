#pragma once

// Internal
#include <sinter/core/defines.h>
#include <sinter/core/typedefs.h>
#include <sinter/core/assert.h>

namespace sinter::core
{

	class Random
	{
	public:
		static f32 GetFloat();
		static f64 GetFloat64();
		static i32 GetInt();
		static i64 GetInt64();
		static u32 GetUInt();
		static u64 GetUInt64();

		static f32 GetFloatInRange(f32 p_min, f32 p_max);
		static f64 GetFloat64InRange(f64 p_min, f64 p_max);
		static i32 GetIntInRange(i32 p_min, i32 p_max);
		static i64 GetInt64InRange(i64 p_min, i64 p_max);
		static u32 GetUIntInRange(u32 p_min, u32 p_max);
		static u64 GetUInt64InRange(u64 p_min, u64 p_max);

		static b8 GetBool(f32 p_probability);
		static f32 GetNormal(f32 p_mean, f32 p_stddev);
		static f64 GetNormal64(f64 p_mean, f64 p_stddev);

		template <typename Container>
		static typename Container::value_type Choice(const Container& p_container)
		{
			SE_ASSERT(!p_container.empty(), "Container is empty");
			i32 index = GetIntInRange(0, STATIC_CAST(i32, p_container.size() - 1));
			
			return p_container[index];
		}

		template <typename Container>
		static void Shuffle(Container& p_container)
		{
			SE_ASSERT(!p_container.empty(), "Container is empty");
			for (i32 i = STATIC_CAST(i32, p_container.size()) - 1; i > 0; --i)
			{
				i32 j = GetIntInRange(0, i);
				std::swap(p_container[i], p_container[j]);
			}
		}

		static void SetSeed(u64 p_seed);
		static void ResetSeed();
	};

} // namespace sinter::core
