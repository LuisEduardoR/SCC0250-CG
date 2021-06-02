// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the Player component
*/

# ifndef PLAYER_HPP
# define PLAYER_HPP

# include <cstdint>
# include <memory>

# include "Component.hpp"

namespace Adven {
    class GameObject;
    class Moveable;
};

class Transform;

class Player : public Adven::Component
{
public:
    Player(std::shared_ptr<Adven::GameObject> bulletPrefab);
public:
    ~Player() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    void Start() override;
    void VDrawUpdate() override;
    void VBlankUpdate() override;

private:
    Transform* transform;
    Adven::Moveable* moveable;
    std::shared_ptr<Adven::GameObject> bulletPrefab;

    // Stores the last time the player shot
    std::uint64_t lastShotTime;

    // Delay before player being able to shoot again
    const float shootingDelay = 0.2f;

};

#endif /* end of include guard: PLAYER_HPP */
