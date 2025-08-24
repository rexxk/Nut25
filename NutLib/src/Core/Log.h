#pragma once


#include <format>
#include <print>
#include <string>
#include <iostream>

namespace Nut
{

	enum class LogType
	{
		Info,
		Warning,
		Error,
		Fatal,
	};


	class Log
	{
	public:

		template<typename... Args>
		static auto PrintString(LogType type, const std::string& string, Args&&... args) -> void
		{
			std::string color;

			switch (type)
			{
				case LogType::Info: color = "32"; break;
				case LogType::Warning: color = "93"; break;
				case LogType::Error: color = "31"; break;
				case LogType::Fatal: color = "41"; break;
			}

			auto s = std::string("\033[" + color + "m" + string + "\033[m");

			const auto log = std::vformat(s, std::make_format_args(std::forward<Args&&>(args)...));
			std::cout << log << "\n";
			//			std::cout << std::vformat(s, std::make_format_args(std::forward<Args&&>(args)...)) << "\n";
		}
	};

}

#define LOG_CORE_INFO(x, ...) Nut::Log::PrintString(Nut::LogType::Info, x, __VA_ARGS__)
#define LOG_CORE_WARN(x, ...) Nut::Log::PrintString(Nut::LogType::Warning, x, __VA_ARGS__)
#define LOG_CORE_ERROR(x, ...) Nut::Log::PrintString(Nut::LogType::Error, x, __VA_ARGS__)
#define LOG_CORE_FATAL(x, ...) Nut::Log::PrintString(Nut::LogType::Fatal, x, __VA_ARGS__)

