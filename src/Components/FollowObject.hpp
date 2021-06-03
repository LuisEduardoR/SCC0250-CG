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
