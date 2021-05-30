#ifndef AMN_MATRIX4X4_HPP
#define AMN_MATRIX4X4_HPP

#include <array>
#include <cstdint>

/* namespace amn */
/* { */

struct Vector2;
struct Vector3;
struct Vector4;

union Matrix4x4
{
	// Static functions.
public:
	static const Matrix4x4 Identity;
	static const Matrix4x4 Zero;

	[[nodiscard]] static auto Camera(Vector3 cameraPos, Vector3 rotation, Vector3 viewFront, Vector3 viewUp) -> Matrix4x4;

	[[nodiscard]] static auto LookAt(Vector3 cameraPos, Vector3 targetPos, Vector3 viewUp) -> Matrix4x4;

	[[nodiscard]] static auto Perspective(float fov, float aspect, float zNear, float zFar) -> Matrix4x4;

	[[nodiscard]] static auto Rotate(float rotationAngle) -> Matrix4x4;

	[[nodiscard]] static auto Rotate(Vector3 rotationAngle) -> Matrix4x4;

	[[nodiscard]] static auto Scale(Vector2 scaleFactor) -> Matrix4x4;

	[[nodiscard]] static auto Scale(Vector3 scaleFactor) -> Matrix4x4;

	[[nodiscard]] static auto Translate(Vector2 translation) -> Matrix4x4;

	[[nodiscard]] static auto Translate(Vector3 translation) -> Matrix4x4;

	[[nodiscard]] static auto TRS(Vector2 translation, float rotationAngle, Vector2 scaleFactor) -> Matrix4x4;

	[[nodiscard]] static auto TRS(Vector3 translation, Vector3 rotationAngle, Vector3 scaleFactor) -> Matrix4x4;
	// Public constructors
public:
	[[nodiscard]] constexpr explicit Matrix4x4(float fill) noexcept : flat({ fill }) {}

	[[nodiscard]] constexpr explicit Matrix4x4(std::array<float, 16> flat) noexcept : flat(flat) {}

	[[nodiscard]] constexpr Matrix4x4(
		std::array<float, 4>&& col0, std::array<float, 4>&& col1, std::array<float, 4>&& col2,
		std::array<float, 4>&& col3) noexcept :
		matrix({ col0, col1, col2, col3 })
	{
	}

	[[nodiscard]] Matrix4x4(const Matrix4x4& other) noexcept = default;

	[[nodiscard]] Matrix4x4(Matrix4x4&& other) noexcept = default;

	auto operator=(const Matrix4x4& other) noexcept -> Matrix4x4& = default;

	auto operator=(Matrix4x4&& other) noexcept -> Matrix4x4& = default;

public:
	[[nodiscard]] auto operator[](std::array<std::size_t, 2> xy_index) const -> float;

	[[nodiscard]] auto operator[](std::array<std::size_t, 2> xy_index) -> float&;

	auto operator+=(Matrix4x4 a) -> Matrix4x4&;
	auto operator-=(Matrix4x4 a) -> Matrix4x4&;
	auto operator*=(float a) -> Matrix4x4&;
	auto operator/=(float a) -> Matrix4x4&;
	[[nodiscard]] auto operator-() const -> Matrix4x4;

	friend auto operator+(const Matrix4x4& a, const Matrix4x4& b) -> Matrix4x4;
	friend auto operator-(const Matrix4x4& a, const Matrix4x4& b) -> Matrix4x4;
	friend auto operator*(const Matrix4x4& a, const Matrix4x4& b) -> Matrix4x4;
	friend auto operator*(const Matrix4x4& a, const Vector4& b) -> Vector4;
	friend auto operator*(const Matrix4x4& a, float b) -> Matrix4x4;
	friend auto operator*(float a, const Matrix4x4& b) -> Matrix4x4;
	friend auto operator/(const Matrix4x4& a, float b) -> Matrix4x4;
	friend auto operator==(const Matrix4x4& a, const Matrix4x4& b) -> bool;
	friend auto operator!=(const Matrix4x4& a, const Matrix4x4& b) -> bool;
	// Union fields.
private:
	// Matrix is stored column major.
	// Indexes 0-3 are the first column and so on.
	std::array<float, 16> flat;
	std::array<std::array<float, 4>, 4> matrix;
};

static_assert(sizeof(Matrix4x4) == sizeof(float) * 16, "Matrix4x4 must have correct size");

constexpr Matrix4x4 Matrix4x4::Identity{ { 1.0f, 0.0f, 0.0f, 0.0f },
										 { 0.0f, 1.0f, 0.0f, 0.0f },
										 { 0.0f, 0.0f, 1.0f, 0.0f },
										 { 0.0f, 0.0f, 0.0f, 1.0f } };

constexpr Matrix4x4 Matrix4x4::Zero{ 0.0f };

/* } // namespace amn */

#endif /* end of include guard: AMN_MATRIX_HPP */
