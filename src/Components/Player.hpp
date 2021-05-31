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

# include "Component.hpp"
# include "GameObject.hpp"
# include "Transform.hpp"
# include "Moveable.hpp"

# include "../Math/Vector.hpp"
# include "../Rendering/Geometry2D.hpp"

class Player : public Adven::Component
{
    friend class GameObject;
public:
    virtual void Start() override;
    virtual void VDrawUpdate() override;
    virtual void VBlankUpdate() override;

private:
    Transform* transform;
    Adven::Moveable* moveable;
    Shape2DCollection bulletModel;

    // Stores the last time the player shot
    uint64_t lastShotTime;

    // Delay before player being able to shoot again
    const float shootingDelay = 0.2f;

};

#endif /* end of include guard: PLAYER_HPP */