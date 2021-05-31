// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the class that handles the game scene
*/

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Scene.hpp"
#include "../Rendering/Renderer.hpp"

class TestScene : public Adven::Scene
{
public:
    TestScene();
    ~TestScene() override = default;
};

#endif /* end of include guard: GAME_SCENE_HPP */