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

# include "../Components/Shooter.hpp"
# include "../Components/Health.hpp"
# include "../Components/HealthBar.hpp"
# include "../Components/Camera.hpp"
# include "../Components/Player.hpp"
# include "../Components/Boss.hpp"
# include "../Components/Moveable.hpp"
# include "../Components/Transform.hpp"
# include "../Components/WrapAround.hpp"
# include "../Components/PlayerDeath.hpp"
# include "../Components/DestroyArea.hpp"
# include "../Components/DestroyOnDie.hpp"
# include "../Components/FollowObject.hpp"
# include "../Components/DamageOnContact.hpp"
# include "../Components/RendererComponent.hpp"
# include "../Math/Vector.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Physics/CircleCollider.hpp"
# include "../Rendering/Renderer.hpp"
# include "../Rendering/Geometry.hpp"
# include "../Rendering/PoissonDiscSampling.hpp"
# include "../Assets/AssetLoader.hpp"

using namespace Adven;

namespace
{

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

}

GameScene::GameScene()
{
    // Loads vertex and fragment shader's GLSL code 
    std::string vertexCode   = AssetLoader<std::string>::LoadAsset("./assets/vertex.glsl");
    std::string fragmentCode = AssetLoader<std::string>::LoadAsset("./assets/fragment.glsl");

    // Creates our shader from code
    Shader shader(vertexCode, fragmentCode);

    // Set the render program to our shader
    Renderer::SetProgram(shader);

    // Loads the models that will be used
    ShapeCollection shipModel     = AssetLoader<ShapeCollection>::LoadAsset("./assets/ship.asset");
    ShapeCollection ship2Model    = AssetLoader<ShapeCollection>::LoadAsset("./assets/ship2.asset");
    ShapeCollection bossModel     = AssetLoader<ShapeCollection>::LoadAsset("./assets/boss.asset");
    ShapeCollection asteroidModel = AssetLoader<ShapeCollection>::LoadAsset("./assets/asteroid.asset");
    ShapeCollection bulletModel   = AssetLoader<ShapeCollection>::LoadAsset("./assets/bullet.asset");
    ShapeCollection bBulletModel    = AssetLoader<ShapeCollection>::LoadAsset("./assets/bossBullet.asset");
    
    // Generates the sky and batchs it's shapes for performance
    ShapeBatch skyBatch(GenerateSkyModel());

    // Make a prefab. Prefabs are just normal gameobjects.
    // Though they don't need to be attached to a scene.
    // Use a shared_ptr so many components can keep a reference to the same prefab.
    auto bulletPrefab = std::make_shared<GameObject>();
    {
        bulletPrefab->AddComponent<Transform>(Vector3(), Vector3());
        bulletPrefab->AddComponent<RendererComponent<ShapeBatch>>(bulletModel);
        bulletPrefab->AddComponent<Moveable>(Vector3 { 0.0f, 1.2f, 0.0f });
        bulletPrefab->AddComponent<CircleCollider>( 0.09f, true );
        bulletPrefab->AddComponent<DamageOnContact>(10);
        bulletPrefab->AddComponent<DestroyArea>(
            Vector3{ -1.0f, -1.0f, -1.0f },
            Vector3{ 1.0f, 1.0f, 1.0f}
        );
        // bulletPrefab->AddComponent<DestroyArea>(
        //     Vector3{ -100.0f, -100.0f, -100.0f },
        //     Vector3{ 100.0f, 100.0f, 100.0f}
        // );
    }

    auto bossBulletPrefab = std::make_shared<GameObject>();
    {
        bossBulletPrefab->AddComponent<Transform>(Vector3(), Vector3());
        bossBulletPrefab->AddComponent<RendererComponent<ShapeBatch>>(bBulletModel);
        bossBulletPrefab->AddComponent<Moveable>(Vector3 { 0.0f, 1.2f, 0.0f });
        bossBulletPrefab->AddComponent<CircleCollider>( 0.05f, true );
        bossBulletPrefab->AddComponent<DamageOnContact>(10);
        bossBulletPrefab->AddComponent<DestroyArea>(
            Vector3{ -1.0f, -1.0f, -1.0f },
            Vector3{ 1.0f, 1.0f, 1.0f}
        );
        // bossBulletPrefab->AddComponent<DestroyArea>(
        //     Vector3{ -100.0f, -100.0f, -100.0f },
        //     Vector3{ 100.0f, 100.0f, 100.0f}
        // );
    }

    GameObject& camera = AddGameObject({});
    camera.AddComponent<Transform>();
    camera.AddComponent<Camera>(true);

    // Creates the sky
    GameObject sky{};
    sky.AddComponent<Transform>(Vector3 { -1.0f, -1.0f, 0.0f });
    sky.AddComponent<RendererComponent<ShapeBatch>>(skyBatch);
    camera.AddChild(std::move(sky));

    // Creates the player
    GameObject& player = AddGameObject({});
    player.AddComponent<Transform>(
        Vector3{ 0.0f, -0.3f, 0.0f },
        Vector3{},
        Vector3{ 0.3f, 0.3f, 1.0f });
    player.AddComponent<Moveable>();
    player.AddComponent<RendererComponent<ShapeCollection>>(ship2Model);
    player.AddComponent<CircleCollider>(0.66f * 0.3f, false);
    auto& playerHealth = player.AddComponent<Health>(100);
    player.AddComponent<Player>();
    player.AddComponent<PlayerDeath>();
    player.AddComponent<Shooter>(bulletPrefab, Vector3{ -0.1f, 0.86f, 0.0f }, 0.0f, 0.2f);
    player.AddComponent<Shooter>(bulletPrefab, Vector3{ 0.1f, 0.86f, 0.0f }, 0.0f, 0.2f);
    player.AddComponent<WrapAround>();

    GameObject& healthBar = AddGameObject({});
    healthBar.AddComponent<Transform>(Vector3{ -0.65f, -0.90f, 0.5f });
    healthBar.AddComponent<HealthBar>(playerHealth, Vector2{ -0.3f, -0.025f }, Vector2{ 0.3f, 0.025f });
    Quad barQuad{};
    barQuad.color = Color::red;
    healthBar.AddComponent<RendererComponent<Quad>>(barQuad);
    
    // Gets random points for the asteroids
    std::vector<Vector2> asteroidPoints{
        amn::PoissonDiscSampler::GeneratePoints(0.3f, { 2.0f, 2.0f }, 5)
    };
	std::random_device rd;
	std::mt19937 rng{ rd() };
    for (const Vector2& point: asteroidPoints)
    {

        // Gets a random angle and scale
        float angle{ 2.0f * CONST_PI
                     * std::uniform_real_distribution<float>{ 0.0f, 1.0f }(rng) };
        float scale{ std::uniform_real_distribution<float>{ 0.02f, 0.07f }(rng) };
        Vector3 speed
        {
            std::uniform_real_distribution<float>{ -0.05f, 0.05f }(rng),
            std::uniform_real_distribution<float>{ -0.05f, 0.05f }(rng),
            0.0f,
        };

        // Creates an asteroid
        GameObject& asteroid = AddGameObject({});
        asteroid.AddComponent<Transform>(
            Vector3{ point } - Vector3{ 1.0f, 1.0f, 0.0f },
            Vector3{ 0.0f, 0.0f, angle },
            Vector3{ scale, scale, 1.0f });
        asteroid.AddComponent<RendererComponent<ShapeCollection>>(asteroidModel);
        asteroid.AddComponent<Moveable>(speed);
        asteroid.AddComponent<CircleCollider>(scale, true);
        asteroid.AddComponent<DamageOnContact>(10);
        asteroid.AddComponent<WrapAround>();
    }

    // Creates the boss
    GameObject& boss = AddGameObject({});

    boss.AddComponent<Transform>(
        Vector3{ 0.0f, 0.4f, 0.0f },
        Vector3{ 0.0f, 0.0f, CONST_PI },
        Vector3{ 0.0025f, 0.0025f, 0.0f });
    boss.AddComponent<Moveable>();
    boss.AddComponent<RendererComponent<ShapeCollection>>(bossModel);
    boss.AddComponent<Health>(1000);
    boss.AddComponent<CircleCollider>(0.3f, true);
    boss.AddComponent<Shooter>(bossBulletPrefab, Vector3{ 268.0f, 140.0f, 0.0f }, 0.0f, 2.0f);
    boss.AddComponent<Shooter>(bossBulletPrefab, Vector3{ -268.0f, 140.0f, 0.0f }, 1.0f, 2.0f);
    boss.AddComponent<Boss>(0.7f, 0.1f);
    boss.AddComponent<DestroyOnDie>();

    // Creates the second ship
    GameObject& ship2 = AddGameObject({});

    ship2.AddComponent<Transform>(
        Vector3{ -0.7f, -0.3f, 0.0f },
        Vector3{},
        Vector3{ 0.3f, 0.3f, 1.0f });
    ship2.AddComponent<Moveable>();
    ship2.AddComponent<RendererComponent<ShapeCollection>>(shipModel);
    ship2.AddComponent<CircleCollider>(0.7f * 0.3f, true);
    ship2.AddComponent<Health>(50);
    ship2.AddComponent<DestroyOnDie>();
    /* ship2.AddComponent<WrapAround>(); */

}
