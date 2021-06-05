// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Renderer.hpp"

# include "RenderData.hpp"
# include "RenderStateChange.hpp"

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

// Clears our color program with a certain color
void Renderer::Clear(const Color& c) {
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

// Sets the program our renderer will use based on some shader code
void Renderer::SetProgram(const std::string& vertexCode, const std::string& fragmentCode) {

    // Creates our shader from source code
    Shader shader(vertexCode, fragmentCode);

    // Uses the program from our shader
    Renderer::currentProgram = shader.GetProgramId();
    glUseProgram(Renderer::currentProgram);

}

// Sets the program our renderer will use from a shader
void Renderer::SetProgram(const Shader& shader) {

    // Uses the program from our shader
    Renderer::currentProgram = shader.GetProgramId();
    glUseProgram(Renderer::currentProgram);

}

// Sets the view matrix for the current program
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

// Draws an object directly interacting with our graphics API
void Renderer::DrawInternal(float* data, size_t data_size, size_t count, GLenum mode, const Color& color, const Matrix4x4& transform) {

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
