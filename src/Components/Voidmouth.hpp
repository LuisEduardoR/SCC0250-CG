// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the Player component
    Implements the player mechanics allowing for
    user control
*/

# ifndef VOIDMOUTH_HPP
# define VOIDMOUTH_HPP

# include <array>
# include <cstdint>
# include <memory>
# include <vector>

# include "Component.hpp"
# include "../Math/Vector.hpp"

namespace Adven {
    class GameObject;
    class Moveable;
    class CircleCollider;
};

class Transform;

class Voidmouth : public Adven::Component
{
public:
    Voidmouth(std::vector<Vector3> path);
public:
    ~Voidmouth() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    void Start() override;
    void VDrawUpdate() override;

private:
    Transform* transform;
    Adven::Moveable* moveable;
    float maxSpeed { 4.0f };
    std::vector<Vector3> path;
    int currentNode { 0 };
};

#endif /* end of include guard: VOIDMOUTH_HPP */
