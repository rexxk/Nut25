#pragma once

#include "Core/Base.h"
#include "Scene/Camera.h"


namespace Nut
{


	class CameraController
	{
	public:
		CameraController(Ref<Camera> camera);

		auto Update(double timestep) -> void;

	private:
		Ref<Camera> m_Camera{ nullptr };

		float m_WalkSpeed{ 1.0f };
		float m_MouseSpeed{ 1.0f };
		double m_Timestep{ 0.0 };
	};


}
