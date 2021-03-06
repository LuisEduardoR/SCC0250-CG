// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/* para linux, instalar os pacotes libglfw3-dev mesa-common-dev libglew-dev */
/* para compilar no linux: make linux */

/* para windows, instalar o MSYS2 e as depedências:

    mingw-w64-x86_64-toolchain,
    mingw-w64-x86_64-glfw,
    mingw-w64-x86_64-glew,
    e mingw-w64-x86_64-glm

    adicionar "C:\msys64\mingw64\bin" ao PATH (se o MSYS2 foi instalado no local padrão)
*/
/* para compilar no windows: mingw32-make windows */


# include "Components/Camera.hpp"
# include "Input/Input.hpp"
# include "Math/Matrix4x4.hpp"
# include "Rendering/Renderer.hpp"
# include "WindowSystem/WindowSystem.hpp"

# include "Time/Time.hpp"
# include "Scene/GameScene.hpp"
# include "Physics/Collider.hpp"

# include <chrono>
# include <cstring>

# define DISPLAY_DELTA_TIME false

using namespace Adven;

void run(void) {

    // Creates our window system (initializes GLFW)
    WindowSystem::Init();

    // Creates our renderer (initializes GLEW)
    Renderer::Init();

    // Shows our window
    WindowSystem::Show();

    // Loads our scene (the scene handles most of the program)
    Scene::LoadScene<GameScene>();

    // While our program isn't closed:
    while (!WindowSystem::ShouldClose()) {

        // Gets the start time.
        uint64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        // Polls our window system for events
        WindowSystem::PollEvents();

        // Clears the color buffer
        Renderer::Clear(Color(0x1B, 0x18, 0x30));

        // Delete GameObjects marked for destruction.
        GameObject::DeletePending();

        // Run Start for all new GameObjects.
        Scene::currentScene->Start();

        // Checks for collision
        Collider::Update();

        // Check every frame for camera, because it might change.
        Camera* camera = Camera::MainCamera();
        // Renders skybox with custom view
        camera->RenderSkybox();
        // Set view matrix to camera's or identity in case camera has been deleted.
        Renderer::SetViewMatrix(camera ? camera->ViewMatrix() : Matrix4x4::Identity);

        // Updates the scene
        Scene::currentScene->VDrawUpdate();
        Scene::currentScene->VBlankUpdate();

        // Swaps the old buffers for the new ones
        WindowSystem::SwapBuffers();

        // Update input state.
        Input::Update();

        // Gets the end time.
        uint64_t endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        // Calculates our frame time delta
        Time::DeltaTime = (endTime - startTime) / 1000.0f;
        Time::Time += Time::DeltaTime;
        # if DISPLAY_DELTA_TIME
            std::cout << "DeltaTime: " << Time::DeltaTime << " FPS: " << 1.0f / Time::DeltaTime << "\n";
        # endif
    }

    // Finishes the program
    Renderer::Destroy();
    WindowSystem::Destroy();

}

auto PrintNestedException(const std::exception& e, std::size_t level = 0) -> void
{
	std::cerr << level << " exception: " << e.what() << '\n';

	if (const auto* systemError = dynamic_cast<const std::system_error*>(&e);
			systemError != nullptr && systemError->code())
	{
		std::cerr << level << " was caused by system error(Code "
			<< systemError->code().value();

		std::array<char, 1024> errorMsg{};
		int result = -1;//strerror_r(systemError->code().value(), errorMsg.data(), errorMsg.size());

		if (result == 0)
		{
				std::cerr << "): " << errorMsg.data() << '\n';
		}
		else
		{
			std::cerr << "): Failed to get error message for error code.\n";
		}
	}

	try
	{
		std::rethrow_if_nested(e);
	}
	catch(const std::exception& e)
	{
		PrintNestedException(e, level + 1);
	}
	catch(...)
	{
		std::cerr << level << " caught nested exception not derived from std::exception! \n";
	}
}

/// Techinically throwing exceptions from main is undefined behaviour (why???)
/// So catch them here and run the app code in another function.
auto main() -> int
{
	try
	{
		run();

        return EXIT_SUCCESS;
	}
	catch(std::exception& e)
	{
		std::cerr << "main(): Crashed with exception:\n";
		PrintNestedException(e);

		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::cerr << "main(): Crashed with exception not derived from std::exception! \n";
	}
}

