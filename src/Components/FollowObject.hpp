// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the FollowObject component
    Makes a GameObject follow another
*/

#ifndef FOLLOW_OBJECT_HPP
#define FOLLOW_OBJECT_HPP

#include "Component.hpp"
#include "../Math/Vector.hpp"

class Transform;

class FollowObject : public Adven::Component
{
public:
    FollowObject(Transform* follow, Vector3 offset = Vector3());
    ~FollowObject() override = default;

public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto VDrawUpdate() -> void override;
    
public:
    Transform* follow;
    Vector3 offset;
};

#endif /* end of include guard: FOLLOW_OBJECT_HPP */
