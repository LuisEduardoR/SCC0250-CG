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

# include "../Components/Camera.hpp"
# include "../Components/Player.hpp"
# include "../Components/Moveable.hpp"
# include "../Components/Transform.hpp"
# include "../Components/Health.hpp"
# include "../Components/DestroyOnDie.hpp"
# include "../Components/DamageOnContact.hpp"
# include "../Components/ShapeRenderer.hpp"
# include "../Math/Vector.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Physics/CircleCollider.hpp"
# include "../Rendering/Geometry2D.hpp"
# include "../Rendering/PoissonDiscSampling.hpp"
# include "../Assets/AssetLoader.hpp"

using namespace Adven;

namespace
{

auto GenerateSkyModel() -> Shape2DCollection
{
    std::vector<Vector2> skyPoints{
        amn::PoissonDiscSampler::GeneratePoints(0.02f, { 2.0f, 2.0f }, 5)
    };

    Shape2DCollection skyModel{ new std::vector<std::unique_ptr<Shape2D>>{} };

    for (Vector2 point : skyPoints)
    {
        skyModel->push_back(std::unique_ptr<Point>{ new Point{
            point, Color::white
        }});
    }

    return skyModel;
}

}

GameScene::GameScene()
{
    // Loads vertex and fragment shader's GLSL code 
    std::string vertexCode = AssetLoader<std::string>::LoadAsset("./assets/vertex.glsl");
    std::string fragmentCode = AssetLoader<std::string>::LoadAsset("./assets/fragment.glsl");

    // Creates our shader from code
    Shader shader(vertexCode, fragmentCode);

    // Set the render program to our shader
    Renderer::SetProgram(shader);

    Shape2DCollection shipModel = AssetLoader<Shape2DCollection>::LoadAsset("./assets/ship.asset");
    Shape2DCollection bossModel = AssetLoader<Shape2DCollection>::LoadAsset("./assets/boss.asset");
    Shape2DCollection ship2Model = AssetLoader<Shape2DCollection>::LoadAsset("./assets/ship2.asset");
    Shape2DCollection asteroidModel = AssetLoader<Shape2DCollection>::LoadAsset("./assets/asteroid.asset");
    Shape2DCollection bulletModel = AssetLoader<Shape2DCollection>::LoadAsset("./assets/bullet.asset");
    
    Shape2DCollection skyModel = GenerateSkyModel();

    // Make a prefab. Prefabs are just normal gameobjects.
    // Though they don't need to be attached to a scene.
    // Use a shared_ptr so many components can keep a reference to the same prefab.
    auto bulletPrefab = std::make_shared<GameObject>();
    {
        bulletPrefab->AddComponent<Transform>(Vector3(), Vector3());
        bulletPrefab->AddComponent<ShapeRenderer>(bulletModel);
        bulletPrefab->AddComponent<Moveable>();
        bulletPrefab->AddComponent<CircleCollider>( 0.09f, true );
        bulletPrefab->AddComponent<DamageOnContact>(10);
    }

    GameObject& sky = AddGameObject({});
    sky.AddComponent<Transform>(Vector3 { -1.0f, -1.0f, 0.0f });
    sky.AddComponent<ShapeRenderer>(skyModel);

    std::vector<Vector2> asteroidPoints{
        amn::PoissonDiscSampler::GeneratePoints(0.2f, { 2.0f, 2.0f }, 5)
    };
	std::random_device rd;
	std::mt19937 rng{ rd() };
    for (const Vector2& point: asteroidPoints)
    {
        float angle{ 2.0f * CONST_PI
                     * std::uniform_real_distribution<float>{ 0.0f, 1.0f }(rng) };
        float scale{ std::uniform_real_distribution<float>{ 0.02f, 0.07f }(rng) };

        GameObject& asteroid = AddGameObject({});
        asteroid.AddComponent<Transform>(
            Vector3{ point } - Vector3{ 1.0f, 1.0f, 0.0f },
            Vector3{ 0.0f, 0.0f, angle },
            Vector3{ scale, scale, 1.0f });
        asteroid.AddComponent<ShapeRenderer>(asteroidModel);
    }

    GameObject& player = AddGameObject({});

    player.AddComponent<Transform>(
        Vector3{ 0.0f, -0.3f, 0.0f },
        Vector3{},
        Vector3{ 0.3f, 0.3f, 1.0f });
    player.AddComponent<Moveable>();
    player.AddComponent<ShapeRenderer>(ship2Model);
    player.AddComponent<CircleCollider>(0.66f * 0.3f, false);
    player.AddComponent<Health>(100);
    player.AddComponent<Player>(
        bulletPrefab,
        std::array<Vector3, 2>{{ { -0.1f, 0.86f, 0.0f }, { 0.1f, 0.86f, 0.0f } }}
    );
    player.AddComponent<Camera>(true);
    player.AddComponent<DestroyOnDie>();

    GameObject& boss = AddGameObject({});

    boss.AddComponent<Transform>(
        Vector3{ 0.0f, 0.4f, 0.0f },
        Vector3{ 0.0f, 0.0f, CONST_PI },
        Vector3{ 0.0025f, 0.0025f, 0.0f });
    boss.AddComponent<Moveable>();
    boss.AddComponent<ShapeRenderer>(bossModel);
    boss.AddComponent<Health>(20);
    boss.AddComponent<CircleCollider>(0.3f, false);
    boss.AddComponent<DestroyOnDie>();

    GameObject& ship2 = AddGameObject({});

    ship2.AddComponent<Transform>(
        Vector3{ -0.7f, -0.3f, 0.0f },
        Vector3{},
        Vector3{ 0.3f, 0.3f, 1.0f });
    ship2.AddComponent<Moveable>();
    ship2.AddComponent<ShapeRenderer>(shipModel);
    ship2.AddComponent<CircleCollider>(0.7f * 0.3f, false);
    ship2.AddComponent<Health>(50);
    ship2.AddComponent<DestroyOnDie>();
}
