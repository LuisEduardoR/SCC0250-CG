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

# include "../Assets/AssetLibrary.hpp"
# include "../Assets/Texture2D.hpp"
# include "../Assets/WavefrontObject.hpp"
# include "../Assets/WavefrontMaterial.hpp"
# include "../Components/Camera.hpp"
# include "../Components/Transform.hpp"
# include "../Components/Moveable.hpp"
# include "../Components/Player.hpp"
# include "../Components/RendererComponent.hpp"
# include "../Components/ItemAnimator.hpp"
# include "../Math/Vector.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Physics/CircleCollider.hpp"
# include "../Rendering/Renderer.hpp"
# include "../Rendering/Geometry.hpp"
# include "../Rendering/TextureObject.hpp"
# include "../WindowSystem/WindowSystem.hpp"

using namespace Adven;

// Creates a regular object on the current scene
void GameScene::CreateObject(
    const std::string modelPath,
    const std::string texturePath,
    std::shared_ptr<Shader> shader,
    const Vector3& position,
    const Vector3& rotation
) {

    Mesh mesh { *AssetLibrary<WavefrontObject>::RequireAsset(modelPath), shader };

    GameObject& gameObject = AddGameObject({});
    gameObject.AddComponent<Transform> ( position, rotation, Vector3( 1.0f, 1.0f, 1.0f));
    gameObject.AddComponent<RendererComponent<Mesh>>(mesh);

}

// Creates an item on the current scene
void GameScene::CreateItem(
    const std::string modelPath,
    const std::string texturePath,
    std::shared_ptr<Shader> shader,
    const Vector3& position,
    const Vector3& rotation
) {
    Mesh mesh { *AssetLibrary<WavefrontObject>::RequireAsset(modelPath), shader };

    GameObject& gameObject = AddGameObject({});
    gameObject.AddComponent<Transform> ( position, rotation, Vector3( 1.0f, 1.0f, 1.0f));
    gameObject.AddComponent<RendererComponent<Mesh>>(mesh);
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

    // Creates the default shader by loading the necessary GLSL code.
    auto defaultShader = std::make_shared<Shader>(
        *AssetLibrary<std::string>::RequireAsset("./assets/defaultVertex.glsl"),
        *AssetLibrary<std::string>::RequireAsset("./assets/defaultFragment.glsl")
    );

    // Creates the objects and items ==================================

    // Creates the Crawler
    CreateObject(
        "./assets/crawler.obj",         // Model path
        "./assets/Crawler.png",         // Texture path
        defaultShader,                  // Shader
        Vector3{ 0.0f, 0.0f, 2.0f },    // Position
        Vector3{ 0.0f, 0.0f, 0.0f }     // Rotation
    );

    // Creates the lab tank
    CreateObject(
        "./assets/labtank.obj",
        "./assets/tech_ATLAS.png",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the table
    CreateObject(
        "./assets/table.obj",
        "./assets/props_ATLAS.png",
        defaultShader,
        Vector3{ 2.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f }
    );

    // Creates the kelp
    CreateObject(
        "./assets/kelp.obj",
        "./assets/outside_ATLAS.png",
        defaultShader,
        Vector3{ -3.0f, 0.0f, 8.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the rocks
    CreateObject(
        "./assets/rock.obj",
        "./assets/Rock.png",
        defaultShader,
        Vector3{ -11.0f, 0.0f, -14.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );
    CreateObject(
        "./assets/rock.obj",
        "./assets/Rock.png",
        defaultShader,
        Vector3{ 11.0f, 0.0f, -10.0f },
        Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f }
    );
    CreateObject(
        "./assets/rock.obj",
        "./assets/Rock.png",
        defaultShader,
        Vector3{ 0.0f, 0.0f, -8.0f },
        Vector3{ CONST_PI / 2.0f, 0.0f, CONST_PI / 2.0f }
    );

    // Creates the scenery wall
    CreateObject(
        "./assets/sceneryWall.obj",
        "./assets/Wall.png",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the scenery metal beam
    CreateObject(
        "./assets/sceneryBeam.obj",
        "./assets/Beam.png",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the scenery concrete
    CreateObject(
        "./assets/sceneryConcrete.obj",
        "./assets/Concrete.png",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the scenery sand
    CreateObject(
        "./assets/scenerySand.obj",
        "./assets/Sand.png",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the scenery rock
    CreateObject(
        "./assets/sceneryRock.obj",
        "./assets/Rock.png",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the weapon
    CreateItem(
        "./assets/weapon.obj",
        "./assets/weapon.png",
        defaultShader,
        Vector3{ 2.0f, 1.25f, 0.0f },
        Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f }
    );

    // Creates the armor
    CreateItem(
        "./assets/armor.obj",
        "./assets/armor.png",
        defaultShader,
        Vector3{ 3.00f, 0.25f, 6.00f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the player =============================================
    GameObject& player = AddGameObject({});

    // Adds the necessary components
    player.AddComponent<Transform>(Vector3 { 0.0f, 2.5f, 4.0f });
    player.AddComponent<Moveable>();
    player.AddComponent<Player>();

    // Loads the data for the skybox.
    auto skyboxShader = std::make_shared<Shader>(
        *AssetLibrary<std::string>::RequireAsset("./assets/skyboxVertex.glsl"),
        *AssetLibrary<std::string>::RequireAsset("./assets/skyboxFragment.glsl")
    );

    std::array<std::shared_ptr<Texture2D>, 6> skybox =
    {{
        AssetLibrary<Texture2D>::RequireAsset("./assets/skybox/underwater/uw_ft.jpg"),
        AssetLibrary<Texture2D>::RequireAsset("./assets/skybox/underwater/uw_bk.jpg"),
        AssetLibrary<Texture2D>::RequireAsset("./assets/skybox/underwater/uw_up.jpg"),
        AssetLibrary<Texture2D>::RequireAsset("./assets/skybox/underwater/uw_dn.jpg"),
        AssetLibrary<Texture2D>::RequireAsset("./assets/skybox/underwater/uw_rt.jpg"),
        AssetLibrary<Texture2D>::RequireAsset("./assets/skybox/underwater/uw_lf.jpg")
    }};
    auto skyboxTexture = std::make_shared<TextureObject>(TextureObject::Type::TextureCubeMap);
    skyboxTexture->UploadTexture(0, skybox);

    Mesh cubeMesh { *AssetLibrary<WavefrontObject>::RequireAsset("./assets/cube.obj") };
    //cubeMesh.SetTexture(skyboxTexture);

    // Adds the camera with skybox.
    player.AddComponent<Camera>(true, cubeMesh, skyboxShader);

}
