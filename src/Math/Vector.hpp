// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the mathematical representation of vertices
*/

# ifndef VECTOR_HPP
# define VECTOR_HPP

class Vector3;
class Vector4;

// Represents a 2D vector, but can also be used to represent 2D coordinates 
class Vector2 {

public:

    float x, y;

    Vector2(float x, float y) { this->x = x; this->y = y; }
    Vector2() : Vector2(0.0f, 0.0f) {}
	explicit Vector2(const Vector3& vec);
	explicit Vector2(const Vector4& vec);

    Vector2(const Vector2& other) = default;
	Vector2(Vector2&& other) = default;

	auto operator=(const Vector2& other) -> Vector2& = default;
	auto operator=(Vector2&& other) -> Vector2& = default;

    auto operator+=(Vector2 a) -> Vector2&;
	auto operator-=(Vector2 a) -> Vector2&;
	auto operator+=(float a) -> Vector2&;
	auto operator-=(float a) -> Vector2&;
	auto operator*=(float a) -> Vector2&;
	auto operator/=(float a) -> Vector2&;
	[[nodiscard]] auto operator-() const -> Vector2;

	[[nodiscard]] auto SqrMagnitude() const -> float;
	[[nodiscard]] auto Magnitude() const -> float;
	auto Normalize() -> Vector2&;
	[[nodiscard]] auto Normalized() const -> Vector2;
};

[[nodiscard]] auto operator+(Vector2 a, Vector2 b) -> Vector2;
[[nodiscard]] auto operator-(Vector2 a, Vector2 b) -> Vector2;
[[nodiscard]] auto operator*(Vector2 a, float b) -> Vector2;
[[nodiscard]] auto operator*(float a, Vector2 b) -> Vector2;
[[nodiscard]] auto operator/(Vector2 a, float b) -> Vector2;
[[nodiscard]] auto operator==(Vector2 a, Vector2 b) -> bool;
[[nodiscard]] auto operator!=(Vector2 a, Vector2 b) -> bool;


// Represents a 3D vector, but can also be used to represent 3D coordinates 
class Vector3{

public:

    float x, y, z;

    Vector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
    Vector3() : Vector3(0.0f, 0.0f, 0.0f) {}
	explicit Vector3(const Vector2& vec);
	explicit Vector3(const Vector4& vec);

    Vector3(const Vector3& other) = default;
	Vector3(Vector3&& other) = default;

	auto operator=(const Vector3& other) -> Vector3& = default;
	auto operator=(Vector3&& other) -> Vector3& = default;

	auto operator+=(Vector3 a) -> Vector3&;
	auto operator-=(Vector3 a) -> Vector3&;
	auto operator+=(float a) -> Vector3&;
	auto operator-=(float a) -> Vector3&;
	auto operator*=(float a) -> Vector3&;
	auto operator/=(float a) -> Vector3&;
	[[nodiscard]] auto operator-() const -> Vector3;

	[[nodiscard]] auto Dot(Vector3 a) const -> float;
	[[nodiscard]] auto Cross(Vector3 a) const -> Vector3;
	[[nodiscard]] auto SqrMagnitude() const -> float;
	[[nodiscard]] auto Magnitude() const -> float;
	auto Normalize() -> Vector3&;
	[[nodiscard]] auto Normalized() const -> Vector3;
};

[[nodiscard]] auto operator+(Vector3 a, Vector3 b) -> Vector3;
[[nodiscard]] auto operator-(Vector3 a, Vector3 b) -> Vector3;
[[nodiscard]] auto operator*(Vector3 a, float b) -> Vector3;
[[nodiscard]] auto operator*(float a, Vector3 b) -> Vector3;
[[nodiscard]] auto operator/(Vector3 a, float b) -> Vector3;
[[nodiscard]] auto operator==(Vector3 a, Vector3 b) -> bool;
[[nodiscard]] auto operator!=(Vector3 a, Vector3 b) -> bool;

// Represents a 4D vector, but can also be used to represent 4D coordinates 
class Vector4{

public:

    float x, y, z, w;

    Vector4(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z, this->w = w; }
    Vector4() : Vector4(0.0f, 0.0f, 0.0f, 0.0f) {}
	explicit Vector4(Vector2 vec);
	explicit Vector4(Vector3 vec);
	Vector4(Vector2 vec, float z, float w);
	Vector4(Vector3 vec, float w);

    Vector4(const Vector4& other) = default;
	Vector4(Vector4&& other) = default;

	auto operator=(const Vector4& other) -> Vector4& = default;
	auto operator=(Vector4&& other) -> Vector4& = default;

	auto operator+=(Vector4 a) -> Vector4&;
	auto operator-=(Vector4 a) -> Vector4&;
	auto operator+=(float a) -> Vector4&;
	auto operator-=(float a) -> Vector4&;
	auto operator*=(float a) -> Vector4&;
	auto operator/=(float a) -> Vector4&;
	[[nodiscard]] auto operator-() const -> Vector4;

	[[nodiscard]] auto SqrMagnitude() const -> float;
	[[nodiscard]] auto Magnitude() const -> float;
	auto Normalize() -> Vector4&;
	[[nodiscard]] auto Normalized() const -> Vector4;
};

[[nodiscard]] auto operator+(Vector4 a, Vector4 b) -> Vector4;
[[nodiscard]] auto operator-(Vector4 a, Vector4 b) -> Vector4;
[[nodiscard]] auto operator*(Vector4 a, float b) -> Vector4;
[[nodiscard]] auto operator*(float a, Vector4 b) -> Vector4;
[[nodiscard]] auto operator/(Vector4 a, float b) -> Vector4;
[[nodiscard]] auto operator==(Vector4 a, Vector4 b) -> bool;
[[nodiscard]] auto operator!=(Vector4 a, Vector4 b) -> bool;

# endif /* end of include guard: VECTOR_HPP */
