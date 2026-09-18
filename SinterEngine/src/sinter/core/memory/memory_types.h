#pragma once

// Internal
#include <sinter/core/defines.h>

// STL
#include <memory>

namespace sinter::core
{

	template <typename T>
	using UniquePtr = std::unique_ptr<T>;

	template <typename T>
	using SharedPtr = std::shared_ptr<T>;

	template <typename T, typename... Args>
	FORCE_INLINE UniquePtr<T> MakeUniquePtr(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename... Args>
	FORCE_INLINE SharedPtr<T> MakeSharedPtr(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

} // namespace sinter::core
