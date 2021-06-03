// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the classes that handles the program's window system
*/

# ifndef WINDOW_SYSTEM_HPP
# define WINDOW_SYSTEM_HPP

#include <GL/glew.h>  

# define GLFW_INCLUDE_NONE
# include <GLFW/glfw3.h>

# include <map>
# include <vector>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define WINDOW_TITLE "Trabalho 1"

class WindowSystem {

private:

    // Our current main window
    static GLFWwindow *mainWindow;

public:

    // Initializes the windom system
    static void Init();

    // Destroys the windows system
    static void Destroy();

    // Shows our window
    static void Show();

    // Checks if our program should close
    static int ShouldClose();

    // Pools our window system for events
    static void PollEvents();

    // Swaps our back and front buffers
    static void SwapBuffers();

    // Sets a callback function for when a key input is detected
    static void SetKeyCallback(GLFWkeyfun callback);

    // Sets a callback function for when a mouse button input is detected
    static void SetMouseButtonCallback(GLFWmousebuttonfun callback);
    
    // Sets a callback function for when the cursor moves
    static void SetCursorPosCallback(GLFWcursorposfun callback);
};

# endif /* end of include guard: WINDOW_SYSTEM_HPP */