#pragma once

// Internal
#include <sinter/core/defines.h>
#include <sinter/core/typedefs.h>
#include <sinter/core/random/random.h>
#include <sinter/core/types/string.h>

namespace sinter::core
{

	class UUID
	{
	public:
		UUID() : m_UUID(Random::GetUInt64()) { NO_OP; }
		constexpr explicit UUID(u64 p_uuid) : m_UUID(p_uuid) { NO_OP; }

		u64 GetUUID() const { return m_UUID; }

		SEString ToString() const { return std::to_string(m_UUID); }

		operator u64() const { return m_UUID; }
		b8 operator==(const UUID& p_other) const { return m_UUID == p_other.m_UUID; }
		b8 operator!=(const UUID& p_other) const { return m_UUID != p_other.m_UUID; }
		b8 operator<(const UUID& p_other) const { return m_UUID < p_other.m_UUID; }

		static UUID Generate() { return UUID(); }

	private:
		u64 m_UUID;
	};

} // namespace sinter::core

namespace std
{

	template <>
	struct hash<sinter::core::UUID>
	{
		std::size_t operator()(const sinter::core::UUID& p_uuid) const noexcept
		{
			return std::hash<uint64_t>{}(p_uuid);
		}
	};

} // namespace std

namespace fmt
{

	template <>
	struct formatter<sinter::core::UUID>
	{
		template <typename ParseContext>
		constexpr auto parse(ParseContext& ctx)
		{
			return ctx.begin();
		}
		template <typename FormatContext>
		auto format(const sinter::core::UUID& p_uuid, FormatContext& ctx) const
		{
			return format_to(ctx.out(), "{}", p_uuid.GetUUID());
		}
	};

} // namespace fmt
