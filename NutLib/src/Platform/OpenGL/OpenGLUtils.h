#pragma once

#include <cstdint>
#include <glad/glad.h>


namespace Nut
{

	auto ToNative(GLenum type) -> GLenum;
	auto EnumLength(GLenum type) -> uint32_t;
	auto EnumCount(GLenum type) -> GLuint;



}
