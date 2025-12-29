#pragma once

#include "Core/Base.h"
#include "Core/Buffer.h"

#include <cstdint>



namespace Nut
{


	class VertexBuffer
	{
	public:
		static auto Create(Ref<Buffer> buffer) -> Ref<VertexBuffer>;
		static auto Create(const void* data, uint32_t size, uint32_t stride) -> Ref<VertexBuffer>;

		VertexBuffer() = default;
		virtual ~VertexBuffer() = default;

		virtual auto SetData(Ref<Buffer> buffer) -> void {}
		virtual auto SetData(const void* data, uint32_t size) -> void {}
		virtual auto UpdateData(const void* data, uint32_t size) -> void {}

		virtual auto Handle() const -> uint32_t = 0;
		virtual auto Stride() const -> const uint32_t { return 0u; }

	};


	class IndexBuffer
	{
	public:
		static auto Create(Ref<Buffer> buffer) -> Ref<IndexBuffer>;
		static auto Create(const void* data, uint32_t size) -> Ref<IndexBuffer>;

		IndexBuffer() = default;
		virtual ~IndexBuffer() = default;

		virtual auto SetData(Ref<Buffer> buffer) -> void {}
		virtual auto SetData(const void* data, uint32_t size) -> void {}

		virtual auto IndexCount() const -> uint32_t = 0;
		virtual auto Handle() const -> uint32_t = 0;
	};


	class UniformBuffer
	{
	public:
		static auto Create(Ref<Buffer> buffer) -> Ref<UniformBuffer>;
		static auto Create(const void* data, uint32_t size) -> Ref<UniformBuffer>;

		UniformBuffer() = default;
		virtual ~UniformBuffer() = default;

		virtual auto SetData(Ref<Buffer> buffer) -> void {}
		virtual auto SetData(const void* data, uint32_t size) -> void {}

		virtual auto Bind() const -> void {}

		virtual auto Handle() const -> const uint32_t = 0;
	};


}
