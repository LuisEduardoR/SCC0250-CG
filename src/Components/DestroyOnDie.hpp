# ifndef DESTROY_ON_DIE_HPP
# define DESTROY_ON_DIE_HPP

# include "Component.hpp"
# include "../Events/Listener.hpp"

class Health;

class DestroyOnDie : public Adven::Component
{
private:
    static auto DeathHandler(Health* health) -> void;
public:
    ~DestroyOnDie() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto Start() -> void override;
public:
    Adven::Listener<void(Health*)> deathListener{ DestroyOnDie::DeathHandler };
};

# endif /* end of include guard: DESTROY_ON_DIE_HPP */
