// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the classes to handle shader loading and using
*/

# ifndef SHADER_HPP
# define SHADER_HPP

# include <GL/glew.h>
# include <iostream>

class Shader {

public:

    // Checks a shader for compile errors and prints them if there are any
    static void CheckShaderForCompileError(GLuint shader);

    // Creates a shader of a certain type from the source code, type can be GL_VERTEX_SHADER  or GL_FRAGMENT_SHADER  
    static GLint CreateShader(const std::string& shader_code, GLenum shaderType);

    // Creates a program from the source code of a vertex shader and a fragment shader
    static GLint CreateProgram(const std::string& vertexCode, const std::string& fragmentCode);

};

# endif /* end of include guard: SHADER_HPP */