#pragma once

#include "Assets/AssetManager.h"

#include "Core/Base.h"
#include "Core/UUID.h"

#include "ECS/ECS.h"

#include "Renderer/Material.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer.h"

#include <glm/glm.hpp>

#include <string>


namespace Nut
{




	class Entity
	{
	public:
		static auto Create(UUID meshID, const std::string& tag) -> Ref<Entity>;

		Entity(UUID meshID, const std::string& tag);

		auto CreateDebugLines(std::vector<LineVertex>& vertexList) -> void;

//		auto SetEntityID(UUID uuid) -> void { m_EntityID = uuid; }
		auto EntityID() const -> const UUID { return m_EntityID; }
		auto GetMesh() const -> const Scope<Mesh>& { return AssetManager<Scope<Mesh>>::Get(m_MeshID); }

		auto ModelID() -> const UUID { return m_ModelID; }

		template<typename T, typename ... Args>
		auto AddComponent(Args&&... args) -> void
		{
			EntitySystem::AddComponent<T>(m_EntityID, std::forward<Args&&>(args)...);
		}

		template<typename T>
		auto RemoveComponent() -> void
		{
			EntitySystem::RemoveComponent<T>(m_EntityID);
		}

		template<typename T>
		auto HasComponent() -> bool
		{
			return EntitySystem::HasComponent<T>(m_EntityID);
		}

		template<typename T>
		auto GetComponent() -> T&
		{
			return EntitySystem::GetComponent<T>(m_EntityID);
		}


	private:
		UUID m_EntityID{};
		UUID m_MeshID{};
		Material m_Material{};

		// OBSOLETE
		UUID m_ModelID{};

	};


}
