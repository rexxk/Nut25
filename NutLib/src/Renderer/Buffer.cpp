#include "Renderer/Buffer.h"
#include "Renderer/RendererContext.h"

#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Nut
{



	auto VertexBuffer::Create(Ref<Buffer> buffer) -> Ref<VertexBuffer>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLVertexBuffer>(buffer);
		}

		return nullptr;
	}
	
	auto VertexBuffer::Create(const void* data, uint32_t size, uint32_t stride) -> Ref<VertexBuffer>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLVertexBuffer>(data, size, stride);
		}

		return nullptr;
	}


	auto IndexBuffer::Create(Ref<Buffer> buffer) -> Ref<IndexBuffer>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLIndexBuffer>(buffer);
		}

		return nullptr;
	}

	auto IndexBuffer::Create(const void* data, uint32_t size) -> Ref<IndexBuffer>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLIndexBuffer>(data, size);
		}

		return nullptr;
	}

	auto UniformBuffer::Create(Ref<Buffer> buffer) -> Ref<UniformBuffer>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLUniformBuffer>(buffer);
		}

		return nullptr;
	}

	auto UniformBuffer::Create(const void* data, uint32_t size) -> Ref<UniformBuffer>
	{
		switch (RendererContext::API())
		{
			case RendererAPI::OpenGL: return CreateRef<OpenGLUniformBuffer>(data, size);
		}

		return nullptr;
	}



}
