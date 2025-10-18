#pragma once


#include "Core/Defines.h"



namespace Nut
{


	class Input
	{
	public:
		static auto Initialize() -> void;

		static auto IsMouseButtonPressed(MouseButton button) -> bool;
		static auto IsKeyPressed(Keys key) -> bool;

		static auto Update() -> void;
	};


}
