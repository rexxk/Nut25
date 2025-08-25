#pragma once

#include <string>


namespace Nut
{

	class Layer
	{
	public:
		Layer(const std::string& debugName);
		virtual ~Layer();

		virtual auto OnAttach() -> void;
		virtual auto OnDetach() -> void;

		virtual auto OnUpdate(double timestep) -> void;

	protected:
		std::string m_DebugName{};
	};

}
