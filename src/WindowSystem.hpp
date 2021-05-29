// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# ifndef WINDOW_SYSTEM_HPP
# define WINDOW_SYSTEM_HPP

# include <map>
# include <vector>

#include <GL/glew.h>  

# define GLFW_INCLUDE_NONE
# include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define WINDOW_TITLE "Minha Janela (EP3 - Pirâmide)"

/*
    This file contains the classes that handles the program's window system
*/

class WindowSystem {

private:

    // Our current main window
    GLFWwindow *mainWindow;

public:

    // Constructor
    WindowSystem();

    // Destructor
    ~WindowSystem();

    // Shows our window
    void Show();

    // Checks if our program should close
    int ShouldClose();

    // Pools our window system for events
    void PollEvents();

    // Swaps our back and front buffers
    void SwapBuffers();

    // Sets a callback function for when a key input is detected
    void SetKeyCallback(GLFWkeyfun callback);

    // Sets a callback function for when a mouse button input is detected
    void SetMouseButtonCallback(GLFWmousebuttonfun callback);

};

# endif