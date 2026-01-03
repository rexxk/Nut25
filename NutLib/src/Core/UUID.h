#pragma once

#include <cstdint>
#include <format>

#include <unordered_map>

namespace Nut
{


	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID& other);
//		UUID(UUID&& other);

		operator uint64_t() { return m_UUID; }
		operator const uint64_t() const { return m_UUID; }

	private:
		uint64_t m_UUID{ 0ull };
	};

}

namespace std
{
	template<>
	struct hash<Nut::UUID>
	{
		auto operator()(const Nut::UUID& uuid) const -> std::size_t
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};


	template<>
	struct std::formatter<Nut::UUID>
	{
		constexpr auto parse(std::format_parse_context& ctx)
		{
			return std::begin(ctx);
		}

		auto format(Nut::UUID uuid, std::format_context& ctx) const
		{
			return std::format_to(ctx.out(), "{}", static_cast<uint64_t>(uuid));
		}
	};


}
