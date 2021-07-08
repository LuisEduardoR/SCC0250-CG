// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Input.hpp"

# include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */

// Stores what mouse buttons are pressed:

Input::State Input::leftMouse = State::Released;
Input::State Input::rightMouse = State::Released;

// Process mouse input
void Input::ProcessMouse(GLFWwindow *window, int button, int action, int mods) {

    switch (button) {

    case GLFW_MOUSE_BUTTON_LEFT:
        if(action == GLFW_PRESS)
            leftMouse = State::Down;
        else if (action == GLFW_RELEASE)
            leftMouse = State::Up;
        break;
    
    case GLFW_MOUSE_BUTTON_RIGHT:
        if(action == GLFW_PRESS)
            rightMouse = State::Down;
        else if (action == GLFW_RELEASE)
            rightMouse = State::Up;
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

Input::State Input::leftArrow = State::Released;
Input::State Input::rightArrow = State::Released;

Input::State Input::left = State::Released;
Input::State Input::right = State::Released;
Input::State Input::up = State::Released;
Input::State Input::down = State::Released;
Input::State Input::space = State::Released;
Input::State Input::shift = State::Released;
Input::State Input::p = State::Released;
Input::State Input::esc = State::Released;

// Process key input
void Input::ProcessKey(GLFWwindow *window, int keyCode, int scanCode, int action, int mods) {

    switch (keyCode) {

    case GLFW_KEY_LEFT:
        if(action == GLFW_PRESS)
            leftArrow = State::Down;
        else if (action == GLFW_RELEASE)
            leftArrow = State::Up;
        break;
    
    case GLFW_KEY_RIGHT:
        if(action == GLFW_PRESS)
            rightArrow = State::Down;
        else if (action == GLFW_RELEASE)
            rightArrow = State::Up;
        break;

    case GLFW_KEY_A:
        if(action == GLFW_PRESS)
            left = State::Down;
        else if (action == GLFW_RELEASE)
            left = State::Up;
        break;
    
    case GLFW_KEY_D:
        if(action == GLFW_PRESS)
            right = State::Down;
        else if (action == GLFW_RELEASE)
            right = State::Up;
        break;

    case GLFW_KEY_W:
        if(action == GLFW_PRESS)
            up = State::Down;
        else if (action == GLFW_RELEASE)
            up = State::Up;
        break;
    
    case GLFW_KEY_S:
        if(action == GLFW_PRESS)
            down = State::Down;
        else if (action == GLFW_RELEASE)
            down = State::Up;
        break;

    case GLFW_KEY_SPACE:
    {
        if (action == GLFW_PRESS)
            space = State::Down;
        else if (action == GLFW_RELEASE)
            space = State::Up;
        break;
    }

    case GLFW_KEY_LEFT_SHIFT:
        if (action == GLFW_PRESS)
            shift = State::Down;
        else if (action == GLFW_RELEASE)
            shift = State::Up;
        break;

    case GLFW_KEY_P:
        if (action == GLFW_PRESS)
            p = State::Down;
        else if (action == GLFW_RELEASE)
            p = State::Up;
        break;

    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            esc = State::Down;
        else if (action == GLFW_RELEASE)
            esc = State::Up;
        break;

    default:
        break;

    }

}

void Input::Update()
{
    if (leftMouse == State::Down)
        leftMouse = State::Held;
    else if (leftMouse == State::Up)
        leftMouse = State::Released;

    if (rightMouse == State::Down)
        rightMouse = State::Held;
    else if (rightMouse == State::Up)
        rightMouse = State::Released;

    if (leftArrow == State::Down)
        leftArrow = State::Held;
    else if (leftArrow == State::Up)
        leftArrow = State::Released;

    if (rightArrow == State::Down)
        rightArrow = State::Held;
    else if (rightArrow == State::Up)
        rightArrow = State::Released;

    if (left == State::Down)
        left = State::Held;
    else if (left == State::Up)
        left = State::Released;

    if (right == State::Down)
        right = State::Held;
    else if (right == State::Up)
        right = State::Released;

    if (up == State::Down)
        up = State::Held;
    else if (up == State::Up)
        up = State::Released;

    if (down == State::Down)
        down = State::Held;
    else if (down == State::Up)
        down = State::Released;

    if (space == State::Down)
        space = State::Held;
    else if (space == State::Up)
        space = State::Released;

    if (shift == State::Down)
        shift = State::Held;
    else if (shift == State::Up)
        shift = State::Released;

    if (p == State::Down)
        p = State::Held;
    else if (p == State::Up)
        p = State::Released;

    if (esc == State::Down)
        esc = State::Held;
    else if (esc == State::Up)
        esc = State::Released;
}
