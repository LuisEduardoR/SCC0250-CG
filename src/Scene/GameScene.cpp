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
# include "../Components/Transform.hpp"
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

// Creates a static mesh on the current scene
void GameScene::CreateStaticMesh(const Mesh& mesh, std::shared_ptr<Shader> shader, const Vector3& position, const Vector3& rotation) {
    
    GameObject& gameObject = AddGameObject({});
    gameObject.AddComponent<Transform> ( position, rotation, Vector3( 1.0f, 1.0f, 1.0f));
    gameObject.AddComponent<RendererComponent<Mesh>>(mesh, shader);

}

// Creates an item on the current scene
void GameScene::CreateItem(const Mesh& mesh, std::shared_ptr<Shader> shader, const Vector3& position, const Vector3& rotation) {
    
    GameObject& gameObject = AddGameObject({});
    gameObject.AddComponent<Transform> ( position, rotation, Vector3( 1.0f, 1.0f, 1.0f));
    gameObject.AddComponent<RendererComponent<Mesh>>(mesh, shader);
    // Items have an special animation.
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

    // Loads default shader's vertex and fragment GLSL code and creates it 
    std::string defaultVertex   = AssetLoader<std::string>::LoadAsset("./assets/defaultVertex.glsl");
    std::string defaultFragment = AssetLoader<std::string>::LoadAsset("./assets/defaultFragment.glsl");
    auto defaultShader       = std::make_shared<Shader>(defaultVertex, defaultFragment);

    // Loads skybox shader's vertex and fragment GLSL code and creates it
    std::string skyboxVertex   = AssetLoader<std::string>::LoadAsset("./assets/skyboxVertex.glsl");
    std::string skyboxFragment   = AssetLoader<std::string>::LoadAsset("./assets/skyboxFragment.glsl");
    auto skyboxShader        = std::make_shared<Shader>(skyboxVertex, skyboxFragment);
 
    // Loads the models ===============================================
    auto cubeObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/cube.obj");
    auto crawlerObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/crawler.obj");
    auto labTankObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/labtank.obj");
    auto tableObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/table.obj");
    auto kelpObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/kelp.obj");
    auto rockObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/rock.obj");
    auto sceneryWallObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/sceneryWall.obj");
    auto sceneryBeamObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/sceneryBeam.obj");
    auto sceneryConcreteObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/sceneryConcrete.obj");
    auto scenerySandObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/scenerySand.obj");
    auto sceneryRockObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/sceneryRock.obj");
    auto weaponObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/weapon.obj");
    auto armorObj = AssetLoader<WavefrontObject>::LoadAsset("./assets/armor.obj");

    // Loads the textures =============================================
    std::array<Texture2D, 6> skybox = 
    {{
        AssetLoader<Texture2D>::LoadAsset("./assets/skybox/underwater/uw_ft.jpg"),
        AssetLoader<Texture2D>::LoadAsset("./assets/skybox/underwater/uw_bk.jpg"),
        AssetLoader<Texture2D>::LoadAsset("./assets/skybox/underwater/uw_up.jpg"),
        AssetLoader<Texture2D>::LoadAsset("./assets/skybox/underwater/uw_dn.jpg"),
        AssetLoader<Texture2D>::LoadAsset("./assets/skybox/underwater/uw_rt.jpg"),
        AssetLoader<Texture2D>::LoadAsset("./assets/skybox/underwater/uw_lf.jpg")
    }};
    auto skyboxTexture = std::make_shared<TextureObject>(TextureObject::Type::TextureCubeMap);
    skyboxTexture->UploadTexture(0, skybox);
    
    auto crawlerTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/crawler.png");
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
    
    auto wallTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/wall.png");
    auto wallTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    wallTexture->UploadTexture(0, wallTextureFile);

    auto beamTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/beam.png");
    auto beamTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    beamTexture->UploadTexture(0, beamTextureFile);

    auto concreteTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/concrete.png");
    auto concreteTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    concreteTexture->UploadTexture(0, concreteTextureFile);

    auto sandTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/sand.png");
    auto sandTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    sandTexture->UploadTexture(0, sandTextureFile);

    auto rockTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/rock.png");
    auto rockTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    rockTexture->UploadTexture(0, rockTextureFile);

    auto weaponTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/weapon.png");
    auto weaponTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    weaponTexture->UploadTexture(0, weaponTextureFile);

    auto armorTextureFile = AssetLoader<Texture2D>::LoadAsset("./assets/armor.png");
    auto armorTexture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
    armorTexture->UploadTexture(0, armorTextureFile);
    
    // Creates the GameObjects ========================================

    // Creates the Crawler
    Mesh crawlerMesh { crawlerObj };
    crawlerMesh.SetTexture(crawlerTexture);
    CreateStaticMesh(crawlerMesh, defaultShader, Vector3{ 0.0f, 0.0f, 2.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the lab tank
    Mesh labTankMesh { labTankObj };
    labTankMesh.SetTexture(techAtlasTexture);
    CreateStaticMesh(labTankMesh, defaultShader, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the table
    Mesh tableMesh { tableObj };
    tableMesh.SetTexture(propsAtlasTexture);
    CreateStaticMesh(tableMesh, defaultShader, Vector3{ 2.0f, 0.0f, 0.0f }, Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f });

    // Creates the kelp
    Mesh kelpMesh { kelpObj };
    kelpMesh.SetTexture(outsideAtlasTexture);
    CreateStaticMesh(kelpMesh, defaultShader, Vector3{ -3.0f, 0.0f, 8.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the rocks
    Mesh rockMesh { rockObj };
    rockMesh.SetTexture(rockTexture);
    CreateStaticMesh(rockMesh, defaultShader, Vector3{ -11.0f, 0.0f, -14.0f }, Vector3{ 0.0f, 0.0f, 0.0f });
    CreateStaticMesh(rockMesh, defaultShader, Vector3{ 11.0f, 0.0f, -10.0f }, Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f });
    CreateStaticMesh(rockMesh, defaultShader, Vector3{ 0.0f, 0.0f, -8.0f }, Vector3{ CONST_PI / 2.0f, 0.0f, CONST_PI / 2.0f });

    // Creates the scenery wall
    Mesh sceneryWallMesh { sceneryWallObj };
    sceneryWallMesh.SetTexture(wallTexture);
    CreateStaticMesh(sceneryWallMesh, defaultShader, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the scenery metal beam
    Mesh sceneryBeamMesh { sceneryBeamObj };
    sceneryBeamMesh.SetTexture(beamTexture);
    CreateStaticMesh(sceneryBeamMesh, defaultShader, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the scenery concrete
    Mesh sceneryConcreteMesh { sceneryConcreteObj };
    sceneryConcreteMesh.SetTexture(concreteTexture);
    CreateStaticMesh(sceneryConcreteMesh, defaultShader, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the scenery sand
    Mesh scenerySandMesh { scenerySandObj };
    scenerySandMesh.SetTexture(sandTexture);
    CreateStaticMesh(scenerySandMesh, defaultShader, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the scenery rock
    Mesh sceneryRockMesh { sceneryRockObj };
    sceneryRockMesh.SetTexture(rockTexture);
    CreateStaticMesh(sceneryRockMesh, defaultShader, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the weapon
    Mesh weaponMesh { weaponObj };
    weaponMesh.SetTexture(weaponTexture);
    CreateItem(weaponMesh, defaultShader, Vector3{ 2.0f, 1.25f, 0.0f }, Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f });

    // Creates the armor
    Mesh armorMesh { armorObj };
    armorMesh.SetTexture(armorTexture);
    CreateItem(armorMesh, defaultShader, Vector3{ 3.00f, 0.25f, 6.00f }, Vector3{ 0.0f, 0.0f, 0.0f });

    // Creates the player =============================================
    Mesh cubeMesh { cubeObj };
    cubeMesh.SetTexture(skyboxTexture);
    GameObject& player = AddGameObject({});

    // Adds the necessary components
    player.AddComponent<Transform>(Vector3 { 0.0f, 2.5f, 4.0f });
    player.AddComponent<Moveable>();
    player.AddComponent<Player>();
    player.AddComponent<Camera>(true, cubeMesh, skyboxShader);

}
