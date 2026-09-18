// random.h
#pragma once

#include <sinter/core/assert.h>
#include <sinter/core/defines.h>
#include <sinter/core/typedefs.h>

namespace sinter::core
{
	class Random
	{
	public:
		static f32 GetFloat();
		static f64 GetFloat64();
		static f32 GetFloatInRange(f32 p_min, f32 p_max);
		static f64 GetFloat64InRange(f64 p_min, f64 p_max);

		static i32 GetInt32();
		static u32 GetUInt32();
		static i64 GetInt64();
		static u64 GetUInt64();

		static i32 GetInt32InRange(i32 p_min, i32 p_max);
		static u32 GetUInt32InRange(u32 p_min, u32 p_max);
		static i64 GetInt64InRange(i64 p_min, i64 p_max);
		static u64 GetUInt64InRange(u64 p_min, u64 p_max);

		static b8 GetBool(f32 p_probability);
		static f32 GetNormal32(f32 p_mean, f32 p_stddev);
		static f64 GetNormal64(f64 p_mean, f64 p_stddev);

		template <typename Container>
		static typename Container::value_type Choice(const Container& p_refContainer)
		{
			SE_ASSERT(!p_refContainer.empty(), "Container is empty");
			i32 l_index = GetInt32InRange(0, STATIC_CAST(i32, p_refContainer.size() - 1));
			return p_refContainer[l_index];
		}

		template <typename Container>
		static void Shuffle(Container& p_refContainer)
		{
			SE_ASSERT(!p_refContainer.empty(), "Container is empty");
			for (i32 i = STATIC_CAST(i32, p_refContainer.size()) - 1; i > 0; --i)
			{
				i32 j = GetInt32InRange(0, i);
				std::swap(p_refContainer[i], p_refContainer[j]);
			}
		}

		static void SetSeed(u64 p_seed);
		static void ResetSeed();
	};

} // namespace sinter::core
