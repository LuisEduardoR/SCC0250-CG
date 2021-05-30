# ifndef MATRIX_HPP
# define MATRIX_HPP

# include "Vector.hpp"

// Represents a 4D transformation matrix
class Matrix4 {

public:

    Vector4 i, j, k, l;   

    // Constructors
    Matrix4(Vector4 i, Vector4 j, Vector4 k, Vector4 l);
    Matrix4() : Matrix4 (
                            { 1.0f, 0.0f, 0.0f, 0.0f }, 
                            { 0.0f, 1.0f, 0.0f, 0.0f }, 
                            { 0.0f, 0.0f, 1.0f, 0.0f }, 
                            { 0.0f, 0.0f, 0.0f, 1.0f }
                        ) {}

    [[nodiscard]] auto MultiplyPoint(const Vector2& point) -> Vector2;

    // Operators
    Matrix4 operator*(const Matrix4& m);
};

[[nodiscard]] auto operator*(const Matrix4& a, Vector4 b) -> Vector4;

# endif
