# ifndef VERTEXDATA_HPP
# define VERTEXDATA_HPP

# include <cstdint>

# include "Vector.hpp"

struct VertexData
{
    union {
        const Vector2 *vertices2D;
        const Vector3 *vertices3D;
    };
    uint32_t vertexCount;
};

# endif