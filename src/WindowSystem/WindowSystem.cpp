// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "WindowSystem.hpp"

# include <iostream>

# include <GLFW/glfw3.h>

# include "../Input/Input.hpp"

namespace {
constexpr std::array<int, 3> cursorModeToGlfw{{
    GLFW_CURSOR_NORMAL,
    GLFW_CURSOR_HIDDEN,
    GLFW_CURSOR_DISABLED,
}};
}

GLFWwindow* WindowSystem::mainWindow{ nullptr };

// Initializes the windom system
void WindowSystem::Init() {

    // Initializes GLFW
    glfwInit();

    // Set a hint for the next glfwCreateWindowCall.
    // Makes our window invisible for now
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    // Make window float on i3
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // Use OpenGL 4.2 Core profile.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // Creates our window
    WindowSystem::mainWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    // Makes our window the default
    glfwMakeContextCurrent(WindowSystem::mainWindow);

    // Binds input
    SetKeyCallback(Input::ProcessKey);
    SetMouseButtonCallback(Input::ProcessMouse);
    SetCursorPosCallback(Input::ProcessCursor);

    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(mainWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    } else {
        std::cout << "WARN: Raw mouse motion is unsupported\n";
    }
}

// Destroys the windows system
void WindowSystem::Destroy() {
    glfwDestroyWindow(WindowSystem::mainWindow);
    glfwTerminate();
}

// Shows our window
void WindowSystem::Show() {
    glfwShowWindow(WindowSystem::mainWindow);
}

// Checks if our program should close
int WindowSystem::ShouldClose() {
    return glfwWindowShouldClose(WindowSystem::mainWindow);
}

// Pools our window system for events
void WindowSystem::PollEvents() {
    glfwPollEvents();
}

// Swaps our back and front buffers
void WindowSystem::SwapBuffers() {
    glfwSwapBuffers(mainWindow);
}

// Sets a callback function for when a key input is detected
void WindowSystem::SetKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(mainWindow, callback);
}

// Sets a callback function for when a mouse button input is detected
void WindowSystem::SetMouseButtonCallback(GLFWmousebuttonfun callback) {
    glfwSetMouseButtonCallback(mainWindow, callback);
}

// Sets a callback function for when the cursor moves
void WindowSystem::SetCursorPosCallback(GLFWcursorposfun callback) {
    glfwSetCursorPosCallback(mainWindow, callback);
}

void WindowSystem::SetCursorMode(CursorMode cursorMode) {
    auto glfwCursorMode = cursorModeToGlfw[static_cast<std::size_t>(cursorMode)];

    glfwSetInputMode(mainWindow, GLFW_CURSOR, glfwCursorMode);
}
