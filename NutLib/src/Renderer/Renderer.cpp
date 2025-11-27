#include "Renderer/Renderer.h"

#include "Assets/AssetManager.h"
#include "Core/Base.h"
#include "Core/UUID.h"
#include "Renderer/OpenGLBuffer.h"
#include "Renderer/OpenGLShader.h"
#include "Scene/Model.h"

#include <glad/glad.h>

#include <unordered_map>
#include <vector>


namespace Nut
{

	struct RendererObject
	{
		std::vector<Ref<VertexBuffer>> VertexBuffers;
		Ref<IndexBuffer> IndexBuffer;

		uint32_t InstanceCount{ 0l };
		GLuint VertexArrayObject{ 0l };
	};

	static std::unordered_map<UUID, RendererObject> s_RendererObjects{};

	static RendererObject s_LineRendererObject{};

	auto Renderer::DrawTriangle() -> void
	{

	}


	auto Renderer::DrawInstanced(UUID modelID, const std::vector<glm::mat4>& transformMatrices, const std::unordered_map<GLint, ShaderLayoutInfo>& shaderLayout) -> void
	{
		if (!s_RendererObjects.contains(modelID))
		{
			auto meshIDs = AssetManager<Ref<Model>>::Get(modelID)->MeshIDs();

			RendererObject newRendererObject{};

			for (auto& meshID : meshIDs)
			{
				auto mesh = AssetManager<Ref<Mesh>>::Get(meshID);

				newRendererObject.VertexBuffers.push_back(VertexBuffer::Create(mesh->GetVertices().data(), static_cast<uint32_t>(mesh->GetVertices().size()), sizeof(Vertex)));
				newRendererObject.IndexBuffer = IndexBuffer::Create(mesh->GetIndices().data(), static_cast<uint32_t>(mesh->GetIndices().size()) * sizeof(uint32_t));
			}

			newRendererObject.VertexBuffers.push_back(VertexBuffer::Create(transformMatrices.data(), static_cast<uint32_t>(transformMatrices.size()), sizeof(glm::mat4)));

			glCreateVertexArrays(1, &newRendererObject.VertexArrayObject);

			GLuint stride{ 0 };

			for (auto i = 0; i < shaderLayout.size(); i++)
			{
				if (shaderLayout.find(i) == shaderLayout.end())
					continue;

				auto& layoutInfo = shaderLayout.at(i);


				if (layoutInfo.IsMatrix)
				{
					for (auto j = 0; j < 4; j++)
					{
						glEnableVertexArrayAttrib(newRendererObject.VertexArrayObject, i);
						glVertexArrayAttribFormat(newRendererObject.VertexArrayObject, i, 4, GL_FLOAT, GL_FALSE, j * sizeof(glm::vec4));

						glVertexArrayAttribBinding(newRendererObject.VertexArrayObject, i, layoutInfo.VertexBufferPosition);

						i++;
					}

					glVertexArrayBindingDivisor(newRendererObject.VertexArrayObject, 1, 1);
				}
				else
				{
					glEnableVertexArrayAttrib(newRendererObject.VertexArrayObject, i);
					glVertexArrayAttribFormat(newRendererObject.VertexArrayObject, i, layoutInfo.Count, layoutInfo.Type, GL_FALSE, stride);

					glVertexArrayAttribBinding(newRendererObject.VertexArrayObject, i, layoutInfo.VertexBufferPosition);

					stride += layoutInfo.Size;
				}

			}

			uint32_t i = 0;

			for (auto& vertexBuffer : newRendererObject.VertexBuffers)
			{
				glVertexArrayVertexBuffer(newRendererObject.VertexArrayObject, i++, vertexBuffer->Handle(), 0, vertexBuffer->Stride());
			}

			glVertexArrayElementBuffer(newRendererObject.VertexArrayObject, newRendererObject.IndexBuffer->Handle());


			s_RendererObjects[modelID] = newRendererObject;
		}
		else
		{
			auto& rendererObject = s_RendererObjects[modelID];

			rendererObject.VertexBuffers[1]->UpdateData(transformMatrices.data(), static_cast<uint32_t>(transformMatrices.size()) * sizeof(glm::mat4));
//			rendererObject.VertexBuffers.back()->SetData(transformMatrices.data(), static_cast<uint32_t>(transformMatrices.size()) * sizeof(glm::mat4));
			rendererObject.InstanceCount = static_cast<uint32_t>(transformMatrices.size());

			glBindVertexArray(rendererObject.VertexArrayObject);

			glDrawElementsInstanced(GL_TRIANGLES, rendererObject.IndexBuffer->IndexCount(), GL_UNSIGNED_INT, nullptr, rendererObject.InstanceCount);
		}
	}
	
	auto Renderer::DrawMesh(Ref<Mesh> mesh, const std::unordered_map<GLint, ShaderLayoutInfo>& shaderLayout) -> void
	{
		if (!s_RendererObjects.contains(mesh->MeshID()))
		{
			RendererObject newRendererObject{};

			newRendererObject.VertexBuffers.push_back(VertexBuffer::Create(mesh->GetVertices().data(), static_cast<uint32_t>(mesh->GetVertices().size()), sizeof(Vertex)));
			newRendererObject.IndexBuffer = IndexBuffer::Create(mesh->GetIndices().data(), static_cast<uint32_t>(mesh->GetIndices().size()) * sizeof(uint32_t));
		
			glCreateVertexArrays(1, &newRendererObject.VertexArrayObject);

			GLuint stride{ 0 };

			for (auto i = 0; i < shaderLayout.size(); i++)
			{
				if (shaderLayout.find(i) == shaderLayout.end())
					continue;

				auto& layoutInfo = shaderLayout.at(i);

				glEnableVertexArrayAttrib(newRendererObject.VertexArrayObject, i);
				glVertexArrayAttribFormat(newRendererObject.VertexArrayObject, i, layoutInfo.Count, layoutInfo.Type, GL_FALSE, stride);

				glVertexArrayAttribBinding(newRendererObject.VertexArrayObject, i, layoutInfo.VertexBufferPosition);

				stride += layoutInfo.Size;
			}

			uint32_t i = 0;

			for (auto& vertexBuffer : newRendererObject.VertexBuffers)
			{
				glVertexArrayVertexBuffer(newRendererObject.VertexArrayObject, i++, vertexBuffer->Handle(), 0, vertexBuffer->Stride());
			}

			glVertexArrayElementBuffer(newRendererObject.VertexArrayObject, newRendererObject.IndexBuffer->Handle());

			s_RendererObjects[mesh->MeshID()] = newRendererObject;
		}
		else
		{
			auto& rendererObject = s_RendererObjects[mesh->MeshID()];

			glBindVertexArray(rendererObject.VertexArrayObject);

			glDrawElements(GL_TRIANGLES, rendererObject.IndexBuffer->IndexCount(), GL_UNSIGNED_INT, nullptr);
		}

	}

	auto Renderer::DrawLines(const std::vector<LineVertex>& vertexList, const std::unordered_map<GLint, ShaderLayoutInfo>& shaderLayout) -> void
	{
		if (s_LineRendererObject.VertexArrayObject == 0)
		{
			s_LineRendererObject.VertexBuffers.push_back(VertexBuffer::Create(vertexList.data(), static_cast<uint32_t>(vertexList.size()), sizeof(LineVertex)));

			glCreateVertexArrays(1, &s_LineRendererObject.VertexArrayObject);

			GLuint stride{ 0 };

			for (auto i = 0; i < shaderLayout.size(); i++)
			{
				if (shaderLayout.find(i) == shaderLayout.end())
					continue;

				auto& layoutInfo = shaderLayout.at(i);

				glEnableVertexArrayAttrib(s_LineRendererObject.VertexArrayObject, i);
				glVertexArrayAttribFormat(s_LineRendererObject.VertexArrayObject, i, layoutInfo.Count, layoutInfo.Type, GL_FALSE, stride);

				glVertexArrayAttribBinding(s_LineRendererObject.VertexArrayObject, i, layoutInfo.VertexBufferPosition);

				stride += layoutInfo.Size;
			}

			uint32_t i = 0;

			glVertexArrayVertexBuffer(s_LineRendererObject.VertexArrayObject, i++, s_LineRendererObject.VertexBuffers[0]->Handle(), 0, s_LineRendererObject.VertexBuffers[0]->Stride());
		}
		else
		{
			s_LineRendererObject.VertexBuffers[0]->SetData(vertexList.data(), static_cast<uint32_t>(vertexList.size()));

			glBindVertexArray(s_LineRendererObject.VertexArrayObject);
			glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(vertexList.size()));
//			glDrawElements(GL_TRIANGLES, rendererObject.IndexBuffer->IndexCount(), GL_UNSIGNED_INT, nullptr);
		}

	}

	auto Renderer::UpdateModel(Ref<Model> model) -> void
	{
//		if (!s_RendererObjects.contains(model->ModelID()))
		if (!s_RendererObjects.contains(model->MeshIDs()[0]))
			return;

//		auto& rendererObject = s_RendererObjects[model->ModelID()];
		auto& rendererObject = s_RendererObjects[model->MeshIDs()[0]];
		
		auto meshID = model->MeshIDs()[0];
		auto mesh = AssetManager<Ref<Mesh>>::Get(meshID);
		rendererObject.VertexBuffers[0]->SetData(mesh->GetVertices().data(), static_cast<uint32_t>(mesh->GetVertices().size()));
		rendererObject.IndexBuffer->SetData(mesh->GetIndices().data(), static_cast<uint32_t>(mesh->GetIndices().size() * sizeof(uint32_t)));
	}

}
