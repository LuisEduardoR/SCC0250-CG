// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the Player component
*/

# ifndef SHOOTER_HPP
# define SHOOTER_HPP

# include <array>
# include <cstdint>
# include <functional>
# include <memory>

# include "Component.hpp"
# include "../Math/Vector.hpp"

namespace Adven {
    class GameObject;
    class Moveable;
};

class Transform;

class Shooter : public Adven::Component
{

public:
    Shooter(std::shared_ptr<Adven::GameObject> bulletPrefab, Vector3 cannonOffset, float startingDelay, float shootingDelay);
    ~Shooter() override = default;

    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    void Start() override;
    void VDrawUpdate() override;
    void VBlankUpdate() override;

    bool active;

    std::function<void(Adven::GameObject&)> afterSpawn;

private:
    Transform* transform{ nullptr };
    Adven::Moveable* moveable{ nullptr };
    std::shared_ptr<Adven::GameObject> bulletPrefab;

    Vector3 cannonOffset;

    // Stores the last time a shot was made
    float currentTime;

    // Delay before the first shot
    const float startingDelay = 0.1f;

    // Delay before being able to shoot again
    const float shootingDelay = 0.2f;

};

#endif /* end of include guard: SHOOTER_HPP */
