// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# ifndef SHADER_HPP
# define SHADER_HPP

# include <GL/glew.h>
# include <iostream>

/*
    This file contains functions to handle shaders
*/

// Checks a shader for compile errors and prints them if there are any
void CheckShaderForCompileError(GLuint shader);

// Creates a shader of a certain type from the source code, type can be GL_VERTEX_SHADER  or GL_FRAGMENT_SHADER  
GLint CreateShader(const std::string& shader_code, GLenum shaderType);

// Creates a program from the source code of a vertex shader and a fragment shader
GLint CreateProgram(const std::string& vertexCode, const std::string& fragmentCode);
 

# endif