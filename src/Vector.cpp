# include "Vector.hpp"

# include <cmath>

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
