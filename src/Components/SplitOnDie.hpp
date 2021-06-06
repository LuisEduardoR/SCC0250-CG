#ifndef SPLIT_ON_DIE_HPP
#define SPLIT_ON_DIE_HPP

# include "Component.hpp"
# include "../Events/Listener.hpp"

namespace Adven
{
class GameObject;
}

class Health;

class SplitOnDie : public Adven::Component
{
public:
    SplitOnDie(std::shared_ptr<Adven::GameObject> prefab);
    ~SplitOnDie() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto Start() -> void override;
private:
    auto DeathHandler(Health& health) -> void;
public:
    std::shared_ptr<Adven::GameObject> prefab;
    Adven::Listener<void(Health&)> deathListener
    {
        [this](Health& health){ return DeathHandler(health); }
    };
};

#endif /* end of include guard: SPLIT_ON_DIE_HPP */
