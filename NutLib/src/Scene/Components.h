#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Nut
{


	struct TagComponent
	{
		std::string Tag{};

		auto Print() -> void
		{
			LOG_CORE_TRACE("TagComponent: {}", Tag);
		}
	};

	struct TransformComponent
	{
		glm::vec3 Position{ 0.0f };
		glm::vec3 Rotation{ 0.0f };
		glm::vec3 Scale{ 1.0f };

		glm::mat4 TransformMatrix{ 1.0f };

		auto CalculateTransformMatrix() -> const glm::mat4&
		{
			TransformMatrix = glm::mat4(1.0f) * glm::translate(glm::mat4(1.0f), Position)
				* glm::rotate(glm::mat4{ 1.0f }, Rotation.x, glm::vec3{ 1.0f, 0.0f, 0.0f })
				* glm::rotate(glm::mat4{ 1.0f }, Rotation.y, glm::vec3{ 0.0f, 1.0f, 0.0f })
				* glm::rotate(glm::mat4{ 1.0f }, Rotation.z, glm::vec3{ 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4{ 1.0f }, Scale);

			return TransformMatrix;
		}
	};

	struct MeshComponent
	{
		UUID MeshID{};
		std::string MeshName{};

		// Mesh id and local transform for each submesh
		std::vector<std::pair<UUID, TransformComponent>> Meshes{};

		MeshComponent()
		{

		}

		MeshComponent(const std::string& meshName, const TransformComponent& transform)
			: MeshName(meshName)
		{
			UUID id = AssetManager<Scope<Mesh>>::Get(meshName)->ID();
			AddMesh(id, transform);
		}

		auto AddMesh(UUID uuid, const TransformComponent& localTransform) -> void
		{
			Meshes.push_back(std::make_pair(uuid, localTransform));
		}
	};

	struct MaterialComponent
	{

	};

	struct TerrainComponent
	{

	};

//	template<>
//	struct hash<TagComponent>
//	{
//		auto operator()(const TagComponent& component) const -> std::size_t
//		{
//			return hash<TagComponent>()(component);
//		}
//	};

}
