// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the class that handles generating random points to use for the sky
*/

#ifndef AMN_POISSON_DISC_SAMPLING_HPP
#define AMN_POISSON_DISC_SAMPLING_HPP

#include "../Math/Vector.hpp"

#include <cstdint>
#include <vector>


namespace amn::PoissonDiscSampler
{
auto GeneratePoints(float radius, Vector2 sampleRegionSize, std::uint32_t numSamplesBeforeRejection = 30)
	-> std::vector<Vector2>;
}

#endif /* end of include guard: AMN_POISSON_DISC_SAMPLING_HPP */
