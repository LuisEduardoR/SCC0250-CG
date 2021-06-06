// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the Player component
*/

# ifndef BOSS_HPP
# define BOSS_HPP

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

class Boss : public Adven::Component
{

public:
    Boss(float amplitude, float speed);
    ~Boss() override = default;

    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    void Start() override;
    void VDrawUpdate() override;
    void VBlankUpdate() override;

    bool active;

private:
    Transform* transform{ nullptr };
    Adven::Moveable* moveable{ nullptr };

    float targetPos;
    bool goingRight;

    // Amplitude of movement
    const float amplitude = 0.5f;

    // Movement speed
    const float speed = 0.5f;

};

#endif /* end of include guard: BOSS_HPP */
