// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the Transform component
*/

# ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include "Component.hpp"
# include "../Math/Vector.hpp"

# include <cmath>
# include <list>

union Matrix4x4;

namespace Adven {
    class Scene;
}

class Transform : public Adven::Component {
public:
    Vector3 localPosition{};
    Vector3 localRotation{};
    Vector3 localScale{ 1.0f, 1.0f, 1.0f };
public:
    Transform() = default;
    explicit Transform(Vector3 localPosition);
    Transform(Vector3 localPosition, Vector3 localRotation);
    Transform(Vector3 localPosition, Vector3 localRotation, Vector3 localScale);
public:
    ~Transform() override = default;
public:
    /// Clones the transform.
    /// This function does not clone the transform childs nor parent.
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
public:
    [[nodiscard]] auto LocalMatrix() const -> Matrix4x4;
    [[nodiscard]] auto WorldMatrix() const -> Matrix4x4;
    [[nodiscard]] auto WorldPosition() const -> Vector3;
    [[nodiscard]] auto WorldRotation() const -> Vector3;
    [[nodiscard]] auto WorldScale() const -> Vector3;
        // void SetWorldPosition(Vector3 worldPos);
};

class Transform2D {

public:

    Vector2 position;
    float rotation;
    Vector2 scale;

    // Constructors
    Transform2D(Vector2 position = {}, float rotation = 0.0f, Vector2 scale = { 1.0f, 1.0f });

    // Gets the 4x4 transformation matrix for this object.
    Matrix4x4 GetTransformationMatrix();

};

# endif /* end of include guard: TRANSFORM_HPP */
