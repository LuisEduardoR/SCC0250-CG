// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

#include "PoissonDiscSampling.hpp"

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "Geometry.hpp"
//#include "util.hpp"

namespace amn::PoissonDiscSampler
{

namespace
{
auto IsValid(
	Vector2 newPoint, Vector2 sampleRegionSize, float cellSize, float radius,
	std::vector<Vector2> points, std::vector<std::size_t> grid, std::size_t gridSizeX,
	std::size_t gridSizeY) -> bool
{
	bool isContainedInRegion{ newPoint.x >= 0 && newPoint.x < sampleRegionSize.x && newPoint.y >= 0
							  && newPoint.y < sampleRegionSize.y };

	if (!isContainedInRegion)
	{
		return false;
	}

	Vector2 cellPos{ newPoint / cellSize };
	auto searchStartX{ static_cast<std::size_t>(std::max(0.0f, cellPos.x - 2.0f)) };
	auto searchEndX{ std::min(static_cast<std::size_t>(cellPos.x) + 2, gridSizeX - 1) };
	auto searchStartY{ static_cast<std::size_t>(std::max(0.0f, cellPos.y - 2.0f)) };
	auto searchEndY{ std::min(static_cast<std::size_t>(cellPos.y) + 2, gridSizeY - 1) };

	for (std::size_t x{ searchStartX }; x <= searchEndX; x++)
	{
		for (std::size_t y{ searchStartY }; y <= searchEndY; y++)
		{
			std::size_t gridValue{ grid[y * gridSizeY + x] };

			if (gridValue >= 1)
			{
				std::size_t pointIndex = gridValue - 1;
				float sqrDst{ (newPoint - points[pointIndex]).SqrMagnitude() };

				if (sqrDst < radius * radius)
				{
					return false;
				}
			}
		}
	}
	return true;
}
} // namespace

auto GeneratePoints(float radius, Vector2 sampleRegionSize, std::uint32_t numSamplesBeforeRejection)
	-> std::vector<Vector2>
{
	float cellSize{ radius / std::sqrt(2.0f) };

	std::size_t gridSizeX{ static_cast<std::size_t>(std::ceil(sampleRegionSize.x / cellSize)) };
	std::size_t gridSizeY{ static_cast<std::size_t>(std::ceil(sampleRegionSize.y / cellSize)) };

	std::vector<std::size_t> grid(gridSizeX * gridSizeY, 0);
	std::vector<Vector2> outputPoints{};
	std::vector<Vector2> spawnPoints{ sampleRegionSize / 2.0f };

	std::random_device rd;
	/* std::default_random_engine rng{ rd() }; */
	std::mt19937 rng{ rd() };

	while (!spawnPoints.empty())
	{
		std::size_t spawnIndex{ std::uniform_int_distribution<std::size_t>{
			0, spawnPoints.size() - 1 }(rng) };
		Vector2 spawnCenter{ spawnPoints[spawnIndex] };
		bool validPointFound{ false };

		for (std::uint32_t limiter = 0; limiter < numSamplesBeforeRejection; limiter++)
		{
			float angle{ 2.0f * CONST_PI
						 * std::uniform_real_distribution<float>{ 0.0f, 1.0f }(rng) };

			Vector2 direction{ std::sin(angle), std::cos(angle) };
			Vector2 newPoint{
				spawnCenter
				+ direction * std::uniform_real_distribution<float>{ radius, 2 * radius }(rng)
			};

			if (IsValid(
					newPoint,
					sampleRegionSize,
					cellSize,
					radius,
					outputPoints,
					grid,
					gridSizeX,
					gridSizeY))
			{
				outputPoints.push_back(newPoint);
				spawnPoints.push_back(newPoint);

				std::size_t gridX{ static_cast<std::size_t>(newPoint.x / cellSize) };
				std::size_t gridY{ static_cast<std::size_t>(newPoint.y / cellSize) };
				grid[gridY * gridSizeY + gridX] = outputPoints.size();

				validPointFound = true;
				break;
			}
		}

		if (!validPointFound)
		{
			spawnPoints.erase(spawnPoints.begin() + static_cast<std::ptrdiff_t>(spawnIndex));
		}
	}

	return outputPoints;
}
} // namespace amn
