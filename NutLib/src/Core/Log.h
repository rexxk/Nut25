#pragma once


#include <format>
#include <print>
#include <string>
#include <iostream>

namespace Nut
{

	enum class LogType
	{
		Trace,
		Info,
		Warning,
		Error,
		Fatal,
	};


	template<LogType Type, typename... Args>
	class Log
	{
	public:
		Log(std::format_string<Args...> fmt, Args&&... args)
		{
			std::string color{};

			if (Type == LogType::Trace) color = "37";
			if (Type == LogType::Info) color = "32";
			if (Type == LogType::Warning) color = "93";
			if (Type == LogType::Error) color = "31";
			if (Type == LogType::Fatal) color = "41";

			const auto log = std::format("\033[{}m{}\033[m", color, std::format(fmt, std::forward<Args&&>(args)...));

			std::println("{}", log);
		}
	};

	template<LogType Type = {}, class ... Args >
	Log(std::format_string<Args...>, Args&& ...) -> Log<Type, Args...>;

	template<class ... Args>
	using trace = Log<LogType::Trace, Args...>;

	template<class ... Args>
	using info = Log<LogType::Info, Args...>;

	template<class ... Args>
	using warn = Log<LogType::Warning, Args...>;

	template<class ... Args>
	using error = Log<LogType::Error, Args...>;

	template<class ... Args>
	using fatal = Log<LogType::Fatal, Args...>;
}


#define LOG_CORE_TRACE(x, ...) Nut::trace(x, __VA_ARGS__)
#define LOG_CORE_INFO(x, ...) Nut::info(x, __VA_ARGS__)
#define LOG_CORE_WARN(x, ...) Nut::warn(x, __VA_ARGS__)
#define LOG_CORE_ERROR(x, ...) Nut::error(x, __VA_ARGS__)
#define LOG_CORE_FATAL(x, ...) Nut::fatal(x, __VA_ARGS__)

#define ASSERT(x, msg, ...) { if (!x) { Nut::error(msg, __VA_ARGS__); __debugbreak(); } }
