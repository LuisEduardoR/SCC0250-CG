// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the code to load Wavefront objects (.obj files)
    that contain 3D geometry
*/

# ifndef AMN_WAVEFRONT_OBJECT_HPP
# define AMN_WAVEFRONT_OBJECT_HPP

#include <memory>
#include <vector>
#include <string>

class Vector3;
class Vector4;

struct WavefrontObject final
{
	struct ElementMetadata final
	{
		std::shared_ptr<std::string> objectName{};
		std::shared_ptr<std::vector<std::string>> groupNames{};
		std::shared_ptr<std::string> materialName{};
		std::size_t smoothingGroupNumber{};
		std::size_t mergeGroupNumber{};
		float mergeGroupRes{};
	};

	template<typename T>
	struct Element final
	{
		ElementMetadata metadata;
		T data;
	};

	struct Face final
	{
		std::vector<std::size_t> vertexIndexes;
		std::vector<std::size_t> textureVertexIndexes;
		std::vector<std::size_t> normalVectorIndexes;
	};

	std::vector<std::string> materialLibraryFiles{};
	std::vector<Element<Vector4>> vertices{};
	std::vector<Element<Vector3>> textureVertices{};
	std::vector<Element<Vector3>> normals{};
	std::vector<Element<Face>> faces{};
};

# endif /* end of include guard: AMN_WAVEFRONT_OBJECT_HPP */
