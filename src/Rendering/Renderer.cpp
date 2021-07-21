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
Matrix4x4 Renderer::projection = Matrix4x4::Identity;
Matrix4x4 Renderer::view = Matrix4x4::Identity;

//Current array buffer bound to the renderer
GLuint Renderer::vertexBuffer{ 0 };
GLuint Renderer::vertexArray{ 0 };

bool Renderer::wireframeMode{ false };

// Initializes the renderer
void Renderer::Init() {

    Renderer::currentProgram = 0;
    Renderer::vertexBuffer = 0;

    // Initializes GLEW to handle OpenGL functions
    GLint result = glewInit();
    std::cout << "GlewStatus: " << glewGetErrorString(result) << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

// Destroys the renderer
void Renderer::Destroy() {
    glDeleteBuffers(1, &(Renderer::vertexBuffer));
}

// Clears our color program with a certain color
void Renderer::Clear(const Color& c) {
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    Renderer::SetProjectionMatrix(projection);
    Renderer::SetViewMatrix(view);
}

// Sets the view matrix for the current program
void Renderer::SetViewMatrix(const Matrix4x4& viewMatrix)
{
    GLint loc = glGetUniformLocation(Renderer::currentProgram, "view");
    glUniformMatrix4fv(loc, 1, GL_FALSE, viewMatrix.DataFlat().data()); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml
    view = viewMatrix;
}

// Sets the projection matrix for the current program
void Renderer::SetProjectionMatrix(const Matrix4x4& projectionMatrix)
{
    GLint loc = glGetUniformLocation(Renderer::currentProgram, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, projectionMatrix.DataFlat().data()); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml
    projection = projectionMatrix;
}

// Creates an array buffer (if one was already created re-uses it)
void Renderer::CreateArrayBuffer() {

    // If the buffer already exists return
    if(vertexBuffer > 0)
        return;

    // Creates our vertex array object (VAO)
    // Needed for core profile, not on compatibility mode.
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // Creates our vertex buffer object (VBO)
    GLuint buffer;
    glGenBuffers(1, &buffer);

    // Sets our array as current.
    Renderer::vertexArray = vao;
    glBindVertexArray(vao);
    // Sets our buffer as the GL_ARRAY_BUFFER
    Renderer::vertexBuffer = buffer;
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

// Draws an object directly interacting with our graphics API
void Renderer::DrawInternal(
        const void* data,
        size_t data_size,
        size_t count,
        GLenum mode,
        const Color& color,
        const Matrix4x4& transform,
        TextureObject* textureObject)
{

    // Creates our array buffer
    CreateArrayBuffer();

    // Sends our data to the array buffer
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_DYNAMIC_DRAW);

    // Associates the variables from our program with our data:
    const GLint positionLoc = 0;
    const GLint texturePositionLoc = 1;
    const GLint normalLoc = 2;

    // Associates the positions of our geometry
    glEnableVertexAttribArray(positionLoc);
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, data_size / count, 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    // Associates the positions of our geometry
    glEnableVertexAttribArray(texturePositionLoc);
    glVertexAttribPointer(texturePositionLoc, 2, GL_FLOAT, GL_FALSE, data_size / count,
            reinterpret_cast<void*>(3 * sizeof(float)));
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, data_size / count, 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    const GLint transformLoc = 0;
    const GLint colorLoc = 3;
    const GLint texSamplerLoc = 4;
    // Ambient Light
    const GLint ambientLightColorLoc = 5;
    const GLint ambientReflectionLoc = 6; //ka
    // Point Light
    const GLint lightPositionLoc = 7;
    const GLint diffuseLightColorLoc = 8;
    const GLint diffuseReflectionLoc = 9; //kd


    // Associates our transform matrix
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform.DataFlat().data()); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml

    // Associates our color
    glUniform4f(colorLoc, color.r, color.g, color.b, color.a); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml

    if (textureObject != nullptr)
    {
        GLint textureUnit{ 0 };
        // Texture unit to activate
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        // Binds texture to above texture unit.
        textureObject->Bind();

        // Texture unit to associate sampler with.
        glUniform1i(texSamplerLoc, textureUnit); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml
    }

    glUniform3f(ambientLightColorLoc, 1.0f, 0.0f, 0.0f);
    glUniform1f(ambientReflectionLoc, 0.2f);
    glUniform3f(lightPositionLoc, 0.0f, 1.0f, 0.0f);
    glUniform3f(diffuseLightColorLoc, 1.0f, 1.0f, 1.0f);
    glUniform1f(diffuseReflectionLoc, 1.0f);

    if (wireframeMode)
        mode = GL_LINE_LOOP;

    // Performs the drawing
    glDrawArrays(mode, 0, count);

}

void Renderer::DrawSkybox(
    const void* data,
    size_t data_size,
    size_t count,
    const Matrix4x4& transform,
    TextureObject* textureObject)
{
    // Creates our array buffer
    CreateArrayBuffer();

    // Sends our data to the array buffer
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_DYNAMIC_DRAW);

    // Associates the variables from our program with our data:
    GLint loc;

    // Associates the positions of our geometry
    loc = glGetAttribLocation(Renderer::currentProgram, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, data_size / count, 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    glDepthMask(GL_FALSE);
    // ... set view and projection matrix

    if (textureObject != nullptr)
    {
        GLint textureUnit{ 0 };
        // Texture unit to activate
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        // Binds texture to above texture unit.
        textureObject->Bind();

        // Texture unit to associate sampler with.
        loc = glGetUniformLocation(Renderer::currentProgram, "texSampler");
        glUniform1i(loc, textureUnit); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUniform.xhtml
    }

    glDrawArrays(GL_TRIANGLE_FAN, 0, count);
    glDepthMask(GL_TRUE);
}

void Renderer::ToggleWireframe()
{
    wireframeMode = !wireframeMode;

    if (wireframeMode)
        std::cout << "Wireframe mode:\t enabled.\n";
    else
        std::cout << "Wireframe mode:\tdisabled.\n";
}
