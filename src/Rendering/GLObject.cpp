#include "GLObject.hpp"

GLObject::GLObject(GLObject&& other) noexcept
{
	self = other.self;
	other.self = 0;
}

auto GLObject::operator=(GLObject&& other) noexcept -> GLObject&
{
	self = other.self;
	other.self = 0;
	return *this;
}

auto GLObject::Name() -> GLuint
{
	return self;
}
