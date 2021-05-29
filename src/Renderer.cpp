// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini
#include <iostream>
# include "Renderer.hpp"

// Constructor
Renderer::Renderer(bool enable3D) {

    this->currentProgram = 0;
    this->arrayBuffer = 0;

    // Initializes GLEW to handle OpenGL functions
    GLint result = glewInit();
    std::cout << "GlewStatus: " << glewGetErrorString(result) << std::endl;

    // Enables the depth buffer if using 3D
    if(enable3D) glEnable(GL_DEPTH_TEST);

}

// Destructor
Renderer::~Renderer() {
    glDeleteBuffers(1, &(this->arrayBuffer));
}

// Clears our color program with a certain color
void Renderer::Clear(const Color& c) {
    glClearColor(c.r, c.b, c.g, c.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Clears our color buffer with a default color
void Renderer::Clear() { Clear(Color::black); }

// Sets the program our renderer will use based on some shader code
void Renderer::SetProgram(std::string vertex_code, std::string fragment_code) {

    // Creates the program we are going to use from our vertex and fragment shader's source code
    this->currentProgram = CreateProgram(vertex_code, fragment_code);

    // Uses our program
    glUseProgram(this->currentProgram);

}

// Creates an array buffer (if one was already created re-uses it)
void Renderer::CreateArrayBuffer() {
    
    // If the buffer already exists return
    if(arrayBuffer > 0)
        return;

    // Creates our buffer
    GLuint buffer;
    glGenBuffers(1, &buffer);
    
    // Sets our buffer as the GL_ARRAY_BUFFER
    this->arrayBuffer = buffer;
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

}

// 2D =====================================

// Draws a basic 2D shape (uses the default transform matrix)
void Renderer::DrawBasic2D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color) { DrawBasic2D(data, data_size, count, mode, color, Matrix4()); }

// Draws a basic 2D shape
void Renderer::DrawBasic2D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color, const Matrix4& transform) {

    // Creates our array buffer
    CreateArrayBuffer();

    // Sends our data to the array buffer
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_DYNAMIC_DRAW);

    // Breaks our transform matrix into a simple array
    float transform_data[16] =  { 
                                    transform.i.x, transform.i.y, transform.i.z, transform.i.w,
                                    transform.j.x, transform.j.y, transform.j.z, transform.j.w,
                                    transform.k.x, transform.k.y, transform.k.z, transform.k.w,
                                    transform.l.x, transform.l.y, transform.l.z, transform.l.w 
                                };

    // Associates the variables from our program with our data:
    GLint loc;

    // Associates the positions of our geometry
    loc = glGetAttribLocation(this->currentProgram, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    // Associates our color
    loc = glGetUniformLocation(this->currentProgram, "color");
    glUniform4f(loc, color.r, color.g, color.b, color.a); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml

    // Associates our transform matrix
    loc = glGetUniformLocation(this->currentProgram, "transform");
    glUniformMatrix4fv(loc, 1, GL_TRUE, transform_data); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml

    // Performs the drawing
    glDrawArrays(mode, 0, count);

}

// Functions to draw some of our basic geometry (uses the default transform matrix):

void Renderer::DrawPoint(const Vector2& vec, const Color& color) { DrawPoint(vec, color, Matrix4()); }
void Renderer::DrawLine(const Line& line, const Color& color) { DrawLine(line, color, Matrix4()); }
void Renderer::DrawPolyline(const Polyline& polyline, const Color& color) { DrawPolyline(polyline, color, Matrix4()); }
void Renderer::DrawTriangle(const Triangle& triangle, const Color& color) { DrawTriangle(triangle, color, Matrix4()); }
void Renderer::DrawQuad(const Quad& quad, const Color& color) { DrawQuad(quad, color, Matrix4()); }
void Renderer::DrawCircle(const Circle& circle, const Color& color) { DrawCircle(circle, color, Matrix4()); }

// Draws a point
void Renderer::DrawPoint(const Vector2& vec, const Color& color, const Matrix4& transform) {

    // Breaks our quad data into a simple array
    float data[2] = { vec.x, vec.y };

    // Performs the drawing
    DrawBasic2D(data, sizeof(data), 1, GL_POINTS, color, transform);

}

// Draws a line (converts our line to a polyline so we can re-use the polyline rendering function)
void Renderer::DrawLine(const Line& line, const Color& color, const Matrix4& transform) { DrawPolyline(Polyline(line.a, line.b), color, transform); }

// Draws a polyline
void Renderer::DrawPolyline(const Polyline& polyline, const Color& color, const Matrix4& transform) {

    // Breaks our polyline data into a simple array
    float data[2 * polyline.points.size()];
    for(int i = 0; i < polyline.points.size(); i++) {
        data[2 * i]         = polyline.points[i].x; 
        data[(2 * i) + 1]   = polyline.points[i].y;
    }

    // Performs the drawing
    DrawBasic2D(data, sizeof(data), polyline.points.size(), GL_LINE_STRIP, color, transform);

}
    
// Draws a triangle
void Renderer::DrawTriangle(const Triangle& triangle, const Color& color, const Matrix4& transform) {

    // Breaks our triangle data into a simple array
    float data[6] = {
                        triangle.a.x, triangle.a.y,
                        triangle.b.x, triangle.b.y,
                        triangle.c.x, triangle.c.y
                    };

    // Performs the drawing
    DrawBasic2D(data, sizeof(data), 3, GL_TRIANGLES, color, transform);

}

// Draws a quad
void Renderer::DrawQuad(const Quad& quad, const Color& color, const Matrix4& transform) {

    // Breaks our quad data into a simple array
    float data[8] = {
                        quad.a.x, quad.a.y,
                        quad.b.x, quad.b.y,
                        quad.c.x, quad.c.y,
                        quad.d.x, quad.d.y
                    };

    // Performs the drawing
    DrawBasic2D(data, sizeof(data), 4, GL_TRIANGLE_STRIP, color, transform);

}

// Draws a circle (converts the circle to a shape with a certain number of vertices - given by Circle.precision - before drawing)
void Renderer::DrawCircle(const Circle& circle, const Color& color, const Matrix4& transform) {

    // Gets the points of our circle.
    std::vector<Vector2> points = circle.GetPoints();

    // Breaks our circle data into a simple array
    float data[2 * points.size()];
    for(int i = 0; i < points.size(); i++) {
        data[(2 * i) + 0] = points[i].x; 
        data[(2 * i) + 1] = points[i].y;
    }

    // Performs the drawing
    DrawBasic2D(data, sizeof(data), points.size(), GL_TRIANGLE_FAN, color, transform);

}

// 3D =====================================

// Draws a basic 3D shape (uses the default transform matrix)
void Renderer::DrawBasic3D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color) { DrawBasic3D(data, data_size, count, mode, color, Matrix4()); }

// Draws a basic 3D shape applying a transformation matrix
void Renderer::DrawBasic3D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color, const Matrix4& transform) {

    // Creates our array buffer
    CreateArrayBuffer();

    // Sends our data to the array buffer
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_DYNAMIC_DRAW);

    // Breaks our transform matrix into a simple array
    float transform_data[16] =  { 
                                    transform.i.x, transform.i.y, transform.i.z, transform.i.w,
                                    transform.j.x, transform.j.y, transform.j.z, transform.j.w,
                                    transform.k.x, transform.k.y, transform.k.z, transform.k.w,
                                    transform.l.x, transform.l.y, transform.l.z, transform.l.w 
                                };

    // Associates the variables from our program with our data:
    GLint loc;

    // Associates the positions of our geometry
    loc = glGetAttribLocation(this->currentProgram, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    // Associates our color
    loc = glGetUniformLocation(this->currentProgram, "color");
    glUniform4f(loc, color.r, color.g, color.b, color.a); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml

    // Associates our transform matrix
    loc = glGetUniformLocation(this->currentProgram, "transform");
    glUniformMatrix4fv(loc, 1, GL_TRUE, transform_data); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml

    // Performs the drawing
    glDrawArrays(mode, 0, count);

}

// Functions to draw some of our basic geometry (uses the default transform matrix):

void Renderer::DrawMesh3D(const Mesh3D& mesh, const Color& color) { DrawMesh3D(mesh, color, Matrix4()); }

// Functions to draw some of our basic geometry applying transformation matrixes:

void Renderer::DrawMesh3D(const Mesh3D& mesh, const Color& color, const Matrix4& transform) {

    // Gets the triangles of our mesh.
    std::vector<Triangle3D> triangles = mesh.GetTriangles();

    // Color for each face
    Color faceColor = color;

    // Performs the drawing of each face of the cube
    for(Triangle3D tri : triangles) {

        // Breaks the current triangle data into a simple array
        float data[9] = {
                            tri.a.x, tri.a.y, tri.a.z,
                            tri.b.x, tri.b.y, tri.b.z,
                            tri.c.x, tri.c.y, tri.c.z
                        };

        // Performs the drawing
        DrawBasic3D(data, sizeof(data), 3, GL_TRIANGLE_STRIP, faceColor, transform);

        // Darkens the color for each face so they look different
        faceColor = Color(faceColor.r * 0.85f, faceColor.g * 0.85f, faceColor.b * 0.85f, faceColor.a);
        
    }

}