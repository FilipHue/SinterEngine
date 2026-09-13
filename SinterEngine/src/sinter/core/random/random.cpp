#include "sepch.h"
#include "random.h"

namespace sinter::core
{

	namespace
	{
		struct ThreadLocalState
		{
			std::mt19937_64 engine;
			std::uniform_real_distribution<f32> float_dist{ 0.0f, 1.0f };
			std::uniform_real_distribution<f64> float64_dist{ 0.0, 1.0 };
			std::normal_distribution<f32> normal_dist{ 0.0f, 1.0f };
			std::normal_distribution<f64> normal64_dist{ 0.0, 1.0 };
		};

		static ThreadLocalState& GetState()
		{
			thread_local ThreadLocalState state{
				std::mt19937_64(std::random_device{}())
			};
			return state;
		}
	}

	using State = ThreadLocalState;

	// ============================================================================
	// FLOATING POINT
	// ============================================================================

	f32 Random::GetFloat()
	{
		return GetState().float_dist(GetState().engine);
	}

	f64 Random::GetFloat64()
	{
		return GetState().float64_dist(GetState().engine);
	}

	f32 Random::GetFloatInRange(f32 p_min, f32 p_max)
	{
		if (p_min == p_max)
		{
			return p_min;
		}

		return std::uniform_real_distribution<f32>(p_min, p_max)(GetState().engine);
	}

	f64 Random::GetFloat64InRange(f64 p_min, f64 p_max)
	{
		if (p_min == p_max)
		{
			return p_min;
		}

		return std::uniform_real_distribution<f64>(p_min, p_max)(GetState().engine);
	}

	// ============================================================================
	// INTEGER
	// ============================================================================

	i32 Random::GetInt()
	{
		// Default range: [0, 100] for practical use
		return GetIntInRange(0, 100);
	}

	i64 Random::GetInt64()
	{
		// Default range: [0, 100] for practical use
		return GetInt64InRange(0, 100);
	}

	u32 Random::GetUInt()
	{
		// Default range: [0, 100] for practical use
		return GetUIntInRange(0, 100);
	}

	u64 Random::GetUInt64()
	{
		// Default range: [0, 100] for practical use
		return GetUInt64InRange(0, 100);
	}

	i32 Random::GetIntInRange(i32 p_min, i32 p_max)
	{
		if (p_min == p_max)
		{
			return p_min;
		}

		return std::uniform_int_distribution<i32>(p_min, p_max)(GetState().engine);
	}

	i64 Random::GetInt64InRange(i64 p_min, i64 p_max)
	{
		if (p_min == p_max)
		{
			return p_min;
		}

		return std::uniform_int_distribution<i64>(p_min, p_max)(GetState().engine);
	}

	u32 Random::GetUIntInRange(u32 p_min, u32 p_max)
	{
		if (p_min == p_max)
		{
			return p_min;
		}

		return std::uniform_int_distribution<u32>(p_min, p_max)(GetState().engine);
	}

	u64 Random::GetUInt64InRange(u64 p_min, u64 p_max)
	{
		if (p_min == p_max)
		{
			return p_min;
		}

		return std::uniform_int_distribution<u64>(p_min, p_max)(GetState().engine);
	}

	// ============================================================================
	// DISTRIBUTIONS
	// ============================================================================

	b8 Random::GetBool(f32 p_probability)
	{
		return GetFloat() < p_probability;
	}

	f32 Random::GetNormal(f32 p_mean, f32 p_stddev)
	{
		return p_mean + p_stddev * GetState().normal_dist(GetState().engine);
	}

	f64 Random::GetNormal64(f64 p_mean, f64 p_stddev)
	{
		return p_mean + p_stddev * GetState().normal64_dist(GetState().engine);
	}

	// ============================================================================
	// SEED
	// ============================================================================

	void Random::SetSeed(u64 p_seed)
	{
		GetState().engine.seed(p_seed);
	}

	void Random::ResetSeed()
	{
		GetState().engine.seed(std::random_device{}());
	}

} // namespace sinter::core
