// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "GameScene.hpp"

# include <filesystem>
# include <memory>
# include <stdexcept>
# include <vector>
# include <random>

# include "../Assets/AssetLibrary.hpp"
# include "../Assets/Texture2D.hpp"
# include "../Assets/WavefrontObject.hpp"
# include "../Assets/WavefrontMaterial.hpp"
# include "../Components/Camera.hpp"
# include "../Components/Transform.hpp"
# include "../Components/Light.hpp"
# include "../Components/Moveable.hpp"
# include "../Components/Player.hpp"
# include "../Components/RendererComponent.hpp"
# include "../Components/ItemAnimator.hpp"
# include "../Components/Voidmouth.hpp"
# include "../Math/Vector.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Physics/CircleCollider.hpp"
# include "../Rendering/Renderer.hpp"
# include "../Rendering/Geometry.hpp"
# include "../Rendering/TextureObject.hpp"
# include "../WindowSystem/WindowSystem.hpp"

using namespace Adven;

namespace {
std::shared_ptr<Mesh> LoadObj(std::string modelPath, std::shared_ptr<Shader> shader) {
    auto modelObj{ AssetLibrary<WavefrontObject>::RequireAsset(modelPath) };
    auto mesh = std::make_shared<Mesh>(*modelObj);

    auto modelDirectory = std::filesystem::path(modelPath).parent_path();

    // Load referenced material libraries (aka mtl files)
    WavefrontMaterialLibrary materialLibrary;
    for (const auto& materialLibraryFile : modelObj->materialLibraryFiles)
    {
        auto matLib = AssetLibrary<WavefrontMaterialLibrary>
            ::RequireAsset((modelDirectory / materialLibraryFile).string());

        // Merge the library maps.
        materialLibrary.insert(matLib->begin(), matLib->end());
    }

    std::unordered_map<std::string, std::shared_ptr<Material>> materials;
    std::size_t i = 0;
    for (const WavefrontObject::Element<WavefrontObject::Face>& face : modelObj->faces)
    {
        if (face.metadata.materialName != nullptr)
        {
            try
            {
                mesh->SetMaterial(i, materials.at(*face.metadata.materialName));
                continue;
            }
            catch(const std::out_of_range&) {}

            try
            {
                auto wMaterial = materialLibrary.at(*face.metadata.materialName);

                std::shared_ptr<TextureObject> texture;
                if (wMaterial.diffuseReflectivityMap.has_value()) {
                    // FIXME: Fix relative path workaround
                    auto texture2d = AssetLibrary<Texture2D>::RequireAsset(
                            (modelDirectory / wMaterial.diffuseReflectivityMap.value()).string());

                    texture = std::make_shared<TextureObject>(TextureObject::Type::Texture2D);
                    texture->UploadTexture(0, texture2d);
                }

                auto material = std::make_shared<DefaultMaterial>(shader, wMaterial, texture);
                mesh->SetMaterial(i, material);
                materials[*face.metadata.materialName] = material;
            }
            catch(const std::out_of_range&)
            {
                throw std::runtime_error(std::string("Failed to find material: ")
                        + *face.metadata.materialName
                        + " while loading "
                        + modelPath + '\n');
            }
        }
        i++;
    }

    return mesh;
}
}

// Creates a regular object on the current scene
void GameScene::CreateObject(
    const std::string modelPath,
    std::shared_ptr<Shader> shader,
    const Vector3& position,
    const Vector3& rotation
) {
    // FIXME: Don't allocated duplicated meshes
    std::shared_ptr<Mesh> mesh = LoadObj(modelPath, shader);

    GameObject& gameObject = AddGameObject({});
    gameObject.AddComponent<Transform> ( position, rotation, Vector3( 1.0f, 1.0f, 1.0f));
    gameObject.AddComponent<RendererComponent<Mesh>>(*mesh);

}

// Creates an item on the current scene
void GameScene::CreateItem(
    const std::string modelPath,
    std::shared_ptr<Shader> shader,
    const Vector3& position,
    const Vector3& rotation
) {
    std::shared_ptr<Mesh> mesh = LoadObj(modelPath, shader);

    GameObject& gameObject = AddGameObject({});
    gameObject.AddComponent<Transform> ( position, rotation, Vector3( 1.0f, 1.0f, 1.0f));
    gameObject.AddComponent<RendererComponent<Mesh>>(*mesh);
    // Items have an special animation.
    gameObject.AddComponent<ItemAnimator>(0.15f, 0.50f);

}

// Creates a VoidMouth that roams the current scene
void GameScene::CreateVoidMouth(
    const std::string modelPath,
    std::shared_ptr<Shader> shader,
    const Vector3& position,
    const Vector3& rotation,
    const std::vector<Vector3>& path
) {
    // FIXME: Don't allocated duplicated meshes
    std::shared_ptr<Mesh> mesh = LoadObj(modelPath, shader);

    GameObject& gameObject = AddGameObject({});
    gameObject.AddComponent<Transform> ( position, rotation, Vector3( 1.0f, 1.0f, 1.0f));
    gameObject.AddComponent<RendererComponent<Mesh>>(*mesh);
    // ! FIX: light position not updating
    gameObject.AddComponent<Light>(Color( 0.0f, 0.4f, 0.5f ));
    gameObject.AddComponent<Moveable>();
    gameObject.AddComponent<Voidmouth>(path);

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
        defaultShader,                  // Shader
        Vector3{ 0.0f, 0.0f, 2.0f },    // Position
        Vector3{ 0.0f, 0.0f, 0.0f }     // Rotation
    );

    // Creates the lab tank
    CreateObject(
        "./assets/labtank.obj",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the table
    CreateObject(
        "./assets/table.obj",
        defaultShader,
        Vector3{ 2.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f }
    );

    // Creates the kelp
    CreateObject(
        "./assets/kelp.obj",
        defaultShader,
        Vector3{ -3.0f, 0.0f, 8.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the rocks
    CreateObject(
        "./assets/rock.obj",
        defaultShader,
        Vector3{ -11.0f, 0.0f, -14.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );
    CreateObject(
        "./assets/rock.obj",
        defaultShader,
        Vector3{ 11.0f, 0.0f, -10.0f },
        Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f }
    );
    CreateObject(
        "./assets/rock.obj",
        defaultShader,
        Vector3{ 0.0f, 0.0f, -8.0f },
        Vector3{ CONST_PI / 2.0f, 0.0f, CONST_PI / 2.0f }
    );

    // Creates the scenery wall
    CreateObject(
        "./assets/sceneryWall.obj",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the scenery metal beam
    CreateObject(
        "./assets/sceneryBeam.obj",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the scenery concrete
    CreateObject(
        "./assets/sceneryConcrete.obj",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the scenery sand
    CreateObject(
        "./assets/scenerySand.obj",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the scenery rock
    CreateObject(
        "./assets/sceneryRock.obj",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 0.0f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // Creates the weapon
    CreateItem(
        "./assets/weapon.obj",
        defaultShader,
        Vector3{ 2.0f, 1.25f, 0.0f },
        Vector3{ 0.0f, CONST_PI / 2.0f, 0.0f }
    );

    // Creates the armor
    CreateItem(
        "./assets/armor.obj",
        defaultShader,
        Vector3{ 3.00f, 0.25f, 6.00f },
        Vector3{ 0.0f, 0.0f, 0.0f }
    );

    // LIGHTS =========================================================

    // Light 1
    {
        GameObject& gameObject = AddGameObject({});
        gameObject.AddComponent<Transform>(Vector3{ 5.0f, 5.0f, -5.0f });
        gameObject.AddComponent<Light>(Color{ 1.0f, 1.0f, 1.0f });
    }

    // Light 2
    {
        GameObject& gameObject = AddGameObject({});
        gameObject.AddComponent<Transform>(Vector3{ 0.0f, 3.0f, 0.0f });
        gameObject.AddComponent<Light>(Color{ 0.0f, 1.0f, 0.0f });
    }

    // VOID MOUTH (Moving light) ======================================

    CreateVoidMouth(
        "./assets/voidMouth.obj",
        defaultShader,
        Vector3{ 0.0f, 0.0f, 10.0f },
        Vector3{ 0.0f, 0.0f, 0.0f },
        {
            { 0.0f, 0.0f, 10.0f },
            { -10.0f, 0.0f, 10.0f },
            { -10.0f, 0.0f, -10.0f },
            { 0.0f, 0.0f, -10.0f },
            { 0.0f, 0.0f, 10.0f }
        }
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

    auto skyboxMaterial = std::make_shared<SkyboxMaterial>(skyboxShader, skyboxTexture);

    Mesh cubeMesh { *AssetLibrary<WavefrontObject>::RequireAsset("./assets/cube.obj") };
    for (std::size_t i = 0; i < 6; i++)
    {
        cubeMesh.SetMaterial(0, skyboxMaterial);
    }

    // Adds the camera with skybox.
    player.AddComponent<Camera>(true, cubeMesh);

    // Configures the renderer
    Renderer::SetAmbientLightColor(Color(1, 3, 42));
    Renderer::SetAmbientLightIntensity(1.0f);

}
