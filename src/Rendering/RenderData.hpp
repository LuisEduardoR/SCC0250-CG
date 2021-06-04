// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains a struct to store data necessary for rendering
*/

# ifndef RENDER_DATA_HPP
# define RENDER_DATA_HPP

# include "Color.hpp"
# include "../Math/Vector.hpp"

# include <GL/glew.h>
# include <cstdint>

class RenderData
{

public:

    // Constructors
    RenderData() {
        this->vertices = nullptr;
        this->vertexCount = 0;
        this->color = nullptr;
        this->drawMode = 0;
    }

    RenderData(const Vector2 *vertices, uint64_t vertexCount, const Color *color, GLuint drawMode) {
        this->vertices = vertices;
        this->vertexCount = vertexCount;
        this->color = color;
        this->drawMode = drawMode;
    }

    // Pointer to an array of vertices to be used on rendering
    const Vector2 *vertices;

    // Number of vertices on the array
    uint64_t vertexCount;

    // Pointer a Color to be used on rendering
    const Color *color;

    // Draw mode to be used on rendering
    GLuint drawMode;

    bool operator==(const RenderData& other)
    {
        return  this->vertices == other.vertices
                && this->vertexCount == other.vertexCount
                && this->color == other.color
                && this->drawMode == other.drawMode;
    }

    bool operator>(const RenderData& other)
    {
        // First sorts by drawMode
        if(this->drawMode != other.drawMode)
            return this->drawMode > other.drawMode;

        // Then by color
        if(this->color != other.color)
            return this->color > other.color;

        // By size
        if(this->vertexCount != other.vertexCount)
            return this->vertexCount > other.vertexCount;

        // Finally by the position in memory simply 
        // because we don't have other option
        return this->vertices > other.vertices;

    }

};

# endif /* end of include guard: RENDER_DATA_HPP */