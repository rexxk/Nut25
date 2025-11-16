#pragma once

#include <exception>
#include <string_view>

using namespace std::literals::string_view_literals;


namespace Nut
{


	class Exception : public std::exception
	{
	public:
		Exception(std::string_view what)
			: m_ErrorMessage(what)
		{

		}

		virtual auto what() const -> const char* override
		{
			return m_ErrorMessage.data();
		}

	private:
		std::string_view m_ErrorMessage;
	};


}
