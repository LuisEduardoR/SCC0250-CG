# include "Health.hpp"

Health::Health(std::uint32_t health) : health(health), maxHealth(health) {}

auto Health::operator=(std::uint32_t value) -> Health&
{
    if (health != 0 && value == 0)
    {
        health = 0;
        onChange.Raise(*this);
        onDie.Raise(*this);
    }
    else
    {
        health = value;
        onChange.Raise(*this);
    }

    return *this;
}

auto Health::operator+=(std::uint32_t value) -> Health&
{
    health += value;
    onChange.Raise(*this);
    return *this;
}

auto Health::operator-=(std::uint32_t value) -> Health&
{
    if (value >= health)
    {
        health = 0;
        onChange.Raise(*this);
        onDie.Raise(*this);
    }
    else
    {
        health -= value;
        onChange.Raise(*this);
    }

    return *this;
}


[[nodiscard]] auto Health::Clone() const -> std::unique_ptr<Component>
{
    return std::make_unique<Health>(health);
}

[[nodiscard]] auto Health::Value() const -> std::uint32_t { return health; }

[[nodiscard]] auto Health::MaxValue() const -> std::uint32_t { return maxHealth; }

[[nodiscard]] auto Health::OnChange() -> Adven::Event<void(Health&)>& { return onChange; }

[[nodiscard]] auto Health::OnDie() -> Adven::Event<void(Health&)>& { return onDie; }
