#pragma once

#include <chrono>


namespace Nut
{


	class Timer
	{
	public:
		Timer()
		{
			Reset();
		}

		auto Reset() -> void
		{
			m_StartTime = std::chrono::steady_clock::now();
		}

		auto ElapsedTime() -> double
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - m_StartTime).count() / 1000.0;
		}

	private:
		std::chrono::steady_clock::time_point m_StartTime{};
	};


}
