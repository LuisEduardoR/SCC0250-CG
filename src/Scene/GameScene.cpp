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
# include "../Components/Shooter.hpp"
# include "../Components/Health.hpp"
# include "../Components/HealthBar.hpp"
# include "../Components/Camera.hpp"
# include "../Components/EnemyShip.hpp"
# include "../Components/Player.hpp"
# include "../Components/Boss.hpp"
# include "../Components/Moveable.hpp"
# include "../Components/Transform.hpp"
# include "../Components/WrapAround.hpp"
# include "../Components/ExitOnDeath.hpp"
# include "../Components/DestroyArea.hpp"
# include "../Components/DestroyOnDie.hpp"
# include "../Components/SplitOnDie.hpp"
# include "../Components/FollowObject.hpp"
# include "../Components/DamageOnContact.hpp"
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
        AsteroidLayer, 
        PlayerLayer,
        PlayerBulletLayer,
        EnemyLayer,
        EnemyBulletLayer,
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
        { true, true, true, true, true, true },     // Default
        { true, false, true, true, true, true },    // Asteroid
        { true, true, false, false, true, true },   // Player
        { true, true, false, false, true, true },   // PlayerBullet
        { true, true, true, true, false, false },   // Enemy
        { true, true, true, true, false, false },   // EnemyBullet
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

	float aspect = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
    Renderer::SetProjectionMatrix(Matrix4x4::Perspective(CONST_PI / 2.0f, aspect, 1.0f, 100.0f));
    /* Renderer::SetProjectionMatrix(Matrix4x4::Identity); */

    // Loads the models that will be used
    ShapeCollection shipModel     = AssetLoader<ShapeCollection>::LoadAsset("./assets/ship.asset");
    ShapeCollection ship2Model    = AssetLoader<ShapeCollection>::LoadAsset("./assets/ship2.asset");
    ShapeCollection bossModel     = AssetLoader<ShapeCollection>::LoadAsset("./assets/boss.asset");
    ShapeCollection asteroidModel = AssetLoader<ShapeCollection>::LoadAsset("./assets/asteroid.asset");
    ShapeCollection bulletModel   = AssetLoader<ShapeCollection>::LoadAsset("./assets/bullet.asset");
    ShapeCollection bBulletModel    = AssetLoader<ShapeCollection>::LoadAsset("./assets/bossBullet.asset");
    
    // Generates the sky and batchs it's shapes for performance
    ShapeBatch skyBatch(GenerateSkyModel());

    auto cubeObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/cube.obj");
    auto texture = AssetLoader<Texture2D>::LoadAsset(
            "./assets/kenney_prototypetextures/PNG/Purple/texture_05.png");

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

    // Make a prefab. Prefabs are just normal gameobjects.
    // Though they don't need to be attached to a scene.
    // Use a shared_ptr so many components can keep a reference to the same prefab.
    // Creates a prefab for the bullet
    auto bulletPrefab = std::make_shared<GameObject>();
    {
        // Adds the necessary components
        bulletPrefab->AddComponent<Transform>(Vector3{ 0.0f, 0.0f, 0.3f });
        bulletPrefab->AddComponent<RendererComponent<ShapeBatch>>(bulletModel);
        bulletPrefab->AddComponent<Moveable>(Vector3 { 0.0f, 1.2f, 0.0f });
        bulletPrefab->AddComponent<CircleCollider>( 0.09f, PlayerBulletLayer, true );
        bulletPrefab->AddComponent<DamageOnContact>(10);
        bulletPrefab->AddComponent<DestroyArea>(
            Vector3{ -1.0f, -1.0f, -1.0f },
            Vector3{ 1.0f, 1.0f, 1.0f}
        );
    }

    // Creates a prefab for the enemy bullet
    auto enemyBulletPrefab = std::make_shared<GameObject>();
    {
        // Adds the necessary components
        enemyBulletPrefab->AddComponent<Transform>(
            Vector3{ 0.0f, 0.0f, 0.3f },
            Vector3{},
            Vector3{ 0.005f, 0.005f, 1.0f }
        );
        enemyBulletPrefab->AddComponent<RendererComponent<ShapeBatch>>(bBulletModel);
        enemyBulletPrefab->AddComponent<Moveable>(Vector3 { 0.0f, 1.2f, 0.0f });
        enemyBulletPrefab->AddComponent<CircleCollider>( 0.05f, EnemyBulletLayer, true );
        enemyBulletPrefab->AddComponent<DamageOnContact>(10);
        enemyBulletPrefab->AddComponent<DestroyArea>(
            Vector3{ -1.0f, -1.0f, -1.0f },
            Vector3{ 1.0f, 1.0f, 1.0f}
        );
    }

    // Creates a prefab for the boss bullet
    auto bossBulletPrefab = std::make_shared<GameObject>();
    {
        // Adds the necessary components
        bossBulletPrefab->AddComponent<Transform>(Vector3{ 0.0f, 0.0f, 0.3f });
        bossBulletPrefab->AddComponent<RendererComponent<ShapeBatch>>(bBulletModel);
        bossBulletPrefab->AddComponent<Moveable>(Vector3 { 0.0f, 1.2f, 0.0f });
        bossBulletPrefab->AddComponent<CircleCollider>( 0.05f, EnemyBulletLayer, true );
        bossBulletPrefab->AddComponent<DamageOnContact>(10);
        bossBulletPrefab->AddComponent<DestroyArea>(
            Vector3{ -1.0f, -1.0f, -1.0f },
            Vector3{ 1.0f, 1.0f, 1.0f}
        );
    }

    // Creates the boss
    auto bossPrefab = std::make_shared<GameObject>();
    {
        // Adds the necessary components
        bossPrefab->AddComponent<Transform>(
            Vector3{ 0.0f, 0.4f, 0.5f },
            Vector3{ 0.0f, 0.0f, CONST_PI },
            Vector3{ 0.0025f, 0.0025f, 0.0f });
        bossPrefab->AddComponent<Moveable>();
        bossPrefab->AddComponent<RendererComponent<ShapeCollection>>(bossModel);
        bossPrefab->AddComponent<Health>(1000);
        bossPrefab->AddComponent<CircleCollider>(0.3f, EnemyLayer, true);
        bossPrefab->AddComponent<Shooter>(bossBulletPrefab, Vector3{ 268.0f, 140.0f, 0.0f }, 0.0f, 2.0f);
        bossPrefab->AddComponent<Shooter>(bossBulletPrefab, Vector3{ -268.0f, 140.0f, 0.0f }, 1.0f, 2.0f);
        bossPrefab->AddComponent<Boss>(0.7f, 0.1f);
        bossPrefab->AddComponent<ExitOnDeath>("GAMEOVER!\nYou won!\n");
        bossPrefab->AddComponent<DestroyOnDie>();
    }

    // Creates a prefab for small asteroids
    auto smallAsteroidPrefab = std::make_shared<GameObject>();
    {
        // Adds the necessary components
        smallAsteroidPrefab->AddComponent<Transform>(Vector3{ 0.0f, 0.4f, 0.4f });
        smallAsteroidPrefab->AddComponent<RendererComponent<ShapeCollection>>(asteroidModel);
        smallAsteroidPrefab->AddComponent<Moveable>();
        smallAsteroidPrefab->AddComponent<CircleCollider>(0.1f, AsteroidLayer, true);
        smallAsteroidPrefab->AddComponent<DamageOnContact>(5);
        smallAsteroidPrefab->AddComponent<WrapAround>();
    }

    // Creates the camera
    GameObject& camera = AddGameObject({});
    // Adds the necessary components
    camera.AddComponent<Transform>(Vector3 { 0.0f, 0.0f, -5.0f });
    camera.AddComponent<Camera>(true);

    // Creates the sky
    GameObject sky{};
    // Adds the necessary components
    sky.AddComponent<Transform>(Vector3 { -1.0f, -1.0f, 1.0f });
    sky.AddComponent<RendererComponent<ShapeBatch>>(skyBatch);

    // Attaches the sky to the camera so they move together
    camera.AddChild(std::move(sky));

    // Creates the player
    GameObject& player = AddGameObject({});
    // Adds the necessary components
    auto& playerTransform = player.AddComponent<Transform>(
        Vector3{ 0.0f, -0.3f, 0.5f },
        Vector3{},
        Vector3{ 0.3f, 0.3f, 1.0f });
    player.AddComponent<Moveable>();
    player.AddComponent<RendererComponent<ShapeCollection>>(ship2Model);
    player.AddComponent<CircleCollider>(0.66f * 0.3f, PlayerLayer, false);
    auto& playerHealth = player.AddComponent<Health>(200);
    player.AddComponent<Player>();
    player.AddComponent<ExitOnDeath>("GAMEOVER!\nYou died!\n");
    player.AddComponent<Shooter>(bulletPrefab, Vector3{ -0.1f, 0.86f, 0.0f }, 0.0f, 0.2f);
    player.AddComponent<Shooter>(bulletPrefab, Vector3{ 0.1f, 0.86f, 0.0f }, 0.0f, 0.2f);
    player.AddComponent<WrapAround>();

    // Creates the health bar
    GameObject& healthBar = AddGameObject({});
    // Adds the necessary components
    healthBar.AddComponent<Transform>(Vector3{ -0.65f, -0.90f, 0.0f });
    healthBar.AddComponent<HealthBar>(playerHealth, Vector2{ -0.3f, -0.025f }, Vector2{ 0.3f, 0.025f });
    Quad barQuad{};
    barQuad.color = Color::red;
    healthBar.AddComponent<RendererComponent<Quad>>(barQuad);

    // Creates a prefab for the enemy ship
    auto enemyShipPrefab = std::make_shared<GameObject>();
    {
        // Adds the necessary components
        enemyShipPrefab->AddComponent<Transform>(
            Vector3{ -0.7f, 0.5f, 0.5f },
            Vector3{},
            Vector3{ 0.15f, 0.15f, 1.0f });
        enemyShipPrefab->AddComponent<Moveable>(Vector3{ 0.5f, 0.0f, 0.0f });
        enemyShipPrefab->AddComponent<RendererComponent<ShapeCollection>>(shipModel);
        enemyShipPrefab->AddComponent<CircleCollider>(0.7f * 0.15f, EnemyLayer, true);
        enemyShipPrefab->AddComponent<Health>(100);
        enemyShipPrefab->AddComponent<Shooter>(enemyBulletPrefab, Vector3{ -0.354f, 0.264f, 0.0f }, 0.0f, 0.5f);
        enemyShipPrefab->AddComponent<Shooter>(enemyBulletPrefab, Vector3{ 0.354f, 0.264f, 0.0f }, 0.0f, 0.5f);
        enemyShipPrefab->AddComponent<EnemyShip>(&playerTransform);
        enemyShipPrefab->AddComponent<WrapAround>();
        enemyShipPrefab->AddComponent<DestroyOnDie>();
    }
    
    // Gets random points for the asteroids
    std::vector<Vector2> asteroidPoints{
        amn::PoissonDiscSampler::GeneratePoints(0.3f, { 2.0f, 2.0f }, 5)
    };

    // Creates a random number geeration to also randomize scale and rotation
	std::random_device rd;
	std::mt19937 rng{ rd() };

    // Adds al the asteroids
    for (const Vector2& point: asteroidPoints)
    {

        // Gets a random angle and scale
        float angle{ 2.0f * CONST_PI
                     * std::uniform_real_distribution<float>{ 0.0f, 1.0f }(rng) };
        float scale{ std::uniform_real_distribution<float>{ 0.05f, 0.13f }(rng) };
        Vector3 speed
        {
            std::uniform_real_distribution<float>{ -0.05f, 0.05f }(rng),
            std::uniform_real_distribution<float>{ -0.05f, 0.05f }(rng),
            0.0f,
        };

        // Creates an asteroid
        GameObject& asteroid = AddGameObject({});
        // Adds the necessary components
        asteroid.AddComponent<Transform>(
            Vector3{ point, 0.4f } - Vector3{ 1.0f, 1.0f, 0.0f },
            Vector3{ 0.0f, 0.0f, angle },
            Vector3{ scale, scale, 1.0f });
        asteroid.AddComponent<RendererComponent<ShapeCollection>>(asteroidModel);
        asteroid.AddComponent<Moveable>(speed);
        asteroid.AddComponent<CircleCollider>(scale, AsteroidLayer, true);
        asteroid.AddComponent<Health>(5);
        asteroid.AddComponent<DamageOnContact>(10);
        asteroid.AddComponent<WrapAround>();
        asteroid.AddComponent<SplitOnDie>(smallAsteroidPrefab);
    }

    // Creates the enemy spawner and adds the TimedSpawner component
    GameObject& enemySpawner = AddGameObject({});
    enemySpawner.AddComponent<TimedSpawner>(enemyShipPrefab, 10.0f); 

    // Creates the enemy spawner and adds the TimedSpawner component
    GameObject& bossSpawner = AddGameObject({});
    bossSpawner.AddComponent<TimedSpawner>(bossPrefab, 30.0f); 

}
