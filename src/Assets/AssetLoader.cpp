// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

/*
    This file contains the base class to load assets
*/

# include "AssetLoader.hpp"

# include <iostream>
# include <fstream>
# include <sstream>

// Opens a file
template<typename T>
std::ifstream AssetLoader<T>::OpenFile(const std::string& path) {

    std::ifstream file;
	file.open(path);
	if (!file) {
		std::cout << "Failed to open file: " << path << std::endl;
        return nullptr;
	}

    return file;

}

// Closes a file
template<typename T>
void AssetLoader<T>::CloseFile(std::ifstream& file) {

    if(file)
        file.close();

}

template<>
std::string AssetLoader<std::string>::LoadAsset(const std::string& path) {
   
    // Tries to open the file
    std::ifstream file = AssetLoader::OpenFile(path);

    // Reads our entire file
    std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Closes the file
    AssetLoader::CloseFile(file);

    return contents;

}

// Functions for reading data.
void ReadPoint(ShapeCollection& collection, const std::string& lineBuffer);
void ReadLine(ShapeCollection& collection, const std::string& lineBuffer);
void ReadTriangle(ShapeCollection& collection, const std::string& lineBuffer);
void ReadQuad(ShapeCollection& collection, const std::string& lineBuffer);
void ReadCircle(ShapeCollection& collection, const std::string& lineBuffer);

template<>
ShapeCollection AssetLoader<ShapeCollection>::LoadAsset(const std::string& path) {

    // Creates our collection
    ShapeCollection collection( new std::vector<std::unique_ptr<Shape>>{});

    // Tries to open the file
    std::ifstream file = AssetLoader::OpenFile(path);

    // Stores the current line for debug purposes
    int currentLine = 0;
    do {

        // Breaks on EOF
        if(file.eof())
            break;

        // Reads a line of the file
        std::string lineBuffer;
        std::getline(file, lineBuffer);
        currentLine++;
        
        // Checks if it's an empty line
        if(lineBuffer.empty())
            continue;

        // Checks if it's not a comment
        if(lineBuffer[0] == '#')
            continue;

        // Gets the type of the shape
        const std::string divider = ": ";

        uint64_t dividerPos = lineBuffer.find(divider);
        std::string shapeType = lineBuffer.substr(0, dividerPos);
        std::string shapeBody = lineBuffer.substr(dividerPos + divider.length());

        if(shapeType.compare("Circle") == 0) {
            ReadCircle(collection, shapeBody);
        } else if(shapeType.compare("Quad") == 0) {
            ReadQuad(collection, shapeBody);
        } else if(shapeType.compare("Triangle") == 0) {
            ReadTriangle(collection, shapeBody);
        } else if(shapeType.compare("Line") == 0) {
            ReadLine(collection, shapeBody);
        } else if(shapeType.compare("Point") == 0) {
            ReadPoint(collection, shapeBody);
        } else {
            std::cout << "Invalid Shape2D (" << shapeType << ") at line " << currentLine << " of " << path << std::endl;
        }


    } while(!file.eof());

    // Closes the file
    AssetLoader::CloseFile(file);

    return collection;

}

// Interprets our shapeBody as a Point and adds it to the collection
void ReadPoint(ShapeCollection& collection, const std::string& shapeBody) {

    float verticeData[2];
    int colorData[4];

    // Reads a Point
    std::sscanf (
                    shapeBody.c_str(), 
                    " { vertices = { { %f , %f } }, color = { %d , %d , %d , %d } } ",
                    verticeData, verticeData + 1,
                    colorData, colorData + 1, colorData + 2, colorData + 3
                );

    // Adds the loaded Point to the collection
    collection->push_back   ( std::unique_ptr<Point>{ new Point {
                                                                    { verticeData[0], verticeData[1] },
                                                                    Color(colorData[0], colorData[1], colorData[2], colorData[3])
                                                                }});

}

// Interprets our shapeBody as a Line and adds it to the collection
void ReadLine(ShapeCollection& collection, const std::string& shapeBody) {

    float verticeData[4];
    int colorData[4];

    // Reads a Line
    std::sscanf (
                    shapeBody.c_str(), 
                    " { vertices = { { %f , %f } , { %f , %f } }, color = { %d , %d , %d , %d } } ",
                    verticeData, verticeData + 1, verticeData + 2, verticeData + 3,
                    colorData, colorData + 1, colorData + 2, colorData + 3
                );

    // Adds the loaded Line to the collection
    collection->push_back   ( std::unique_ptr<Line>{ new Line   {
                                                                    { verticeData[0], verticeData[1] },
                                                                    { verticeData[2], verticeData[3] },
                                                                    Color(colorData[0], colorData[1], colorData[2], colorData[3])
                                                                }});

}

// Interprets our shapeBody as a Triangle and adds it to the collection
void ReadTriangle(ShapeCollection& collection, const std::string& shapeBody) {

    float verticeData[6];
    int colorData[4];

    // Reads a triangle
    std::sscanf (
                    shapeBody.c_str(), 
                    " { vertices = { { %f , %f }, { %f , %f }, { %f , %f } }, color = { %d , %d , %d , %d } } ",
                    verticeData, verticeData + 1, verticeData + 2, verticeData + 3, verticeData + 4, verticeData + 5,
                    colorData, colorData + 1, colorData + 2, colorData + 3
                );

    // Adds the loaded triangle to the collection
    collection->push_back   ( std::unique_ptr<Triangle>{ new Triangle {
                                                                            { verticeData[0], verticeData[1] }, 
                                                                            { verticeData[2], verticeData[3] },
                                                                            { verticeData[4], verticeData[5] },
                                                                            Color(colorData[0], colorData[1], colorData[2], colorData[3])
                                                                        }});

}

// Interprets our shapeBody as a Quad and adds it to the collection
void ReadQuad(ShapeCollection& collection, const std::string& shapeBody) {

    float verticeData[8];
    int colorData[4];

    // Reads a Quad
    std::sscanf (
                    shapeBody.c_str(), 
                    " { vertices = { { %f , %f } , { %f , %f } , { %f , %f } , { %f , %f } } , color = { %d , %d , %d , %d } } ",
                    verticeData, verticeData + 1, verticeData + 2, verticeData + 3, verticeData + 4, verticeData + 5, verticeData + 6, verticeData + 7,
                    colorData, colorData + 1, colorData + 2, colorData + 3
                );

    // Adds the loaded Quad to the collection
    collection->push_back   ( std::unique_ptr<Quad>{ new Quad   {
                                                                    { verticeData[0], verticeData[1] }, 
                                                                    { verticeData[2], verticeData[3] },
                                                                    { verticeData[4], verticeData[5] },
                                                                    { verticeData[6], verticeData[7] },
                                                                    Color(colorData[0], colorData[1], colorData[2], colorData[3])
                                                                }});

}

// Interprets our shapeBody as a Circle and adds it to the collection
void ReadCircle(ShapeCollection& collection, const std::string& shapeBody) {

    float centerData[2];
    float radiusData;
    int precisionData;
    int colorData[4];

    // Reads a Circle
    std::sscanf (
                    shapeBody.c_str(), 
                    " { center = { %f , %f } , radius = %f , precision = %d , color = { %d , %d , %d , %d } } ",
                    centerData, centerData + 1,
                    &radiusData,
                    &precisionData,
                    colorData, colorData + 1, colorData + 2, colorData + 3
                );

    // Adds the loaded Circle to the collection
    collection->push_back   ( std::unique_ptr<Circle>{ new Circle   {
                                                                        { centerData[0], centerData[1] }, 
                                                                        radiusData,
                                                                        precisionData,
                                                                        Color(colorData[0], colorData[1], colorData[2], colorData[3])
                                                                    }});

}