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
    enum class State
    {
        Released,   //Key has been released for a frame or more.
        Down,       // Key was pressed this frame.
        Held,       // Key has been pressed for a frame or more.
        Up,         // Key was released this frame.
    };

    // Process inputs
    static void ProcessMouse(GLFWwindow *window, int button, int action, int mods);
    static void ProcessKey(GLFWwindow *window, int keyCode, int scanCode, int action, int mods);
    static void ProcessCursor(GLFWwindow *window, double x, double y);
    
    // Update key states
    static void Update();

    // Stores mouse buttons
    static State leftMouse;
    static State rightMouse;

    // Stores what keys are pressed:
    static State leftArrow;
    static State rightArrow;

    static State left;
    static State right;
    static State up;
    static State down;
    static State space;
    static State shift;
    static State p;

    static Vector2 mousePosition;

    // Disallow any instances
    Input() = delete;

};

# endif /* end of include guard: INPUT_HPP */
