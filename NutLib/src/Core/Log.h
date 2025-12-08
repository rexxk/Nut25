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


	template<LogType Type, typename... Args>
	class PrintString
	{
	public:
		PrintString(std::format_string<Args...> fmt, Args&&... args)
		{
			std::string color{};

			if (Type == LogType::Info) color = "32";
			if (Type == LogType::Warning) color = "93";
			if (Type == LogType::Error) color = "31";
			if (Type == LogType::Fatal) color = "41";

			const auto log = std::format("\033[{}m{}\033[m", color, std::format(fmt, std::forward<Args>(args)...));

			std::println("{}", log);
		}
	};

	template<LogType Type = {}, class ... Args >
	PrintString(std::format_string<Args...>, Args&& ...) -> PrintString<Type, Args...>;

	template<class ... Args>
	using info = PrintString<LogType::Info, Args...>;

	template<class ... Args>
	using warn = PrintString<LogType::Warning, Args...>;

	template<class ... Args>
	using error = PrintString<LogType::Error, Args...>;

	template<class ... Args>
	using fatal = PrintString<LogType::Fatal, Args...>;
}


#define UNPACK_VARARGS(...) __VA_ARGS__

#define LOG_CORE_INFO(x, ...) Nut::info(x, __VA_ARGS__)
#define LOG_CORE_WARN(x, ...) Nut::warn(x, __VA_ARGS__)
#define LOG_CORE_ERROR(x, ...) Nut::error(x, __VA_ARGS__)
#define LOG_CORE_FATAL(x, ...) Nut::fatal(x, __VA_ARGS__)
