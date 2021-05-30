// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Transform.hpp"

# include "Vector.hpp"
# include "Matrix4x4.hpp"
# include "Geometry.hpp"

Transform::Transform(Vector3 localPosition) : localPosition(localPosition) {}

Transform::Transform(Vector3 localPosition, Vector3 localRotation)
    : localPosition(localPosition), localRotation(localRotation) {}

Transform::Transform(Vector3 localPosition, Vector3 localRotation, Vector3 localScale)
    : localPosition(localPosition), localRotation(localRotation), localScale(localScale) {}

Transform::Transform(Transform* parent)
    : parent(parent)
{
    parent->children.push_back(this);
}

Transform::Transform(Transform* parent, Vector3 localPosition)
    : parent(parent), localPosition(localPosition)
{
    parent->children.push_back(this);
}

Transform::Transform(Transform* parent, Vector3 localPosition, Vector3 localRotation)
    : parent(parent), localPosition(localPosition), localRotation(localRotation)
{
    parent->children.push_back(this);
}

Transform::Transform(Transform* parent, Vector3 localPosition, Vector3 localRotation, Vector3 localScale)
    : parent(parent), localPosition(localPosition), localRotation(localRotation), localScale(localScale)
{
    parent->children.push_back(this);
}

[[nodiscard]] auto Transform::LocalMatrix() const -> Matrix4x4
{
    return Matrix4x4::TRS(localPosition, localRotation, localScale);
}

[[nodiscard]] auto Transform::WorldMatrix() const -> Matrix4x4
{
    Matrix4x4 world = LocalMatrix();
    
    for (const Transform* transform = parent; transform != nullptr; transform=transform->parent)
    {
        world = transform->LocalMatrix() * world;
    }

    return world;
}

[[nodiscard]] auto Transform::WorldPosition() const -> Vector3
{
    return Vector3{ WorldMatrix() * Vector4{} };
}

[[nodiscard]] auto Transform::WorldRotation() const -> Vector3
{
    Vector3 world = localRotation;
    
    for (const Transform* transform = parent; transform != nullptr; transform=transform->parent)
    {
        world += localRotation;
    }

    return world;
}

[[nodiscard]] auto Transform::WorldScale() const -> Vector3
{
    Vector3 world = localScale;
    
    for (const Transform* transform = parent; transform != nullptr; transform=transform->parent)
    {
        world += localScale;
    }

    return world;
}

Transform2D::Transform2D(Vector2 position, float rotation, Vector2 scale)
    : position(position), rotation(rotation), scale(scale) {}

Matrix4x4 Transform2D::GetTransformationMatrix() {
    return Matrix4x4::TRS(position, rotation, scale);

    /* Matrix4 scale_mat =     { */
    /*                             { this->scale.x,    0.0f,               0.0f,   0.0f    }, */
    /*                             { 0.0f,             this->scale.y,      0.0f,   0.0f    }, */
    /*                             { 0.0f,             0.0f,               1.0f,   0.0f    }, */
    /*                             { 0.0f,             0.0f,               0.0f,   1.0f    } */
    /*                         }; */

    /* float cos = cosf(this->rotation), sin = sinf(this->rotation); */
    /* Matrix4 rotation_mat =  { */
    /*                             { cos,      -sin,    0.0f,   0.0f    }, */
    /*                             { sin,      cos,     0.0f,   0.0f    }, */
    /*                             { 0.0f,     0.0f,    1.0f,   0.0f    }, */
    /*                             { 0.0f,     0.0f,    0.0f,   1.0f    } */
    /*                         }; */
    /* Matrix4 position_mat =  { */
    /*                             { 1.0f,     0.0f,       0.0f,   this->position.x    }, */
    /*                             { 0.0f,     1.0f,       0.0f,   this->position.y    }, */
    /*                             { 0.0f,     0.0f,       1.0f,   0.0f                }, */
    /*                             { 0.0f,     0.0f,       0.0f,   1.0f                } */
    /*                         }; */

    /* return position_mat * rotation_mat * scale_mat; */

}
