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
