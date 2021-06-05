# ifndef HEALTH_HPP
# define HEALTH_HPP

# include <cstdint>

# include "Component.hpp"
# include "../Events/Event.hpp"

class Health : public Adven::Component
{
private:
    Adven::Event<void(Health&)> onChange;
    Adven::Event<void(Health&)> onDie;
    std::uint32_t health;
    std::uint32_t maxHealth;
public:
    Health(std::uint32_t health);
    ~Health() override = default;
public:
    auto operator=(std::uint32_t value) -> Health&;
    auto operator+=(std::uint32_t value) -> Health&;
    auto operator-=(std::uint32_t value) -> Health&;
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    [[nodiscard]] auto Value() const -> std::uint32_t;
    [[nodiscard]] auto MaxValue() const -> std::uint32_t;
    [[nodiscard]] auto OnChange() -> Adven::Event<void(Health&)>&;
    [[nodiscard]] auto OnDie() -> Adven::Event<void(Health&)>&;
};

# endif /* end of include guard: HEALTH_HPP */
