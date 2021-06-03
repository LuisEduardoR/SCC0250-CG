#ifndef WRAP_AROUND_HPP
#define WRAP_AROUND_HPP

#include "Component.hpp"
#include "Player.hpp"
#include <memory>

class WrapAround : public Adven::Component
{
public:
    ~WrapAround() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto VDrawUpdate() -> void override;
};

#endif /* end of include guard: WRAP_AROUND_HPP */
