#pragma once

// Internal
#include "memory_types.h"

namespace sinter
{

	namespace core
	{

		template <typename T, typename... Args>
		UniquePtr<T> MakeUnique(Args&&... args)
		{
			return std::make_unique<T>(std::forward<Args>(args)...);
		}

		template <typename T, typename... Args>
		SharedPtr<T> MakeShared(Args&&... args)
		{
			return std::make_shared<T>(std::forward<Args>(args)...);
		}

	} // namespace core

} // namespace sinter
