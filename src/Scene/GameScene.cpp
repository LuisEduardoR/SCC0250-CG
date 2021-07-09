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
# include "../Components/Moveable.hpp"
# include "../Components/Player.hpp"
# include "../Components/RendererComponent.hpp"
# include "../Components/TimedSpawner.hpp"
# include "../Components/ItemAnimator.hpp"
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

void GameScene::CreateStaticMesh(const Mesh& mesh, const Vector3& position, const Vector3& rotation) {
    
    GameObject& gameObject = AddGameObject({});
    gameObject.AddComponent<Transform> ( position, rotation, Vector3( 1.0f, 1.0f, 1.0f));
    gameObject.AddComponent<RendererComponent<Mesh>>(mesh);

}

void GameScene::CreateItem(const Mesh& mesh, const Vector3& position, const Vector3& rotation) {
    
    GameObject& gameObject = AddGameObject({});
    gameObject.AddComponent<Transform> ( position, rotation, Vector3( 1.0f, 1.0f, 1.0f));
    gameObject.AddComponent<RendererComponent<Mesh>>(mesh);
    gameObject.AddComponent<ItemAnimator>(0.15f, 0.50f);

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
    auto crawlerObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/crawler.obj");
    auto labTankObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/labtank.obj");
    auto tableObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/table.obj");
    auto kelpObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/kelp.obj");
    auto sceneryWallObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/scenery_wall.obj");
    auto scenerySandObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/scenery_sand.obj");
    auto sceneryRockObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/scenery_rock.obj");
    auto weaponObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/weapon.obj");
    auto armorObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/armor.obj");

    // Loads the textures.
    auto crawlerTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/Crawler.png");
    auto crawlerTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    crawlerTexture->UploadTexture(0, crawlerTextureFile);

    auto techAtlasTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/tech_ATLAS.png");
    auto techAtlasTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    techAtlasTexture->UploadTexture(0, techAtlasTextureFile);

    auto propsAtlasTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/props_ATLAS.png");
    auto propsAtlasTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    propsAtlasTexture->UploadTexture(0, propsAtlasTextureFile);

    auto outsideAtlasTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/outside-ATLAS.png");
    auto outsideAtlasTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    outsideAtlasTexture->UploadTexture(0, outsideAtlasTextureFile);
    
    auto wallTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/Wall.png");
    auto wallTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    wallTexture->UploadTexture(0, wallTextureFile);

    auto sandTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/Sand.png");
    auto sandTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    sandTexture->UploadTexture(0, sandTextureFile);

    auto rockTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/Rock.png");
    auto rockTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    rockTexture->UploadTexture(0, rockTextureFile);

    auto weaponTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/weapon.png");
    auto weaponTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    weaponTexture->UploadTexture(0, weaponTextureFile);

    auto armorTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/armor.png");
    auto armorTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    armorTexture->UploadTexture(0, armorTextureFile);
    
    // Creates the Crawler
    Mesh crawlerMesh { crawlerObj };
    crawlerMesh.SetTexture(crawlerTexture);
    CreateStaticMesh(crawlerMesh, Vector3{ 0.0f, 0.0f, 2.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the lab tank
    Mesh labTankMesh { labTankObj };
    labTankMesh.SetTexture(techAtlasTexture);
    CreateStaticMesh(labTankMesh, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the table
    Mesh tableMesh { tableObj };
    tableMesh.SetTexture(propsAtlasTexture);
    CreateStaticMesh(tableMesh, Vector3{ 2.0f, 0.0f, 0.0f }, Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f });

    // Creates the kelp
    Mesh kelpMesh { kelpObj };
    kelpMesh.SetTexture(outsideAtlasTexture);
    CreateStaticMesh(kelpMesh, Vector3{ -3.0f, 0.0f, 8.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the scenery wall
    Mesh sceneryWallMesh { sceneryWallObj };
    sceneryWallMesh.SetTexture(wallTexture);
    CreateStaticMesh(sceneryWallMesh, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the scenery sand
    Mesh scenerySandMesh { scenerySandObj };
    scenerySandMesh.SetTexture(sandTexture);
    CreateStaticMesh(scenerySandMesh, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the scenery rock
    Mesh sceneryRockMesh { sceneryRockObj };
    sceneryRockMesh.SetTexture(rockTexture);
    CreateStaticMesh(sceneryRockMesh, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the weapon
    Mesh weaponMesh { weaponObj };
    weaponMesh.SetTexture(weaponTexture);
    CreateItem(weaponMesh, Vector3{ 2.0f, 1.25f, 0.0f }, Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f });

    // Creates the armor
    Mesh armorMesh { armorObj };
    armorMesh.SetTexture(armorTexture);
    CreateItem(armorMesh, Vector3{ 3.00f, 0.25f, 6.00f }, Vector3{ 0.0f, 0.0f, 0.0f });


    // Creates the player
    GameObject& player = AddGameObject({});
    // Adds the necessary components
    player.AddComponent<Transform>(Vector3 { 0.0f, 2.5f, -5.0f });
    player.AddComponent<Moveable>();
    player.AddComponent<Player>();
    player.AddComponent<Camera>(true);

}
