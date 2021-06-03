// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Input.hpp"

# include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */

// Stores what mouse buttons are pressed:

bool Input::leftMousePressed = false;
bool Input::rightMousePressed = false;

// Process mouse input
void Input::ProcessMouse(GLFWwindow *window, int button, int action, int mods) {

    switch (button) {

    case GLFW_MOUSE_BUTTON_LEFT:
        if(action == GLFW_PRESS)
            leftMousePressed = true;
        else if (action == GLFW_RELEASE)
            leftMousePressed = false;
        break;
    
    case GLFW_MOUSE_BUTTON_RIGHT:
        if(action == GLFW_PRESS)
            rightMousePressed = true;
        else if (action == GLFW_RELEASE)
            rightMousePressed = false;
        break;

    default:
        break;

    }

}

/// (0, 0) is the bottom left corner.
Vector2 Input::mousePosition{};

void Input::ProcessCursor(GLFWwindow *window, double x, double y)
{
    int width{};
    int height{};
    glfwGetWindowSize(window, &width, &height);

    mousePosition = Vector2
    {
        static_cast<float>(x),
        static_cast<float>(height) - static_cast<float>(y)
    };
}

// Stores what keys are pressed:

bool Input::leftArrowPressed = false;
bool Input::rightArrowPressed = false;

bool Input::leftPressed = false;
bool Input::rightPressed = false;
bool Input::upPressed = false;
bool Input::downPressed = false;
bool Input::spacePressed = false;
bool Input::shiftPressed = false;

// Process key input
void Input::ProcessKey(GLFWwindow *window, int keyCode, int scanCode, int action, int mods) {

    switch (keyCode) {

    case GLFW_KEY_LEFT:
        if(action == GLFW_PRESS)
            leftArrowPressed = true;
        else if (action == GLFW_RELEASE)
            leftArrowPressed = false;
        break;
    
    case GLFW_KEY_RIGHT:
        if(action == GLFW_PRESS)
            rightArrowPressed = true;
        else if (action == GLFW_RELEASE)
            rightArrowPressed = false;
        break;

    case GLFW_KEY_A:
        if(action == GLFW_PRESS)
            leftPressed = true;
        else if (action == GLFW_RELEASE)
            leftPressed = false;
        break;
    
    case GLFW_KEY_D:
        if(action == GLFW_PRESS)
            rightPressed = true;
        else if (action == GLFW_RELEASE)
            rightPressed = false;
        break;

    case GLFW_KEY_W:
        if(action == GLFW_PRESS)
            upPressed = true;
        else if (action == GLFW_RELEASE)
            upPressed = false;
        break;
    
    case GLFW_KEY_S:
        if(action == GLFW_PRESS)
            downPressed = true;
        else if (action == GLFW_RELEASE)
            downPressed = false;
        break;

    case GLFW_KEY_SPACE:
        if (action == GLFW_PRESS)
            spacePressed = true;
        else if (action == GLFW_RELEASE)
            spacePressed = false;
        break;

    case GLFW_KEY_LEFT_SHIFT:
        if (action == GLFW_PRESS)
            shiftPressed = true;
        else if (action == GLFW_RELEASE)
            shiftPressed = false;
        break;

    default:
        break;

    }

}
