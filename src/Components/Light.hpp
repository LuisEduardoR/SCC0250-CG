// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the code to represent a light that
    illuminates other objects in the scene
*/

# ifndef LIGHT_HPP
# define LIGHT_HPP

# include <memory>
# include <vector>

# include "Component.hpp"
# include "../Rendering/Color.hpp"

namespace Adven {
    class GameObject;
    class Moveable;
    class CircleCollider;
};

class Transform;

class Light : public Adven::Component
{
public:
    // Static vector containing all the lights
    static std::vector<Light*> lights;
public:
    Light(Color color);
public:
    ~Light() override;
public:

    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;

    // Color for the light.
    Color color;

private:

    // Transform for the light (only position matters because we only have point lights).
    Transform* transform;

};

#endif /* end of include guard: LIGHT_HPP */
