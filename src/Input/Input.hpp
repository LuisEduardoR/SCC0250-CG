// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file handles and flags all inputs
*/

# ifndef INPUT_HPP
# define INPUT_HPP

# include "../Math/Vector.hpp"

struct GLFWwindow;

class Input {

public:
    // Process inputs
    static void ProcessMouse(GLFWwindow *window, int button, int action, int mods);
    static void ProcessKey(GLFWwindow *window, int keyCode, int scanCode, int action, int mods);
    static void ProcessCursor(GLFWwindow *window, double x, double y);

    // Stores mouse buttons
    static bool leftMousePressed;
    static bool rightMousePressed;

    // Stores what keys are pressed:
    static bool leftArrowPressed;
    static bool rightArrowPressed;

    static bool leftPressed;
    static bool rightPressed;
    static bool upPressed;
    static bool downPressed;
    static bool spacePressed;
    static bool shiftPressed;

    static Vector2 mousePosition;

private:
    // Disallow any instances
    Input() {}

};

# endif /* end of include guard: INPUT_HPP */