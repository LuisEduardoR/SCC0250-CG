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
# include "../Components/ShapeRenderer.hpp"
# include "../Math/Vector.hpp"
# include "../Math/Matrix4x4.hpp"
# include "../Physics/CircleCollider.hpp"
# include "../Rendering/Geometry2D.hpp"
# include "../Rendering/PoissonDiscSampling.hpp"

using namespace Adven;

namespace
{

auto ShipModel() -> Shape2DCollection
{
    Color cannon{ 73, 76, 88 };
    Color base{ 47, 50, 59 };
    Color circle{ 64, 92, 157 };
    Color window{ 101, 109, 138 };

    Shape2DCollection shipModel( new std::vector<std::unique_ptr<Shape2D>>{});
    // Ship Cannons
    shipModel.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.405f, +0.264f }, { -0.304f, +0.263f },
        { -0.405f, -0.196f }, { -0.304f, -0.196f },
        cannon
    }});
    shipModel.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { +0.304f, +0.264f }, { +0.405f, +0.263f },
        { +0.304f, -0.196f }, { +0.405f, -0.196f },
        cannon
    }});
    // Ship Thruster
    shipModel.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.190f, -0.455f }, { +0.213f, -0.455f },
        { -0.150f, -0.728f }, { +0.150f, -0.728f },
        cannon
    }});
    // Ship Base 
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, +0.660f }, { -0.231f, +0.048f }, { +0.231f, +0.048f }, base
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.231f, +0.048f }, { +0.231f, +0.048f }, { -0.526f, -0.205f }, base
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.231f, +0.048f }, { -0.526f, -0.205f }, { +0.526f, -0.205f }, base
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.526f, -0.205f }, { -0.190f, -0.455f }, { +0.190f, -0.455f }, base
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.526f, -0.205f }, { +0.526f, -0.205f }, { +0.190f, -0.455f }, base
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.526f, -0.205f }, { -0.190f, -0.455f }, { -0.581f, -0.744f }, base
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.526f, -0.205f }, { +0.190f, -0.455f }, { +0.581f, -0.744f }, base
    }});
    // Ship Window
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, +0.530f }, { -0.194f, -0.074f }, { +0.194f, -0.074f }, window
    }});
    shipModel.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -0.290f }, { -0.194f, -0.074f }, { +0.194f, -0.074f }, window
    }});
    // Ship Circles
    shipModel.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.357f, -0.354f }, 0.125f, 32, circle
    }});
    shipModel.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +0.357f, -0.354f }, 0.125f, 32, circle
    }});

    return shipModel;
}

auto Ship2Model() -> Shape2DCollection
{
    Shape2DCollection shipModel( new std::vector<std::unique_ptr<Shape2D>>{});

    // Ship Base
    shipModel->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, +0.694f }, { -0.083f, +0.458f }, { +0.083f, +0.458f }, Color(170, 166, 155)
    }});
    shipModel->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.083f, +0.458f }, { +0.083f, +0.458f },
        { -0.073f, -0.099f }, { +0.073f, -0.099f },
        Color(170, 166, 155)
    }});
    shipModel->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.073f, -0.099f }, { +0.073f, -0.099f },
        { -0.144f, -0.417f }, { +0.144f, -0.417f },
        Color(170, 166, 155)
    }});
    shipModel->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.144f, -0.417f }, { +0.144f, -0.417f },
        { -0.084f, -0.489f }, { +0.084f, -0.489f },
        Color(170, 166, 155)
    }});
    shipModel->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.084f, -0.489f }, { +0.084f, -0.489f },
        { -0.066f, -0.604f }, { +0.066f, -0.604f },
        Color(170, 166, 155)
    }});
    shipModel->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.066f, -0.604f }, { +0.066f, -0.604f }, { +0.000f, -0.681f }, Color(170, 166, 155)
    }});
    shipModel->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.014f, -0.640f }, { +0.014f, -0.640f },
        { -0.014f, -0.713f }, { +0.014f, -0.713f },
        Color(170, 166, 155)
    }});
    // Ship Wings
    shipModel->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.083f, +0.458f }, { -0.347f, -0.246f }, { -0.073f, -0.099f }, Color(87, 46, 47)
    }});
    shipModel->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.305f, -0.386f }, { -0.347f, -0.246f }, { -0.073f, -0.099f }, Color(87, 46, 47)
    }});
    shipModel->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -0.305f, -0.386f }, { -0.144f, -0.417f }, { -0.073f, -0.099f }, Color(87, 46, 47)
    }});
    shipModel->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.083f, +0.458f }, { +0.347f, -0.246f }, { +0.073f, -0.099f }, Color(87, 46, 47)
    }});
    shipModel->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.305f, -0.386f }, { +0.347f, -0.246f }, { +0.073f, -0.099f }, Color(87, 46, 47)
    }});
    shipModel->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.305f, -0.386f }, { +0.144f, -0.417f }, { +0.073f, -0.099f }, Color(87, 46, 47)
    }});
    // Ship Window
    shipModel->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.040f, -0.297f }, { +0.040f, -0.297f },
        { -0.064f, -0.346f }, { +0.064f, -0.346f },
        Color(46, 60, 72)
    }});
    shipModel->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.064f, -0.346f }, { +0.064f, -0.346f },
        { -0.064f, -0.443f }, { +0.064f, -0.443f },
        Color(46, 60, 72)
    }});
    shipModel->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.064f, -0.443f }, { +0.064f, -0.443f },
        { -0.040f, -0.499f }, { +0.040f, -0.499f },
        Color(46, 60, 72)
    }});
    // Thruster
    shipModel->push_back(std::unique_ptr<Quad>{ new Quad{
        { -0.167f, -0.414f }, { -0.144f, -0.417f },
        { -0.148f, -0.488f }, { -0.084f, -0.488f },
        Color(46, 60, 72)
    }});
    shipModel->push_back(std::unique_ptr<Quad>{ new Quad{
        { +0.167f, -0.414f }, { +0.144f, -0.417f },
        { +0.148f, -0.488f }, { +0.084f, -0.488f },
        Color(46, 60, 72)
    }});

    return shipModel;
}

auto AsteroidModel() -> Shape2DCollection
{
    Shape2DCollection asteroidModel( new std::vector<std::unique_ptr<Shape2D>>{});

    //Base
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.179f, -0.241f }, 1.027f / 2.0f, 16, Color(145, 145, 145)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { +0.179f, +0.201f }, 1.060f / 2.0f, 16, Color(145, 145, 145)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { +0.243f, -0.259f }, 0.876f / 2.0f, 16, Color(145, 145, 145)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { +0.599f, -0.025f }, 0.404f / 2.0f, 16, Color(145, 145, 145)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.424f, +0.034f }, 0.600f / 2.0f, 16, Color(145, 145, 145)
    }});
    // Craters
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { +0.053f, +0.570f }, 0.108f / 2.0f, 16, Color(113, 113, 113)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { +0.377f, +0.356f }, 0.201f / 2.0f, 16, Color(113, 113, 113)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.029f, +0.262f }, 0.404f / 2.0f, 16, Color(113, 113, 113)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.394f, +0.179f }, 0.166f / 2.0f, 16, Color(113, 113, 113)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { +0.483f, +0.002f }, 0.201f / 2.0f, 16, Color(113, 113, 113)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.574f, -0.004f }, 0.104f / 2.0f, 16, Color(113, 113, 113)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.202f, -0.163f }, 0.297f / 2.0f, 16, Color(113, 113, 113)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { +0.271f, -0.414f }, 0.474f / 2.0f, 16, Color(113, 113, 113)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.483f, -0.344f }, 0.196f / 2.0f, 16, Color(113, 113, 113)
    }});
    asteroidModel->push_back(std::unique_ptr<Circle>{ new Circle{
        { -0.210f, -0.498f }, 0.283f / 2.0f, 16, Color(113, 113, 113)
    }});

    return asteroidModel;
}

auto BossModel() -> Shape2DCollection
{
    Shape2DCollection boss( new std::vector<std::unique_ptr<Shape2D>>{});

    // Boss Base
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { -80.000f, -76.950f }, { -50.000f, -18.320f }, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { -50.000f, -18.320f }, { +0.000f, +0.000f }, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { +0.000f, +0.000f }, { +50.000f, -18.320f }, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { 50.000f, -18.320f }, { +80.000f, -77.000f }, Color(31, 40, 126)
    }});

    // Boss Window
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -167.000f }, { -54.000f, -75.890f }, { -33.750f, -34.830f }, Color(67, 39, 197)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -167.000f }, { -33.750f, -34.830f }, { +0.000f, -22.000f }, Color(67, 39, 197)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -167.000f }, { +0.000f, -22.000f }, { +33.750f, -34.830f }, Color(67, 39, 197)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -167.000f }, { +33.750f, -34.830f }, { +54.000f, -75.890f }, Color(67, 39, 197)
    }});

    // Boss body shape
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { -90.000f, -170.250f }, { -80.00, -76.94f }, Color(117, 72, 138)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +0.000f, -207.000f }, { 90.000f, -170.250f }, { +80.000f, -77.000f }, Color(117, 72, 138)
    }});

    // Boss Big Claw Left
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -73.000f, -67.500f }, { -152.000f, 26.000f }, { -59.000f, -35.500f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -152.000f, 26.000f }, { -59.000f, -35.500f }, { -110.000f, +26.000f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -152.000f, 26.000f }, { -110.000f, +26.000f }, { -59.000f, +122.000f }, Color(195, 195, 195)
    }});

    // Boss Big Claw Right
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +73.000f, -67.500f }, { +152.000f, 26.000f }, { +59.000f, -35.500f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +152.000f, 26.000f }, { +59.000f, -35.500f }, { +110.000f, +26.000f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +152.000f, 26.000f }, { +110.000f, +26.000f }, { +59.000f, +122.000f }, Color(195, 195, 195)
    }});

    // Boss Small Claw Left
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -50.000f, -18.320f }, { -80.000f, +22.130f }, { -34.500f, -12.640f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -80.000f, +22.130f }, { -34.500f, -12.640f }, { -58.140f, +22.130f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { -80.000f, +22.130f }, { -58.140f, +22.130f }, { -35.470f, +81.000f }, Color(195, 195, 195)
    }});

    // Boss Small Claw Right
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +50.000f, -18.320f }, { +80.000f, +22.130f }, { +34.500f, -12.640f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +80.000f, +22.130f }, { +34.500f, -12.640f }, { +58.140f, +22.130f }, Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Triangle>{ new Triangle{
        { +80.000f, +22.130f }, { +58.140f, +22.130f }, { +35.470f, +81.000f }, Color(195, 195, 195)
    }});

    // Center Orb
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +3.000f, +92.000f }, 40.000f, 32
    }});

    // Left Cannon
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -295.000f, +90.000f }, { -285.000f, +90.000f },
        { -295.000f, +120.000f }, { -285.000f, +120.000f },
        Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -277.000f, +96.000f }, { -259.000f, +96.000f },
        { -277.000f, +153.000f }, { -259.000f, +153.000f },
        Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { -251.000f, +90.000f }, { -241.000f, +90.000f },
        { -251.000f, +120.000f }, { -241.000f, +120.000f },
        Color(195, 195, 195)
    }});
    
    // Right Cannon
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { +295.000f, +90.000f }, { +285.000f, +90.000f },
        { +295.000f, +120.000f }, { +285.000f, +120.000f },
        Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { +277.000f, +96.000f }, { +259.000f, +96.000f },
        { +277.000f, +153.000f }, { +259.000f, +153.000f },
        Color(195, 195, 195)
    }});
    boss.get()->push_back(std::unique_ptr<Quad>{ new Quad{
        { +251.000f, +90.000f }, { +241.000f, +90.000f },
        { +251.000f, +120.000f }, { +241.000f, +120.000f },
        Color(195, 195, 195)
    }});

    // Tail Left
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -59.000f, -227.000f }, 40.000f, 32, Color(117, 72, 138)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -139.000f, -215.000f }, 40.000f, 32, Color(117, 72, 138)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -204.000f, -167.000f }, 40.000f, 32, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -239.000f, -95.000f }, 40.000f, 32, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -261.000f, -18.000f }, 40.000f, 32, Color(67, 39, 197)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { -268.000f, +62.000f }, 40.000f, 32, Color(67, 39, 197)
    }});

     // Tail Right
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +59.000f, -227.000f }, 40.000f, 32, Color(117, 72, 138)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +139.000f, -215.000f }, 40.000f, 32, Color(117, 72, 138)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +204.000f, -167.000f }, 40.000f, 32, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +239.000f, -95.000f }, 40.000f, 32, Color(31, 40, 126)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +261.000f, -18.000f }, 40.000f, 32, Color(67, 39, 197)
    }});
    boss.get()->push_back(std::unique_ptr<Circle>{ new Circle{
        { +268.000f, +62.000f }, 40.000f, 32, Color(67, 39, 197)
    }});

    return boss;
}

auto SkyModel() -> Shape2DCollection
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

TestScene::TestScene()
{
    // Vertex Shader's GLSL code
    std::string vertexCode =
    "attribute vec3 position;\n"
    "uniform mat4 transform;\n"
    "uniform mat4 view;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = view * transform * vec4(position, 1.0);\n"
    "}\n";

    // Fragment Shader's GLSL code
    std::string fragmentCode =
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n";

    // Creates the program we are going to use from our vertex and fragment shader's source code
    Renderer::SetProgram(vertexCode, fragmentCode);

    Shape2DCollection shipModel = ShipModel();
    Shape2DCollection bossModel = BossModel();
    Shape2DCollection skyModel = SkyModel();
    Shape2DCollection ship2Model = Ship2Model();
    Shape2DCollection asteroidModel = AsteroidModel();

    GameObject& ship = AddGameObject({});

    ship.AddComponent<Transform>(
        Vector3{ 0.0f, -0.3f, 0.0f },
        Vector3{},
        Vector3{ 0.3f, 0.3f, 1.0f });
    ship.AddComponent<ShapeRenderer>(shipModel);
    ship.AddComponent<Moveable>();
    ship.AddComponent<CircleCollider>(0.66f * 0.3f, true);
    ship.AddComponent<Player>();
    ship.AddComponent<Camera>(true);

    GameObject& boss = AddGameObject({});

    boss.AddComponent<Transform>(
        Vector3{ 0.0f, 0.4f, 0.0f },
        Vector3{ 0.0f, 0.0f, CONST_PI },
        Vector3{ 0.0025f, 0.0025f, 0.0f });
    boss.AddComponent<ShapeRenderer>(bossModel);
    boss.AddComponent<Moveable>();
    boss.AddComponent<CircleCollider>(0.66f * 0.3f, true);

    GameObject& ship2 = AddGameObject({});

    ship2.AddComponent<Transform>(
        Vector3{ -0.7f, -0.3f, 0.0f },
        Vector3{},
        Vector3{ 0.3f, 0.3f, 1.0f });
    ship2.AddComponent<ShapeRenderer>(ship2Model);

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

    // Sky goes last because of render order
    GameObject& sky = AddGameObject({});
    sky.AddComponent<Transform>(Vector3 { -1.0f, -1.0f, 0.0f });
    sky.AddComponent<ShapeRenderer>(skyModel);
}
