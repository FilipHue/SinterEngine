#pragma once

// STL
#include <unordered_map>

namespace  sinter::core
{

	template<typename Key, typename Value>
	using SEUnorderedMap = std::unordered_map<Key, Value>;

} // namespace sinter::core
