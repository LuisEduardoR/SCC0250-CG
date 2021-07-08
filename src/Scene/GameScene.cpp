// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "GameScene.hpp"

# include <memory>
# include <vector>
# include <random>

# include "../Assets/AssetLoader.hpp"
# include "../Assets/Texture2D.hpp"
# include "../Assets/WavefrontObject.hpp"
# include "../Components/Camera.hpp"
# include "../Components/EnemyShip.hpp"
# include "../Components/Transform.hpp"
# include "../Components/DamageOnContact.hpp"
# include "../Components/Moveable.hpp".hpp"
# include "../Components/Player.hpp"
# include "../Components/RendererComponent.hpp"
# include "../Components/TimedSpawner.hpp"
# include "../Math/Vector.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Physics/CircleCollider.hpp"
# include "../Rendering/Renderer.hpp"
# include "../Rendering/Geometry.hpp"
# include "../Rendering/PoissonDiscSampling.hpp"
# include "../Rendering/TextureObject.hpp"
# include "../WindowSystem/WindowSystem.hpp"

using namespace Adven;

namespace
{

    // Generates random points to be used on the sky
    auto GenerateSkyModel() -> ShapeCollection
    {
        
        std::vector<Vector2> skyPoints {
            amn::PoissonDiscSampler::GeneratePoints(0.02f, { 2.0f, 2.0f }, 5)
        };

        ShapeCollection skyModel{ new std::vector<std::unique_ptr<Shape>>{} };

        for (Vector2 point : skyPoints)
        {
            skyModel->push_back(std::unique_ptr<Point>{ new Point{
                point, Color::white
            }});
        }

        return skyModel;

    }
    
    // Collision layer used by the scene
    enum CollisionLayers : Collider::Layer
    {
        DefaultLayer,
        PlayerLayer,
    };

}

// Creates all the objects and adds all the components necessary to run the scene
// The rest will be executed via Scene::VDrawUpdate() and Scene::VBlankUpdate()
// that will update each GameObject and it's Components to execute the game. This
// functions are executed on this scene by the main loop.
GameScene::GameScene()
{

    // Matrix containing which layers collide with eachother
    std::vector<std::vector<bool>> collisionLayers
    {
        { true, true },     // Default
        { true, false },    // Player
    };

    // Sets the collision layers of this scene
    Collider::GetSceneData(*this).collisionLayers = std::move(collisionLayers);

    // Loads vertex and fragment shader's GLSL code 
    std::string vertexCode   = AssetLoader<std::string>::LoadAsset("./assets/vertex.glsl");
    std::string fragmentCode = AssetLoader<std::string>::LoadAsset("./assets/fragment.glsl");

    // Creates our shader from code
    Shader shader(vertexCode, fragmentCode);

    // Set the render program to our shader
    Renderer::SetProgram(shader);

    // Applies the projection matrix.
	float aspect = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
    Renderer::SetProjectionMatrix(Matrix4x4::Perspective(CONST_PI / 2.0f, aspect, 1.0f, 100.0f));

    // Loads the models.
    auto cubeObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/crawler.obj");

    // Loads the textures.
    auto texture = AssetLoader<Texture2D>::LoadAsset(
            "./assets/Crawler.png");

    auto testTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    testTexture->UploadTexture(0, texture);
    
    Mesh cubeMesh{ cubeObj };
    cubeMesh.SetTexture(testTexture);
    
    GameObject& cube = AddGameObject({});
    cube.AddComponent<Transform>(
            Vector3{ 0.0f, 0.0f, 2.0f },
            Vector3{ 0.0f, CONST_PI / 4.0f, 0.0f },
            Vector3{ 0.3f, 0.3f, 0.3f });
    cube.AddComponent<RendererComponent<Mesh>>(cubeMesh);

    // Creates the player
    GameObject& player = AddGameObject({});
    // Adds the necessary components
    player.AddComponent<Transform>(Vector3 { 0.0f, 0.0f, -5.0f });
    player.AddComponent<Moveable>();
    player.AddComponent<Player>();
    player.AddComponent<Camera>(true);

}
