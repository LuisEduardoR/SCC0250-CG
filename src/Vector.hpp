# ifndef VECTOR_HPP
# define VECTOR_HPP

// Represents a 2D vector, but can also be used to represent 2D coordinates 
class Vector2 {

public:

    float x, y;

    Vector2(float x, float y) { this->x = x; this->y = y; }
    Vector2() : Vector2(0.0f, 0.0f) {}

    Vector2(const Vector2& other) = default;
	Vector2(Vector2&& other) = default;

	auto operator=(const Vector2& other) -> Vector2& = default;
	auto operator=(Vector2&& other) -> Vector2& = default;

    auto operator+=(Vector2 a) -> Vector2&;
	auto operator-=(Vector2 a) -> Vector2&;
	auto operator*=(float a) -> Vector2&;
	auto operator/=(float a) -> Vector2&;
	[[nodiscard]] auto operator-() const -> Vector2;

	[[nodiscard]] auto SqrMagnitude() const -> float;
	[[nodiscard]] auto Magnitude() const -> float;
	[[nodiscard]] auto Normalize() -> Vector2&;
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

    Vector3(const Vector3& other) = default;
	Vector3(Vector3&& other) = default;

	auto operator=(const Vector3& other) -> Vector3& = default;
	auto operator=(Vector3&& other) -> Vector3& = default;

	auto operator+=(Vector3 a) -> Vector3&;
	auto operator-=(Vector3 a) -> Vector3&;
	auto operator*=(float a) -> Vector3&;
	auto operator/=(float a) -> Vector3&;
	[[nodiscard]] auto operator-() const -> Vector3;

	[[nodiscard]] auto SqrMagnitude() const -> float;
	[[nodiscard]] auto Magnitude() const -> float;
	[[nodiscard]] auto Normalize() -> Vector3&;
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

    Vector4(const Vector4& other) = default;
	Vector4(Vector4&& other) = default;

	auto operator=(const Vector4& other) -> Vector4& = default;
	auto operator=(Vector4&& other) -> Vector4& = default;
};

# endif
