#include "Component.hpp" 

namespace Adven
{

auto Component::GetGameObject() const -> const GameObject* { return gameObject; }

auto Component::GetGameObject() -> GameObject* { return gameObject; }

} /* Adven */ 
