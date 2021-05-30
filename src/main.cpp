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

# include <cstddef>
# include <iostream>
# include <cmath>
# include <chrono>
# include <thread>
# include <set>

# include "Collider2D.hpp"
# include "Transform.hpp"
# include "Vector.hpp"
# include "WindowSystem.hpp"
# include "Renderer.hpp"
# include "Shader.hpp"
# include "Color.hpp"
# include "Geometry.hpp"
# include "Object2D.hpp"
# include "Matrix4x4.hpp"
# include "TestScene.hpp"
# include "adven/Collider.hpp"
# include "Time.hpp"
# include "adven/Scene.hpp"

using namespace Adven;

int main(void) {

    // Creates our window system (initializes GLFW)
    WindowSystem::Init();

    // Initializes the renderer (initializes GLEW)
    Renderer::Init();

    // Shows our window
    WindowSystem::Show();

    // Loads our scene (the scene handles most of the program)
    Scene::LoadScene<TestScene>();
    Scene::currentScene->Start();

    // While our program isn't closed:
    while (!WindowSystem::ShouldClose()) {

        // Gets the start time.
        uint64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        // Polls our window system for events
        WindowSystem::PollEvents();

        Renderer::Clear(Color(0x1B, 0x18, 0x30));

        Adven::Collider::Update();
        Scene::currentScene->VDrawUpdate();
        Scene::currentScene->VBlankUpdate();

        // Swaps the old buffer for the new one
        WindowSystem::SwapBuffers();

        // Gets the end time.
        uint64_t endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        
        // Calculates our frame time delta
        Time::DeltaTime = (endTime - startTime) / 1000.0f;

    }

    // Finishes the program
    Renderer::Destroy();
    WindowSystem::Destroy();

    return EXIT_SUCCESS;

}
