#include "Core/Log.h"

#include <format>
#include <print>


namespace Nut
{

	constexpr auto TypeToAnsiColor(LogType type) -> const std::string
	{
		switch (type)
		{
			case LogType::Info: return "32";
			case LogType::Warning: return "93";
			case LogType::Error: return "31";
			case LogType::Fatal: return "41";
		}

		return "32";
	}


/*	auto Log::PrintString(LogType type, const std::string& string) -> void
	{
//		std::string color = "\033[" + TypeToAnsiColor(type) + "m";
		std::println(std::format("{}", string));
//		std::println(color + "mHello\033[m");
//		std::println("\033[" + TypeToAnsiColor(type) + "m" + string + "\033[m");
	}
*/

}
