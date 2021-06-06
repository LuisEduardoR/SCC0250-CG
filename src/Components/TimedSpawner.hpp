// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the TimedSpawner component
    Causes this GameObject to spawn other GameObjects
    with time
*/

#ifndef TIMED_SPAWNER_HPP
#define TIMED_SPAWNER_HPP

# include "Component.hpp"

namespace Adven
{
class GameObject;
}

class TimedSpawner : public Adven::Component
{
public:
    TimedSpawner(std::shared_ptr<Adven::GameObject> prefab, float timeToSpawn);
    ~TimedSpawner() override = default;
public:
    [[nodiscard]] auto Clone() const -> std::unique_ptr<Component> override;
    auto Start() -> void override;
    auto VDrawUpdate() -> void override;
public:
    std::shared_ptr<Adven::GameObject> prefab;
    float timeToSpawn;
    float startTime;
};

#endif /* end of include guard: TIMED_SPAWNER_HPP */
