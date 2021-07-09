// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Vector.hpp"

# include <cmath>
# include <algorithm>

Vector2::Vector2(const Vector3& vec) : x(vec.x), y(vec.y) {}
Vector2::Vector2(const Vector4& vec) : x(vec.x), y(vec.y) {}

auto Vector2::operator+=(Vector2 a) -> Vector2&
{
    x += a.x;
    y += a.y;
    return *this;
}

auto Vector2::operator-=(Vector2 a) -> Vector2&
{
    x -= a.x;
    y -= a.y;
    return *this;
}

auto Vector2::operator+=(float a) -> Vector2&
{
    x += a;
    y += a;
    return *this;
}

auto Vector2::operator-=(float a) -> Vector2&
{
    x -= a;
    y -= a;
    return *this;
}

auto Vector2::operator*=(float a) -> Vector2&
{
    x *= a;
    y *= a;
    return *this;
}

auto Vector2::operator/=(float a) -> Vector2&
{
    x /= a;
    y /= a;
    return *this;
}

auto Vector2::operator-() const -> Vector2
{
    return {-x, -y};
}

auto Vector2::SqrMagnitude() const -> float
{
    return x * x + y * y; 
}

auto Vector2::Magnitude() const -> float
{
    return std::sqrt(x * x + y * y); 
}

auto Vector2::Normalize() -> Vector2&
{
    const float mag = Magnitude();

    if (mag != 0.0f)
    {
        *this /= mag;        
    }

    return *this;
}

auto Vector2::Normalized() const -> Vector2
{
    const float mag = Magnitude();

    if (mag != 0.0f)
    {
        return *this / mag;        
    }

    return {};
}

auto operator+(Vector2 a, Vector2 b) -> Vector2
{
    return {a.x + b.x, a.y + b.y};
}

auto operator-(Vector2 a, Vector2 b) -> Vector2
{
    return {a.x - b.x, a.y - b.y};
}

auto operator*(Vector2 a, float b) -> Vector2
{
    return {a.x * b, a.y * b};
}

auto operator*(float a, Vector2 b) -> Vector2
{
    return b * a;
}

auto operator/(Vector2 a, float b) -> Vector2
{
    return {a.x / b, a.y / b};
}

auto operator==(Vector2 a, Vector2 b) -> bool
{
    return a.x == b.x && a.y == b.y;
}

auto operator!=(Vector2 a, Vector2 b) -> bool
{
    return a.x != b.x || a.y != b.y;
}

Vector3::Vector3(const Vector2& vec) : x(vec.x), y(vec.y), z(0.0f) {}
Vector3::Vector3(const Vector4& vec) : x(vec.x), y(vec.y), z(vec.z) {}
Vector3::Vector3(const Vector2& vec, float z) : x(vec.x), y(vec.y), z(z) {}

auto Vector3::operator+=(Vector3 a) -> Vector3&
{
    x += a.x;
    y += a.y;
	z += a.z;
    return *this;
}

auto Vector3::operator-=(Vector3 a) -> Vector3&
{
    x -= a.x;
    y -= a.y;
	z -= a.z;
    return *this;
}

auto Vector3::operator+=(float a) -> Vector3&
{
    x += a;
    y += a;
    z += a;
    return *this;
}

auto Vector3::operator-=(float a) -> Vector3&
{
    x -= a;
    y -= a;
    z -= a;
    return *this;
}

auto Vector3::operator*=(float a) -> Vector3&
{
    x *= a;
    y *= a;
	z *= a;
    return *this;
}

auto Vector3::operator/=(float a) -> Vector3&
{
    x /= a;
    y /= a;
	z /= a;
    return *this;
}

auto Vector3::operator-() const -> Vector3
{
    return {-x, -y, -z};
}

auto Vector3::Dot(Vector3 a) const -> float
{
    return x * a.x + y * a.y + z * a.z;
}

auto Vector3::ClampMagnitude(float max) -> Vector3
{
    if (SqrMagnitude() > max * max)
    {
        return Normalized() * max;
    }
    
    return *this;
}

auto Vector3::Cross(Vector3 a) const -> Vector3
{
    return { y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x }; 
}

auto Vector3::SqrMagnitude() const -> float
{
    return x * x + y * y + z * z; 
}

auto Vector3::Magnitude() const -> float
{
    return std::sqrt(x * x + y * y + z * z); 
}

auto Vector3::Normalize() -> Vector3&
{
    const float mag = Magnitude();

    if (mag != 0.0f)
    {
        *this /= mag;        
    }

    return *this;
}

auto Vector3::Normalized() const -> Vector3
{
    const float mag = Magnitude();

    if (mag != 0.0f)
    {
        return *this / mag;        
    }

    return {};
}

auto Vector3::Clamp(Vector3 lowerBounds, Vector3 higherBounds) -> Vector3&
{
    this->x = std::clamp(this->x, lowerBounds.x, higherBounds.x);
    this->y = std::clamp(this->y, lowerBounds.y, higherBounds.y);
    this->z = std::clamp(this->z, lowerBounds.z, higherBounds.z);

    return *this;
}

auto operator+(Vector3 a, Vector3 b) -> Vector3
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

auto operator-(Vector3 a, Vector3 b) -> Vector3
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

auto operator*(Vector3 a, float b) -> Vector3
{
    return {a.x * b, a.y * b, a.z * b};
}

auto operator*(float a, Vector3 b) -> Vector3
{
    return b * a;
}

auto operator/(Vector3 a, float b) -> Vector3
{
    return {a.x / b, a.y / b, a.z / b};
}

auto operator==(Vector3 a, Vector3 b) -> bool
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

auto operator!=(Vector3 a, Vector3 b) -> bool
{
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

auto Vector4::operator+=(Vector4 a) -> Vector4&
{
    x += a.x;
    y += a.y;
	z += a.z;
    w += a.w;
    return *this;
}

auto Vector4::operator-=(Vector4 a) -> Vector4&
{
    x -= a.x;
    y -= a.y;
	z -= a.z;
    w -= a.w;
    return *this;
}

auto Vector4::operator+=(float a) -> Vector4&
{
    x += a;
    y += a;
    z += a;
    w += a;
    return *this;
}

auto Vector4::operator-=(float a) -> Vector4&
{
    x -= a;
    y -= a;
    z -= a;
    w -= a;
    return *this;
}

auto Vector4::operator*=(float a) -> Vector4&
{
    x *= a;
    y *= a;
	z *= a;
    w *= a;
    return *this;
}

auto Vector4::operator/=(float a) -> Vector4&
{
    x /= a;
    y /= a;
	z /= a;
    w /= a;
    return *this;
}

Vector4::Vector4(Vector3 vec) : x(vec.x), y(vec.y), z(vec.z), w(0.0f) {}
Vector4::Vector4(Vector2 vec) : x(vec.x), y(vec.y), z(0.0f), w(0.0f) {}
Vector4::Vector4(Vector3 vec, float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}
Vector4::Vector4(Vector2 vec, float z, float w) : x(vec.x), y(vec.y), z(z), w(w) {}

auto Vector4::operator-() const -> Vector4
{
    return {-x, -y, -z, -w};
}

auto Vector4::SqrMagnitude() const -> float
{
    return x * x + y * y + z * z + w * w; 
}

auto Vector4::Magnitude() const -> float
{
    return std::sqrt(x * x + y * y + z * z + w * w); 
}

auto Vector4::Normalize() -> Vector4&
{
    const float mag = Magnitude();

    if (mag != 0.0f)
    {
        *this /= mag;        
    }

    return *this;
}

auto Vector4::Normalized() const -> Vector4
{
    const float mag = Magnitude();

    if (mag != 0.0f)
    {
        return *this / mag;        
    }

    return {};
}

auto operator+(Vector4 a, Vector4 b) -> Vector4
{
    return {a.x + b.x, a.y + b.y, a.z + b.z, a.w - b.w };
}

auto operator-(Vector4 a, Vector4 b) -> Vector4
{
    return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

auto operator*(Vector4 a, float b) -> Vector4
{
    return {a.x * b, a.y * b, a.z * b, a.w * b};
}

auto operator*(float a, Vector4 b) -> Vector4
{
    return b * a;
}

auto operator/(Vector4 a, float b) -> Vector4
{
    return {a.x / b, a.y / b, a.z / b, a.w / b };
}

auto operator==(Vector4 a, Vector4 b) -> bool
{
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

auto operator!=(Vector4 a, Vector4 b) -> bool
{
    return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
}
