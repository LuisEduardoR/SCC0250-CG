#ifndef AMN_GL_OBJECT_HPP
#define AMN_GL_OBJECT_HPP

#include <GL/glew.h>

class GLObject
{
public:
	GLObject() = default;
	GLObject(const GLObject& other) = delete;
	GLObject(GLObject&& other) noexcept;

	auto operator=(const GLObject& other) -> GLObject& = delete;
	auto operator=(GLObject&& other) noexcept -> GLObject&;
public:
	[[nodiscard]] auto Name() -> GLuint;
protected:
	GLuint self;
};

#endif /* end of include guard: AMN_GL_OBJECT_HPP */
