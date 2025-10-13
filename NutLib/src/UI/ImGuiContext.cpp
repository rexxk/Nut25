#include "UI/ImGuiContext.h"

#include "Core/Log.h"

#include "Events/EventHandler.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


namespace Nut
{

	
	auto ImGuiContext::Initialize(GLFWwindow* window) -> void
	{
		LOG_CORE_INFO("Initializing ImGui");

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window, false);
		ImGui_ImplOpenGL3_Init();

		EventHandler::Subscribe(EventType::MouseButtonPress, [](Ref<Event> event)
			{
				Ref<MouseButtonPressedEvent> e = std::dynamic_pointer_cast<MouseButtonPressedEvent>(event);

				ImGuiIO& io = ImGui::GetIO();
				io.MouseDown[static_cast<int>(e->Button())] = true;
			});

		EventHandler::Subscribe(EventType::MouseButtonRelease, [](Ref<Event> event)
			{
				Ref<MouseButtonReleasedEvent> e = std::dynamic_pointer_cast<MouseButtonReleasedEvent>(event);

				ImGuiIO& io = ImGui::GetIO();
				io.MouseDown[static_cast<int>(e->Button())] = false;
			});

		EventHandler::Subscribe(EventType::MouseMove, [](Ref<Event> event)
			{
				Ref<MouseMovedEvent> e = std::dynamic_pointer_cast<MouseMovedEvent>(event);

				ImGuiIO& io = ImGui::GetIO();
				io.MousePos = ImVec2(static_cast<float>(e->X()), static_cast<float>(e->Y()));
			});
	}

	auto ImGuiContext::Shutdown() -> void
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
	}

	auto ImGuiContext::BeginFrame() -> void
	{
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
	}

	auto ImGuiContext::EndFrame() -> void
	{
		ImGui::EndFrame();
	}

	auto ImGuiContext::Render() -> void
	{
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();

			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
	}

}
