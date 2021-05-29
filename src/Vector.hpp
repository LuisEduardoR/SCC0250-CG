# ifndef VECTOR_HPP
# define VECTOR_HPP

// Represents a 2D vector, but can also be used to represent 2D coordinates 
class Vector2 {

public:

    float x, y;

    Vector2(float x, float y) { this->x = x; this->y = y; }
    Vector2() : Vector2(0.0f, 0.0f) {}

};

// Represents a 3D vector, but can also be used to represent 3D coordinates 
class Vector3{

public:

    float x, y, z;

    Vector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
    Vector3() : Vector3(0.0f, 0.0f, 0.0f) {}

};

// Represents a 4D vector, but can also be used to represent 4D coordinates 
class Vector4{

public:

    float x, y, z, w;

    Vector4(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z, this->w = w; }
    Vector4() : Vector4(0.0f, 0.0f, 0.0f, 0.0f) {}

};

# endif