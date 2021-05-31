// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Renderer.hpp"

GLuint Renderer::currentProgram{ 0 };

    //Current array buffer bound to the renderer
GLuint Renderer::arrayBuffer{ 0 };

// Initializes the renderer
void Renderer::Init() {

    Renderer::currentProgram = 0;
    Renderer::arrayBuffer = 0;

    // Initializes GLEW to handle OpenGL functions
    GLint result = glewInit();
    std::cout << "GlewStatus: " << glewGetErrorString(result) << std::endl;

}

// Destroys the renderer
void Renderer::Destroy() {
    glDeleteBuffers(1, &(Renderer::arrayBuffer));
}

// Enables or disables 3D rendering (enables or disables depth buffer testing)  
void Renderer::Set3D(bool enabled) {

    if(enabled)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

}

// Clears our color program with a certain color
void Renderer::Clear(const Color& c) {
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Clears our color buffer with a default color
void Renderer::Clear() { Clear(Color::black); }

// Sets the program our renderer will use based on some shader code
void Renderer::SetProgram(std::string vertex_code, std::string fragment_code) {

    // Creates the program we are going to use from our vertex and fragment shader's source code
    Renderer::currentProgram = Shader::CreateProgram(vertex_code, fragment_code);

    // Uses our program
    glUseProgram(Renderer::currentProgram);

}

void Renderer::SetViewMatrix(const Matrix4x4& viewMatrix)
{
    GLint loc = glGetUniformLocation(Renderer::currentProgram, "view");
    glUniformMatrix4fv(loc, 1, GL_FALSE, viewMatrix.DataFlat().data()); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml
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
    Renderer::arrayBuffer = buffer;
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

}

// 2D =====================================

// Draws a basic 2D shape (uses the default transform matrix)
void Renderer::DrawBasic2D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color) { DrawBasic2D(data, data_size, count, mode, color, Matrix4x4::Identity); }

// Draws a basic 2D shape
void Renderer::DrawBasic2D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color, const Matrix4x4& transform) {

    // Creates our array buffer
    CreateArrayBuffer();

    // Sends our data to the array buffer
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_DYNAMIC_DRAW);

    // Associates the variables from our program with our data:
    GLint loc;

    // Associates the positions of our geometry
    loc = glGetAttribLocation(Renderer::currentProgram, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    // Associates our color
    loc = glGetUniformLocation(Renderer::currentProgram, "color");
    glUniform4f(loc, color.r, color.g, color.b, color.a); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml

    // Associates our transform matrix
    loc = glGetUniformLocation(Renderer::currentProgram, "transform");
    glUniformMatrix4fv(loc, 1, GL_FALSE, transform.DataFlat().data()); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml

    // Performs the drawing
    glDrawArrays(mode, 0, count);

}

// Draws a Shape2D applying a transformation matrix
void Renderer::DrawShape2D(const Shape2D& shape, const Matrix4x4& transform) {
    // Gets the vertices of our shape
    VertexData data = shape.GetVertices();

    // Performs the drawing
    DrawBasic2D((float*)data.vertices2D, data.vertexCount * sizeof(Vector2), data.vertexCount, shape.GetDrawMode(), shape.color, transform);

}

// Draws a Shape2DCollection applying a transformation matrix
void Renderer::DrawShape2DCollection(const Shape2DCollection& shapes, const Matrix4x4& transform) {

    // Performs the drawing of each shape
    /* for (auto iter = (*shapes).cbegin(); iter != (*shapes).cend(); iter++) */
    /*     DrawShape2D(*(*iter).get(), transform); */
    for (const std::unique_ptr<Shape2D>& shape : *shapes.get())
        DrawShape2D(*shape.get(), transform);

}

// 3D =====================================

// Draws a basic 3D shape (uses the default transform matrix)
void Renderer::DrawBasic3D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color) { DrawBasic3D(data, data_size, count, mode, color, Matrix4x4::Identity); }

// Draws a basic 3D shape applying a transformation matrix
void Renderer::DrawBasic3D(float* data, size_t data_size, size_t count, GLenum mode, const Color& color, const Matrix4x4& transform) {

    // Creates our array buffer
    CreateArrayBuffer();

    // Sends our data to the array buffer
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_DYNAMIC_DRAW);

    // Associates the variables from our program with our data:
    GLint loc;

    // Associates the positions of our geometry
    loc = glGetAttribLocation(Renderer::currentProgram, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    // Associates our color
    loc = glGetUniformLocation(Renderer::currentProgram, "color");
    glUniform4f(loc, color.r, color.g, color.b, color.a); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml

    // Associates our transform matrix
    loc = glGetUniformLocation(Renderer::currentProgram, "transform");
    glUniformMatrix4fv(loc, 1, GL_TRUE, transform.DataFlat().data()); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml

    // Performs the drawing
    glDrawArrays(mode, 0, count);

}

// Functions to draw some of our basic geometry (uses the default transform matrix):

void Renderer::DrawMesh3D(const Mesh3D& mesh, const Color& color) { DrawMesh3D(mesh, color, Matrix4x4::Identity); }

// Functions to draw some of our basic geometry applying transformation matrixes:

void Renderer::DrawMesh3D(const Mesh3D& mesh, const Color& color, const Matrix4x4& transform) {

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
