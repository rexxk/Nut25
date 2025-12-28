#include "Platform/OpenGL/OpenGLUtils.h"



namespace Nut
{

	auto EnumLength(GLenum type) -> uint32_t
	{
		switch (type)
		{
			case GL_FLOAT: return sizeof(GLfloat);
			case GL_FLOAT_VEC2: return 2 * sizeof(GLfloat);
			case GL_FLOAT_VEC3: return 3 * sizeof(GLfloat);
			case GL_FLOAT_VEC4: return 4 * sizeof(GLfloat);
			case GL_FLOAT_MAT2: return 2 * 2 * sizeof(GLfloat);
			case GL_FLOAT_MAT3: return 3 * 3 * sizeof(GLfloat);
			case GL_FLOAT_MAT4: return 4 * 4 * sizeof(GLfloat);
			case GL_FLOAT_MAT2x3: return 2 * 3 * sizeof(GLfloat);
			case GL_FLOAT_MAT2x4: return 2 * 4 * sizeof(GLfloat);
			case GL_FLOAT_MAT3x2: return 3 * 2 * sizeof(GLfloat);
			case GL_FLOAT_MAT3x4: return 3 * 4 * sizeof(GLfloat);
			case GL_FLOAT_MAT4x2: return 4 * 2 * sizeof(GLfloat);
			case GL_FLOAT_MAT4x3: return 4 * 3 * sizeof(GLfloat);
			case GL_INT: return sizeof(GLint);
			case GL_INT_VEC2: return 2 * sizeof(GLint);
			case GL_INT_VEC3: return 3 * sizeof(GLint);
			case GL_INT_VEC4: return 4 * sizeof(GLint);
			case GL_UNSIGNED_INT: return sizeof(GLuint);
			case GL_UNSIGNED_INT_VEC2: return 2 * sizeof(GLuint);
			case GL_UNSIGNED_INT_VEC3: return 3 * sizeof(GLuint);
			case GL_UNSIGNED_INT_VEC4: return 4 * sizeof(GLuint);
			case GL_DOUBLE: return sizeof(GLdouble);
			case GL_DOUBLE_VEC2: return 2 * sizeof(GLdouble);
			case GL_DOUBLE_VEC3: return 3 * sizeof(GLdouble);
			case GL_DOUBLE_VEC4: return 4 * sizeof(GLdouble);
			case GL_DOUBLE_MAT2: return 2 * 2 * sizeof(GLdouble);
			case GL_DOUBLE_MAT3: return 3 * 3 * sizeof(GLdouble);
			case GL_DOUBLE_MAT4: return 4 * 4 * sizeof(GLdouble);
			case GL_DOUBLE_MAT2x3: return 2 * 3 * sizeof(GLdouble);
			case GL_DOUBLE_MAT2x4: return 2 * 4 * sizeof(GLdouble);
			case GL_DOUBLE_MAT3x2: return 3 * 2 * sizeof(GLdouble);
			case GL_DOUBLE_MAT3x4: return 3 * 4 * sizeof(GLdouble);
			case GL_DOUBLE_MAT4x2: return 4 * 2 * sizeof(GLdouble);
			case GL_DOUBLE_MAT4x3: return 4 * 3 * sizeof(GLdouble);
		}

		return 4;
	}

	auto ToNative(GLenum type) -> GLenum
	{
		switch (type)
		{
			case GL_FLOAT: return GL_FLOAT;
			case GL_FLOAT_VEC2: return GL_FLOAT;
			case GL_FLOAT_VEC3: return GL_FLOAT;
			case GL_FLOAT_VEC4: return GL_FLOAT;
			case GL_FLOAT_MAT2: return GL_FLOAT;
			case GL_FLOAT_MAT3: return GL_FLOAT;
			case GL_FLOAT_MAT4: return GL_FLOAT;
			case GL_FLOAT_MAT2x3: return GL_FLOAT;
			case GL_FLOAT_MAT2x4: return GL_FLOAT;
			case GL_FLOAT_MAT3x2: return GL_FLOAT;
			case GL_FLOAT_MAT3x4: return GL_FLOAT;
			case GL_FLOAT_MAT4x2: return GL_FLOAT;
			case GL_FLOAT_MAT4x3: return GL_FLOAT;
			case GL_INT: return GL_INT;
			case GL_INT_VEC2: return GL_INT;
			case GL_INT_VEC3: return GL_INT;
			case GL_INT_VEC4: return GL_INT;
			case GL_UNSIGNED_INT: return GL_UNSIGNED_INT;
			case GL_UNSIGNED_INT_VEC2: GL_UNSIGNED_INT;
			case GL_UNSIGNED_INT_VEC3: GL_UNSIGNED_INT;
			case GL_UNSIGNED_INT_VEC4: GL_UNSIGNED_INT;
			case GL_DOUBLE: return GL_DOUBLE;
			case GL_DOUBLE_VEC2: return GL_DOUBLE;
			case GL_DOUBLE_VEC3: return GL_DOUBLE;
			case GL_DOUBLE_VEC4: return GL_DOUBLE;
			case GL_DOUBLE_MAT2: return GL_DOUBLE;
			case GL_DOUBLE_MAT3: return GL_DOUBLE;
			case GL_DOUBLE_MAT4: return GL_DOUBLE;
			case GL_DOUBLE_MAT2x3: return GL_DOUBLE;
			case GL_DOUBLE_MAT2x4: return GL_DOUBLE;
			case GL_DOUBLE_MAT3x2: return GL_DOUBLE;
			case GL_DOUBLE_MAT3x4: return GL_DOUBLE;
			case GL_DOUBLE_MAT4x2: return GL_DOUBLE;
			case GL_DOUBLE_MAT4x3: return GL_DOUBLE;
		}

		return GL_FLOAT;
	}

	auto EnumCount(GLenum type) -> GLuint
	{
		switch (type)
		{
			case GL_FLOAT: return 1u;
			case GL_FLOAT_VEC2: return 2u;
			case GL_FLOAT_VEC3: return 3u;
			case GL_FLOAT_VEC4: return 4u;
			case GL_FLOAT_MAT2: return 2u * 2u;
			case GL_FLOAT_MAT3: return 3u * 3u;
			case GL_FLOAT_MAT4: return 4u * 4u;
			case GL_FLOAT_MAT2x3: return 2u * 3u;
			case GL_FLOAT_MAT2x4: return 2u * 4u;
			case GL_FLOAT_MAT3x2: return 3u * 2u;
			case GL_FLOAT_MAT3x4: return 3u * 4u;
			case GL_FLOAT_MAT4x2: return 4u * 2u;
			case GL_FLOAT_MAT4x3: return 4u * 3u;
			case GL_INT: return 1u;
			case GL_INT_VEC2: return 2u;
			case GL_INT_VEC3: return 3u;
			case GL_INT_VEC4: return 4u;
			case GL_UNSIGNED_INT: return 1u;
			case GL_UNSIGNED_INT_VEC2: 2u;
			case GL_UNSIGNED_INT_VEC3: 3u;
			case GL_UNSIGNED_INT_VEC4: 4u;
			case GL_DOUBLE: return 1u;
			case GL_DOUBLE_VEC2: return 2u;
			case GL_DOUBLE_VEC3: return 3u;
			case GL_DOUBLE_VEC4: return 4u;
			case GL_DOUBLE_MAT2: return 2u * 2u;
			case GL_DOUBLE_MAT3: return 3u * 3u;
			case GL_DOUBLE_MAT4: return 4u * 4u;
			case GL_DOUBLE_MAT2x3: return 2u * 3u;
			case GL_DOUBLE_MAT2x4: return 2u * 4u;
			case GL_DOUBLE_MAT3x2: return 3u * 2u;
			case GL_DOUBLE_MAT3x4: return 3u * 4u;
			case GL_DOUBLE_MAT4x2: return 4u * 2u;
			case GL_DOUBLE_MAT4x3: return 4u * 3u;
		}

		return 1u;
	}


}
