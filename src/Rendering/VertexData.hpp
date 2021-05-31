// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains a struct to store data about the vertices to be rendered
*/

# ifndef VERTEX_DATA_HPP
# define VERTEX_DATA_HPP

# include <cstdint>

# include "../Math/Vector.hpp"

struct VertexData
{
    // Pointer to an array of vertices, can be either Vector2s or Vector3s
    union {
        const Vector2 *vertices2D;
        const Vector3 *vertices3D;
    };
    // Number of vertices on the array
    uint32_t vertexCount;
};

# endif /* end of include guard: VERTEX_DATA_HPP */