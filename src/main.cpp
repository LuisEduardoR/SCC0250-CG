// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/* para linux, instalar os pacotes libglfw3-dev mesa-common-dev libglew-dev */
/* para compilar no linux: g++ ./src/*.cpp -lglfw -lGL -lGLEW -lm */

/* para windows, instalar o MSYS2 e as depedências: 

    mingw-w64-x86_64-toolchain, 
    mingw-w64-x86_64-glfw, 
    mingw-w64-x86_64-glew, 
    e mingw-w64-x86_64-glm

    adicionar "C:\msys64\mingw64\bin" ao PATH (se o MSYS2 foi instalado no local padrão)
*/
/* para compilar no windows: g++ ./src/*.cpp -lglfw3 -lglew32 -lopengl32 -lm */

# include <GL/glew.h>

# include <iostream>
# include <cmath>
# include <chrono>
# include <thread>

# include "WindowSystem.hpp"
# include "Renderer.hpp"
# include "Shader.hpp"
# include "Color.hpp"
# include "Geometry.hpp"



// Stores what mouse buttons are pressed:

static bool leftMousePressed = false;
static bool rightMousePressed = false;

// Process mouse input
void ProcessMouse(GLFWwindow *window, int button, int action, int mods) {

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

// Stores what keys are pressed:

static bool leftArrowPressed = false;
static bool rightArrowPressed = false;

static bool leftPressed = false;
static bool rightPressed = false;
static bool upPressed = false;
static bool downPressed = false;

// Process key input
void ProcessKey(GLFWwindow *window, int keyCode, int scanCode, int action, int mods) {

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

    default:
        break;

    }

}
/*

const Shape2DCollection ship( new std::vector<std::unique_ptr<Shape2D>> {
    // Ship Base 
    std::unique_ptr<Triangle>{
        new Triangle{ { +0.000f, +0.660f }, { -0.231f, +0.048f }, { +0.231f, +0.048f } } },
    std::unique_ptr<Triangle>{
        new Triangle{ { -0.231f, +0.048f }, { +0.231f, +0.048f }, { -0.526f, -0.205f } } },
    std::unique_ptr<Triangle>{
        new Triangle{ { +0.231f, +0.048f }, { -0.526f, -0.205f }, { +0.526f, -0.205f } } },
    std::unique_ptr<Triangle>{
        new Triangle{ { -0.526f, -0.205f }, { -0.190f, -0.455f }, { +0.190f, -0.455f } } },
    std::unique_ptr<Triangle>{
        new Triangle{ { -0.526f, -0.205f }, { +0.526f, -0.205f }, { +0.190f, -0.455f } } },
    std::unique_ptr<Triangle>{
        new Triangle{ { -0.526f, -0.205f }, { -0.190f, -0.455f }, { -0.581f, -0.744f } } },
    std::unique_ptr<Triangle>{
        new Triangle{ { +0.526f, -0.205f }, { +0.190f, -0.455f }, { +0.581f, -0.744f } } },
    // Ship Window
    std::unique_ptr<Triangle>{
        new Triangle{ { +0.000f, +0.530f }, { -0.194f, -0.074f }, { +0.194f, -0.074f } } },
    std::unique_ptr<Triangle>{
        new Triangle{ { +0.000f, -0.290f }, { -0.194f, -0.074f }, { +0.194f, -0.074f } } },
    // Ship Cannons
    std::unique_ptr<Quad>{
        new Quad{ { -0.405f, +0.264f }, { -0.304f, +0.263f }, { -0.405f, -0.196f }, { -0.304f, +0.196f } } },
    std::unique_ptr<Quad>{
        new Quad{ { +0.304f, +0.264f }, { +0.405f, +0.263f }, { +0.304f, -0.196f }, { +0.405f, +0.196f } } },
    // Ship Thruster
    std::unique_ptr<Quad>{
        new Quad{ { -0.190f, -0.455f }, { +0.213f, -0.455f }, { -0.150f, -0.728f }, { +0.150f, -0.728f } } },
    // Ship Circles
    std::unique_ptr<Circle>{
        new Circle{ { -0.357f, -0.354f }, 0.156f } },
    std::unique_ptr<Circle>{
        new Circle{ { +0.357f, -0.354f }, 0.156f } },
});*/
// const std::array<Triangle, 7> shipBase{{
//     { { +0.000f, +0.660f }, { -0.231f, +0.048f }, { +0.231f, +0.048f } },
//     { { -0.231f, +0.048f }, { +0.231f, +0.048f }, { -0.526f, -0.205f } },
//     { { +0.231f, +0.048f }, { -0.526f, -0.205f }, { +0.526f, -0.205f } },
//     { { -0.526f, -0.205f }, { -0.190f, -0.455f }, { +0.190f, -0.455f } },
//     { { -0.526f, -0.205f }, { +0.526f, -0.205f }, { +0.190f, -0.455f } },
//     { { -0.526f, -0.205f }, { -0.190f, -0.455f }, { -0.581f, -0.744f } },
//     { { +0.526f, -0.205f }, { +0.190f, -0.455f }, { +0.581f, -0.744f } },
// }};

// const std::array<Quad, 2> shipCannons{{
//     { { -0.405f, +0.264f }, { -0.304f, +0.263f }, { -0.405f, -0.196f }, { -0.304f, +0.196f } },
//     { { +0.304f, +0.264f }, { +0.405f, +0.263f }, { +0.304f, -0.196f }, { +0.405f, +0.196f } },
// }};

// GL_TRIANGLE_STRIP FORMAT
// constexpr Mesh3D shipNose{
//     { 
//         { +0.000f, +0.660f, 0.0f},
//         { -0.231f, +0.048f, 0.0f },
//         { +0.231f, +0.048f, 0.0f },
//     }
// };

// constexpr Mesh3D shipBodyRight{
//     { 
//         { -0.231f, +0.048f, 0.0f },
//         { +0.231f, +0.048f, 0.0f },
//         { -0.526f, -0.205f, 0.0f },
//         { +0.526f, -0.205f, 0.0f },
//         { +0.190f, -0.455f, 0.0f },
//         { +0.581f, -0.744f, 0.0f },
//     }
// };

// constexpr Mesh3D shipBodyLeft{
//     { 
//         { +0.000f, +0.660f, 0.0f},
//         { -0.231f, +0.048f, 0.0f },
//         { -0.526f, -0.205f, 0.0f },
//         { -0.581f, -0.744f, 0.0f },
//         { -0.190f, -0.455f, 0.0f },
//         { +0.190f, -0.455f, 0.0f },
//         { +0.581f, -0.744f, 0.0f },
//         { +0.526f, -0.205f, 0.0f },
//         { +0.231f, +0.048f, 0.0f },
//     }
// };




int main(void) {

    Shape2DCollection ship( new std::vector<std::unique_ptr<Shape2D>>{});
    // Ship Base 
    ship.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, +0.660f }, { -0.231f, +0.048f }, { +0.231f, +0.048f }
    }});
    ship.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.231f, +0.048f }, { +0.231f, +0.048f }, { -0.526f, -0.205f }
    }});
    ship.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.231f, +0.048f }, { -0.526f, -0.205f }, { +0.526f, -0.205f }
    }});
    ship.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.526f, -0.205f }, { -0.190f, -0.455f }, { +0.190f, -0.455f }
    }});
    ship.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.526f, -0.205f }, { +0.526f, -0.205f }, { +0.190f, -0.455f }
    }});
    ship.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.526f, -0.205f }, { -0.190f, -0.455f }, { -0.581f, -0.744f }
    }});
    ship.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.526f, -0.205f }, { +0.190f, -0.455f }, { +0.581f, -0.744f }
    }});
    // Ship Window
    ship.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, +0.530f }, { -0.194f, -0.074f }, { +0.194f, -0.074f }
    }});
    ship.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -0.290f }, { -0.194f, -0.074f }, { +0.194f, -0.074f }
    }});
    // Ship Cannons
    ship.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.405f, +0.264f }, { -0.304f, +0.263f }, { -0.405f, -0.196f }, { -0.304f, +0.196f }
    }});
    ship.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { +0.304f, +0.264f }, { +0.405f, +0.263f }, { +0.304f, -0.196f }, { +0.405f, +0.196f }
    }});
    // Ship Thruster
    ship.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.190f, -0.455f }, { +0.213f, -0.455f }, { -0.150f, -0.728f }, { +0.150f, -0.728f }
    }});
    // Ship Circles
    ship.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.357f, -0.354f }, 0.156f
    }});
    ship.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +0.357f, -0.354f }, 0.156f
    }});

    // Shape2DCollection boss( new std::vector<std::unique_ptr<Shape2D>>{});

    // // Boss Base
    // boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
    //     { +0.000f, -207.000f }, { -80.000f, -76.950f }, { -50.000f, -18.320f }
    // }});
    // boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
    //     { +0.000f, -207.000f }, { -50.000f, -18.320f }, { +0.000f, +0.000f }
    // }});
    // boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
    //     { +0.000f, -207.000f }, { +0.000f, +0.000f }, { +50.000f, -18.320f }
    // }});
    // boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
    //     { +0.000f, -207.000f }, { 50.000f, -18.320f }, { +80.000f, -77.000f }
    // }});

    // // Boss Window
    // boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
    //     { +0.000f, -167.000f }, { -54.000f, -75.890f }, { -33.750f, -34.830f }
    // }});
    // boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
    //     { +0.000f, -207.000f }, { -33.750f, -34.830f }, { +0.000f, -22.000f }
    // }});
    // boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
    //     { +0.000f, -207.000f }, { +0.000f, -22.000f }, { +33.750f, -34.830f }
    // }});
    // boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
    //     { +0.000f, -207.000f }, { +33.750f, -34.830f }, { +54.000f, -75.890f }
    // }});

    // // Boss body shape
    // boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
    //     { +0.000f, -207.000f }, { -90.000f, -170.250f }, { -80.00, -76.94f }
    // }});
    // boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
    //     { +0.000f, -207.000f }, { 90.000f, -170.250f }, { +80.000f, -77.000f }
    // }});

    // Boss big claw
 
    // Creates our window system (constructor initializes GLFW)
    WindowSystem windowSystem;

    // Creates our renderer (constructor initializes GLEW)
    Renderer renderer(false);

    // Vertex Shader's GLSL code
    std::string vertexCode =
    "attribute vec3 position;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = transform * vec4(position, 1.0);\n"
    "}\n";

    // Fragment Shader's GLSL code
    std::string fragmentCode =
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n";

    // Creates the program we are going to use from our vertex and fragment shader's source code
    renderer.SetProgram(vertexCode, fragmentCode);

    // Creates the data that will be used for the GPU:
    Circle circle = Circle();

    // Stores the position of our pyramid (x and y)
    float tX = 0.0f, tY = 0.0f;

    // Stores the angle of our pyramid (in radians)
    float angle = 0.0f;

    // Stores the scale of our pyramid
    float scale = 1.0f;

    // Sets the callback function for when our windows system detects a mouse button input
    windowSystem.SetMouseButtonCallback(ProcessMouse);

    // Sets the callback function for when our windows system detects a key input
    windowSystem.SetKeyCallback(ProcessKey);

    // Shows our window
    windowSystem.Show();

    // Duration of the last frame in seconds.
    float deltaTime = 0.0f;

    // While our program isn't closed:
    while (!windowSystem.ShouldClose()) {

        // Gets the start time.
        uint64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        // Polls our window system for events
        windowSystem.PollEvents();

        // Clears our screen with a certain color
        renderer.Clear(Color::black);

        // TODO: Draw all shapes
        renderer.DrawShape2DCollection(ship, Color::white);

        // Swaps the old buffer for the new one
        windowSystem.SwapBuffers();

        // TODO: Process Input

        /*
        // Updates the scale (based on input)
        if(leftMousePressed)
            ;
        else if(rightMousePressed)
            ;

        // Updates the angle
        angle += 2.00f * deltaTime;

        // Updates the X position (based on input)
        if(rightPressed)
            ;
        else if(leftPressed)
            ;

        // Updates the Y position (based on input)
        if(upPressed)
            ;
        else if(downPressed)
            ;
        */

        // Gets the end time.
        uint64_t endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        
        // Calculates our frame time delta
        deltaTime = (endTime - startTime) / 1000.0f;

    }

    return EXIT_SUCCESS;

}
