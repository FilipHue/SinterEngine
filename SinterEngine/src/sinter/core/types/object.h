#pragma once

// Internal
#include <sinter/core/typedefs.h>

// STL
#include <string>

namespace sinter::core
{

	class SEObject
	{
	public:
		SEObject() = default;
		virtual ~SEObject() = default;

		struct ClassType {
			const char* className;
			u64 classID;
		};

		ClassType GetType() const { return m_type; }

	protected:
		ClassType m_type;
	};

} // namespace sinter::core
