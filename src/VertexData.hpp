// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

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