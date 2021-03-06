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

# ifndef PLAYER_HPP
# define PLAYER_HPP

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

class Shooter;

class Transform;

class Player : public Adven::Component
{
public:
    Player() = default;
public:
    ~Player() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    void Start() override;
    void VDrawUpdate() override;

private:
    Transform* transform;
    Adven::Moveable* moveable;
    Adven::CircleCollider* collider;
    float maxSpeed { 4.0f };
    float fov;
    Vector3 lowerBounds { -12.3f, 1.5f, -12.3f };
    Vector3 higherBounds { 12.3f, 1.5f, 12.3f };
};

#endif /* end of include guard: PLAYER_HPP */
