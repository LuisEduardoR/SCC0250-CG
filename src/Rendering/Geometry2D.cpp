// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Geometry2D.hpp"

// Point ======================================

// Returns the vertices used to represent this shape
const VertexData Point::GetVertices() const {
    VertexData data;
    data.vertices2D = &(this->a);
    data.vertexCount = 1;
    return data;
}

// Returns the draw mode of this shape
GLenum Point::GetDrawMode() const { return GL_POINTS; }

// Line =======================================

// Returns the vertices used to represent this shape
const VertexData Line::GetVertices() const {
    VertexData data;
    data.vertices2D = &(this->a);
    data.vertexCount = 2;
    return data;
}

// Returns the draw mode of this shape
GLenum Line::GetDrawMode() const { return GL_LINE_STRIP; }

// Polyline ===================================

// Returns the vertices used to represent this shape
const VertexData Polyline::GetVertices() const {
    VertexData data;
    data.vertices2D = this->vertices.data();
    data.vertexCount = this->vertices.size();
    return data;
}

// Returns the draw mode of this shape
GLenum Polyline::GetDrawMode() const { return GL_LINE_STRIP; }

// Triangle ===================================

// Returns the vertices used to represent this shape
const VertexData Triangle::GetVertices() const {
    VertexData data;
    data.vertices2D = &(this->a);
    data.vertexCount = 3;
    return data;
}

// Returns the draw mode of this shape
GLenum Triangle::GetDrawMode() const { return GL_TRIANGLE_STRIP; }

// Quad =======================================

// Returns the vertices used to represent this shape
const VertexData Quad::GetVertices() const {
    VertexData data;
    data.vertices2D = &(this->a);
    data.vertexCount = 4;
    return data;
}

// Returns the draw mode of this shape
GLenum Quad::GetDrawMode() const { return GL_TRIANGLE_STRIP; }

// Circle =======================================

// Returns the vertices used to represent this shape (an approximation of the Circle represented by a certain number of vertices)
const VertexData Circle::GetVertices() const {
    VertexData data;
    data.vertices2D = this->vertices.data();
    data.vertexCount = this->vertices.size();
    return data;
}

// Returns the draw mode of this shape
GLenum Circle::GetDrawMode() const { return GL_TRIANGLE_FAN; }