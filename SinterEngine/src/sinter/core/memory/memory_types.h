#pragma once

// STL
#include <memory>

namespace sinter::core
{

	template <typename T>
	using UniquePtr = std::unique_ptr<T>;

	template <typename T>
	using SharedPtr = std::shared_ptr<T>;

} // namespace sinter::core
