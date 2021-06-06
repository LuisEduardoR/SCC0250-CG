// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the EnemyShip component
    Implements the regular enemy ship mechanics
*/

#ifndef ENEMY_SHIP_HPP
#define ENEMY_SHIP_HPP

# include <array>
# include <cstdint>
# include <memory>

# include "Component.hpp"
# include "../Math/Vector.hpp"

namespace Adven {
    class GameObject;
};

class Transform;

class EnemyShip : public Adven::Component
{

public:
    EnemyShip(Transform* targetTransform);
    ~EnemyShip() override = default;

    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    void Start() override;
    void VDrawUpdate() override;

private:
    Transform* transform{ nullptr };
    Transform* targetTransform;
};

#endif /* end of include guard: ENEMY_SHIP_HPP */
