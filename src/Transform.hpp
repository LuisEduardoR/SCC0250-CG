// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# ifndef TRANSFORM2D_HPP
# define TRANSFORM2D_HPP

# include <cmath>
# include <list>

# include "Component.hpp"
# include "Vector.hpp"
union Matrix4x4;

/*
    This file contains the base class to represent 2D objects
*/

class Transform : public Adven::Component {
private:
    Transform* parent{ nullptr };
    std::list<Transform*> children{};
public:
    Vector3 localPosition{};
    Vector3 localRotation{};
    Vector3 localScale{ 1.0f, 1.0f, 1.0f };
public:
    Transform() = default;
    explicit Transform(Vector3 localPosition);
    Transform(Vector3 localPosition, Vector3 localRotation);
    Transform(Vector3 localPosition, Vector3 localRotation, Vector3 localScale);
    explicit Transform(Transform* parent);
    Transform(Transform* parent, Vector3 localPosition);
    Transform(Transform* parent, Vector3 localPosition, Vector3 localRotation);
    Transform(Transform* parent, Vector3 localPosition, Vector3 localRotation, Vector3 localScale);
public:
    [[nodiscard]] auto GetChildren() const -> const std::list<Transform*>&;
    [[nodiscard]] auto GetChildren() -> std::list<Transform*>&;
    [[nodiscard]] auto GetParent() const -> Transform*; 
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

# endif
