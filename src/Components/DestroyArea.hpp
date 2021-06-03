#ifndef DESTROY_AREA_HPP
#define DESTROY_AREA_HPP

#include "Component.hpp"
#include "../Math/Vector.hpp"

class DestroyArea : public Adven::Component
{
public:
    DestroyArea(Vector3 min, Vector3 max);
    ~DestroyArea() override = default;

public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto VDrawUpdate() -> void override;
    
public:
    Vector3 min;
    Vector3 max;
};

#endif /* end of include guard: DESTROY_AREA_HPP */
