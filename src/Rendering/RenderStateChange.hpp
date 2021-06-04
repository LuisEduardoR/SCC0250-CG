// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains a class to store data necessary for the 
    state changes that happen when rendering
*/

# ifndef RENDER_STATE_CHANGE_HPP
# define RENDER_STATE_CHANGE_HPP

# include "Color.hpp"
# include "../Math/Vector.hpp"

# include <GL/glew.h>
# include <cstdint>


class RenderStateChange
{

public:

    // Constructors
    RenderStateChange() {
        this->index = 0;
        this->vertexCount = 0;
        this->color = Color::white;
        this->drawMode = 0;
    }

    RenderStateChange(uint64_t index, uint64_t vertexCount, const Color& color, GLuint drawMode) {
        this->index = index;
        this->vertexCount = vertexCount;
        this->color = color;
        this->drawMode = drawMode;
    }

    // Initial index
    uint64_t index;

    // Number of vertices on the array
    uint64_t vertexCount;

    // Color to be used on rendering
    Color color;

    // Draw mode to be used on rendering
    GLuint drawMode;

};

# endif /* end of include guard: RENDER_STATE_CHANGE_HPP */