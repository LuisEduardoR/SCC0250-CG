// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Component.hpp"
# include "GameObject.hpp"
# include "Vector.hpp"
# include "Transform.hpp"
# include "Moveable.hpp"
# include "Geometry.hpp"

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
};

#endif