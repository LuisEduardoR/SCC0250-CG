// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the BaseEnemy component
    Intended  to be used as a base to further develop enemies
*/

# ifndef BASE_ENEMY_HPP
# define BASE_ENEMY_HPP

# include <array>
# include <cstdint>
# include <memory>

# include "Component.hpp"
# include "../Math/Vector.hpp"

namespace Adven {
    class GameObject;
    class Moveable;
};

class Transform;

class BaseEnemy : public Adven::Component
{
public:
    virtual BaseEnemy() = 0;
    virtual ~BaseEnemy() = 0;

    void Start() override;
    void VDrawUpdate() override;
    void VBlankUpdate() override;

private:
    Transform* transform;
    Adven::Moveable* moveable;
    std::shared_ptr<Adven::GameObject> bulletPrefab;

    std::array<Vector3, 2> cannonOffsets;

    // Stores the last time the player shot
    std::uint64_t lastShotTime;

    // Delay before player being able to shoot again
    const float shootingDelay = 0.2f;

};

#endif /* end of include guard: BASE_ENEMY_HPP */
