// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Matrix4x4.hpp"
# include "Vector.hpp"

# include <cmath>


/* namespace amn */
/* { */

auto Matrix4x4::Camera(Vector3 cameraPos, Vector3 rotation, Vector3 viewFront, Vector3 viewUp) -> Matrix4x4
{
	Vector4 dir = (Matrix4x4::Rotate(rotation) * Vector4{ viewFront, 1.0f }).Normalize();
	Vector3 cameraZ{ dir.x, dir.y, dir.z };
	Vector4 viewUp4 = (Matrix4x4::Rotate(rotation) * Vector4{ viewUp, 1.0f }).Normalize();
	Vector3 cameraX = Vector3{ viewUp4.x, viewUp4.y, viewUp4.z }.Cross(cameraZ).Normalized(); // u
	Vector3 cameraY = cameraZ.Cross(cameraX).Normalize(); // v

	return Matrix4x4{
		{ cameraX.x, cameraY.x, cameraZ.x, 0 },
		{ cameraX.y, cameraY.y, cameraZ.y, 0 },
		{ cameraX.z, cameraY.z, cameraZ.z, 0 },
		{ -cameraX.Dot(cameraPos), -cameraY.Dot(cameraPos), -cameraZ.Dot(cameraPos), 1 }
	};
}

auto Matrix4x4::LookAt(Vector3 cameraPos, Vector3 targetPos, Vector3 viewUp) -> Matrix4x4
{
	Vector3 cameraZ = cameraPos - targetPos;
	Vector3 cameraX = viewUp.Cross(cameraZ).Normalized(); // u
	Vector3 cameraY = cameraZ.Cross(cameraX); // v

	return Matrix4x4{
		{ cameraX.x, cameraY.x, cameraZ.x, 0 },
		{ cameraX.y, cameraY.y, cameraZ.y, 0 },
		{ cameraX.z, cameraY.z, cameraZ.z, 0 },
		{ -cameraX.Dot(cameraPos), -cameraY.Dot(cameraPos), -cameraZ.Dot(cameraPos), 1 }
	};
}

auto Matrix4x4::Perspective(float fov, float aspect, float zNear, float zFar) -> Matrix4x4
{
	return Matrix4x4{
		{ 1.0f / std::tan(fov * 0.5f) * aspect, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f / std::tan(fov * 0.5f), 0.0f, 0.0f },
		{ 0.0f, 0.0f, zNear - zFar / zFar - zNear, -1.0f },
		{ 0.0f, 0.0f, 2.0f * zFar * zNear / zNear - zFar, 0.0f }, 
	};
}

auto Matrix4x4::Rotate(float rotationAngle) -> Matrix4x4
{
	return Matrix4x4{ { std::cos(rotationAngle), std::sin(rotationAngle), 0.0f, 0.0f },
					  { -std::sin(rotationAngle), std::cos(rotationAngle), 0.0f, 0.0f },
					  { 0.0f, 0.0f, 1.0f, 0.0f },
					  { 0.0f, 0.0f, 0.0f, 1.0f } };
}

auto Matrix4x4::Rotate(Vector3 rotationAngle) -> Matrix4x4
{
	return Matrix4x4{ { 1.0f, 0.0f, 0.0f, 0.0f },
					  { 0.0f, std::cos(rotationAngle.x), std::sin(rotationAngle.x), 0.0f },
					  { 0.0f, -std::sin(rotationAngle.x), std::cos(rotationAngle.x), 0.0f },
					  { 0.0f, 0.0f, 0.0f, 1.0f } }
		   * Matrix4x4{ { std::cos(rotationAngle.y), 0.0f, -std::sin(rotationAngle.y), 0.0f },
						{ 0.0f, 1.0f, 0.0f, 0.0f },
						{ std::sin(rotationAngle.y), 0.0f, std::cos(rotationAngle.y), 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } }
		   * Matrix4x4{ { std::cos(rotationAngle.z), std::sin(rotationAngle.z), 0.0f, 0.0f },
						{ -std::sin(rotationAngle.z), std::cos(rotationAngle.z), 0.0f, 0.0f },
						{ 0.0f, 0.0f, 1.0f, 0.0f },
						{ 0.0f, 0.0f, 0.0f, 1.0f } };
}

auto Matrix4x4::Scale(Vector2 scaleFactor) -> Matrix4x4
{
	return Matrix4x4{ { scaleFactor.x, 0.0f, 0.0f, 0.0f },
					  { 0.0f, scaleFactor.y, 0.0f, 0.0f },
					  { 0.0f, 0.0f, 1.0f, 0.0f },
					  { 0.0f, 0.0f, 0.0f, 1.0f } };
}

auto Matrix4x4::Scale(Vector3 scaleFactor) -> Matrix4x4
{
	return Matrix4x4{ { scaleFactor.x, 0.0f, 0.0f, 0.0f },
					  { 0.0f, scaleFactor.y, 0.0f, 0.0f },
					  { 0.0f, 0.0f, scaleFactor.z, 0.0f },
					  { 0.0f, 0.0f, 0.0f, 1.0f } };
}

auto Matrix4x4::Translate(Vector2 translation) -> Matrix4x4
{
	return Matrix4x4{ { 1.0f, 0.0f, 0.0f, 0.0f },
					  { 0.0f, 1.0f, 0.0f, 0.0f },
					  { 0.0f, 0.0f, 1.0f, 0.0f },
					  { translation.x, translation.y, 0.0f, 1.0f } };
}

auto Matrix4x4::Translate(Vector3 translation) -> Matrix4x4
{
	return Matrix4x4{ { 1.0f, 0.0f, 0.0f, 0.0f },
					  { 0.0f, 1.0f, 0.0f, 0.0f },
					  { 0.0f, 0.0f, 1.0f, 0.0f },
					  { translation.x, translation.y, translation.z, 1.0f } };
}


auto Matrix4x4::TRS(Vector2 translation, float rotationAngle, Vector2 scaleFactor) -> Matrix4x4
{
	return Matrix4x4::Translate(translation) * Matrix4x4::Rotate(rotationAngle) * Matrix4x4::Scale(scaleFactor);
}

auto Matrix4x4::TRS(Vector3 translation, Vector3 rotationAngle, Vector3 scaleFactor) -> Matrix4x4
{
	return Matrix4x4::Translate(translation) * Matrix4x4::Rotate(rotationAngle) * Matrix4x4::Scale(scaleFactor);
}

auto Matrix4x4::DataFlat() const -> const std::array<float, 16>&
{
	return flat;
}

auto Matrix4x4::operator[](std::array<std::size_t, 2> xy_index) const -> float
{
	return matrix[xy_index[0]][xy_index[1]];
}

auto Matrix4x4::operator[](std::array<std::size_t, 2> xy_index) -> float&
{
	return matrix[xy_index[0]][xy_index[1]];
}

auto Matrix4x4::operator+=(Matrix4x4 a) -> Matrix4x4&
{
	for (std::size_t i = 0; i < 16; i++)
	{
		flat[i] += a.flat[i];
	}
	return *this;
}

auto Matrix4x4::operator-=(Matrix4x4 a) -> Matrix4x4&
{
	for (std::size_t i = 0; i < 16; i++)
	{
		flat[i] -= a.flat[i];
	}
	return *this;
}

auto Matrix4x4::operator*=(float a) -> Matrix4x4&
{
	for (std::size_t i = 0; i < 16; i++)
	{
		flat[i] *= a;
	}
	return *this;
}

auto Matrix4x4::operator/=(float a) -> Matrix4x4&
{
	for (std::size_t i = 0; i < 16; i++)
	{
		flat[i] /= a;
	}
	return *this;
}

auto Matrix4x4::operator-() const -> Matrix4x4
{
	Matrix4x4 out{ {} };
	for (std::size_t i = 0; i < 16; i++)
	{
		out.flat[i] = -flat[i];
	}
	return out;
}

auto operator+(const Matrix4x4& a, const Matrix4x4& b) -> Matrix4x4
{
	Matrix4x4 out{ {} };
	for (std::size_t i = 0; i < 16; i++)
	{
		out.flat[i] = a.flat[i] + b.flat[i];
	}
	return out;
}

auto operator-(const Matrix4x4& a, const Matrix4x4& b) -> Matrix4x4
{
	Matrix4x4 out{ {} };
	for (std::size_t i = 0; i < 16; i++)
	{
		out.flat[i] = a.flat[i] - b.flat[i];
	}
	return out;
}

auto operator*(const Matrix4x4& a, const Matrix4x4& b) -> Matrix4x4
{
	Matrix4x4 out{ {} };
	for (std::size_t x = 0; x < 4; x++)
	{
		for (std::size_t y = 0; y < 4; y++)
		{
			out.matrix[x][y] =
				a.matrix[0][y] * b.matrix[x][0] + a.matrix[1][y] * b.matrix[x][1]
				+ a.matrix[2][y] * b.matrix[x][2] + a.matrix[3][y] * b.matrix[x][3];
		}
	}
	return out;
}

auto operator*(const Matrix4x4& a, const Vector4& b) -> Vector4
{
	return Vector4{
		a.matrix[0][0] * b.x + a.matrix[1][0] * b.y + a.matrix[2][0] * b.z + a.matrix[3][0] * b.w,
		a.matrix[0][1] * b.x + a.matrix[1][1] * b.y + a.matrix[2][1] * b.z + a.matrix[3][1] * b.w,
		a.matrix[0][2] * b.x + a.matrix[1][2] * b.y + a.matrix[2][2] * b.z + a.matrix[3][2] * b.w,
		a.matrix[0][3] * b.x + a.matrix[1][3] * b.y + a.matrix[2][3] * b.z + a.matrix[3][3] * b.w,
	};
}

auto operator*(const Matrix4x4& a, float b) -> Matrix4x4
{
	Matrix4x4 out{ {} };
	for (std::size_t i = 0; i < 16; i++)
	{
		out.flat[i] = a.flat[i] * b;
	}
	return out;
}

auto operator*(float a, const Matrix4x4& b) -> Matrix4x4
{
	Matrix4x4 out{ {} };
	for (std::size_t i = 0; i < 16; i++)
	{
		out.flat[i] = a * b.flat[i];
	}
	return out;
}

auto operator/(const Matrix4x4& a, float b) -> Matrix4x4
{
	Matrix4x4 out{ {} };
	for (std::size_t i = 0; i < 16; i++)
	{
		out.flat[i] = a.flat[i] / b;
	}
	return out;
}

auto operator==(const Matrix4x4& a, const Matrix4x4& b) -> bool
{
	for (std::size_t i = 0; i < 16; i++)
	{
		if (a.flat[i] != b.flat[i])
		{
			return false;
		}
	}
	return true;
}

auto operator!=(const Matrix4x4& a, const Matrix4x4& b) -> bool
{
	for (std::size_t i = 0; i < 16; i++)
	{
		if (a.flat[i] != b.flat[i])
		{
			return true;
		}
	}
	return false;
}

/* } // namespace amn */
