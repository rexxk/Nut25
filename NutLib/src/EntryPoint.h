#pragma once

#include "Core/Base.h"
#include "Core/Application.h"



extern Ref<Nut::Application> CreateApplication();


auto main() -> int
{
	Ref<Nut::Application> app = CreateApplication();





	return 0;
}
