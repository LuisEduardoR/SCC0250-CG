// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Shader.hpp"

// Checks a shader for compile errors and prints them if there are any
void CheckShaderForCompileError(GLuint shader) {

    // Checks for compilation errors
    GLint compileStatus = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    // Prints the compilation errors if they happened
    if(compileStatus == GL_FALSE) {

        // Finds the size of the error log
        int infoLen = 512;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        // Retrieves the error log and prints it to the screen
        char info[infoLen];
        glGetShaderInfoLog(shader, infoLen, NULL, info);

        // Prints the error
        std::cout << "Shader compile error:" << std::endl;
        std::cout << "--> " << info << std::endl;

    }

}

// Creates a shader of a certain type from the source code, type can be GL_VERTEX_SHADER  or GL_FRAGMENT_SHADER  
GLint CreateShader(const std::string& shaderCode, GLenum shaderType) {

    GLuint shader = glCreateShader(shaderType);

    // Associates our source code to the GLSl slot solicitados
    const char *shaderCode_cstr = shaderCode.c_str();
    glShaderSource(shader, 1, &shaderCode_cstr, NULL);

    // Compiles the shader and checks for errors
    glCompileShader(shader);
    CheckShaderForCompileError(shader);

    return shader;

}

// Creates a program from the source code of a vertex shader and a fragment shader
GLint CreateProgram(const std::string& vertexCode, const std::string& fragmentCode) {

    // Creates a new program
    GLuint program = glCreateProgram();

    // Creates vertex and fragment shaders
    GLuint vertex = CreateShader(vertexCode, GL_VERTEX_SHADER);
    GLuint fragment = CreateShader(fragmentCode, GL_FRAGMENT_SHADER);

    // Attaches our shaders to our program
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Links our program
    glLinkProgram(program);

    return program;

}
 