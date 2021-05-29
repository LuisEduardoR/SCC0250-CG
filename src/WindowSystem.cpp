// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "WindowSystem.hpp"

// Constructor
WindowSystem::WindowSystem() {
    
    // Initializes GLFW
    glfwInit();

    // Makes our window invisible for now
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // Creates our window
    this->mainWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    // Makes our window the default
    glfwMakeContextCurrent(this->mainWindow);

}

// Destructor
WindowSystem::~WindowSystem() {
    glfwDestroyWindow(this->mainWindow);
    glfwTerminate();
}

// Shows our window
void WindowSystem::Show() {
    glfwShowWindow(this->mainWindow);
}

// Checks if our program should close
int WindowSystem::ShouldClose() {
    return glfwWindowShouldClose(this->mainWindow);
}

// Pools our window system for events
void WindowSystem::PollEvents() {
    glfwPollEvents();
}

// Swaps our back and front buffers
void WindowSystem::SwapBuffers() {
    glfwSwapBuffers(this->mainWindow);
}

// Sets a callback function for when a key input is detected
void WindowSystem::SetKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(this->mainWindow, callback);
}

// Sets a callback function for when a mouse button input is detected
void WindowSystem::SetMouseButtonCallback(GLFWmousebuttonfun callback) {
    glfwSetMouseButtonCallback(this->mainWindow, callback);
}