// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Geometry.hpp"

// Point ======================================

// Returns the data necessary to render this shape
const RenderData Point::GetRenderData() const {
    return {
                // This points to the start of the first float on
                // the first Vector2 of this shape, as long as they
                // are declared in sequence on this class it will
                // work
                &(this->a),
                1,
                &(this->color),
                this->drawMode
            };
}

// Line =======================================

// Returns the data necessary to render this shape
const RenderData Line::GetRenderData() const {
    return {
                // This points to the start of the first float on
                // the first Vector2 of this shape, as long as they
                // are declared in sequence on this class it will
                // work
                &(this->a),
                2,
                &(this->color),
                this->drawMode
            };
}

// Polyline ===================================

// Returns the data necessary to render this shape
const RenderData Polyline::GetRenderData() const {
    return {
                this->vertices.data(),
                this->vertices.size(),
                &(this->color),
                this->drawMode
            };
}

// Triangle ===================================

// Returns the data necessary to render this shape
const RenderData Triangle::GetRenderData() const {
    return {
                // This points to the start of the first float on
                // the first Vector2 of this shape, as long as they
                // are declared in sequence on this class it will
                // work
                &(this->a),
                3,
                &(this->color),
                this->drawMode
            };
}

// Quad =======================================

// Returns the data necessary to render this shape
const RenderData Quad::GetRenderData() const {
    return {
                // This points to the start of the first float on
                // the first Vector2 of this shape, as long as they
                // are declared in sequence on this class it will
                // work
                &(this->a),
                4,
                &(this->color),
                this->drawMode
            };
}

// Circle =======================================

// Generates a number of points to represent an approximation of the circle based on precision
// and saves them to vertices
void Circle::GeneratePoints() {

    this->vertices.reserve(precision);
    float angle = 0.0;
    for(int i = 0; i < this->precision; i++){
        angle += (2.0f * CONST_PI) / this->precision;
        float x = this->center.x + std::cos(angle) * this->radius;
        float y = this->center.y + std::sin(angle) * this->radius;
        this->vertices.push_back({ x, y });
    }

}

// Returns the data necessary to render this shape (an approximation of the Circle represented by a certain number of vertices is used)
const RenderData Circle::GetRenderData() const {
    return {
                this->vertices.data(),
                this->vertices.size(),
                &(this->color),
                this->drawMode
            };
}

// ShapeBatch ===============================
// TODO: use ShapeBatch for most ShapeRenderers
ShapeBatch::ShapeBatch(ShapeCollection collection) {

    // Stores the total number of vertices
    uint64_t totalVertices = 0;

    // Gets the RenderData of all shapes
    std::vector<RenderData> renderData;
    for (const std::unique_ptr<Shape>& collection : *collection.get()) {
        RenderData data = collection->GetRenderData();
        renderData.push_back(data);
        totalVertices += data.vertexCount;
    }

    // Sorts the render data
    // !FIX: using Sort causes lots of weird C++ errors
    std::sort(renderData.begin(), renderData.end());

    // Allocates memory for the vertices
    vertexBuffer.reserve(totalVertices);

    // Copies the vertices to the buffer
    for(RenderData data : renderData) {
        for(uint64_t curVectorData = 0; curVectorData < data.vertexCount; curVectorData++)
            vertexBuffer.push_back(data.vertices[curVectorData]);
    }

    // Adds the first state
    stateChanges.push_back(RenderStateChange(0, renderData[0].vertexCount, Color(*renderData[0].color), renderData[0].drawMode));

    // Detects state changes
    for(uint64_t curIndex = 1; curIndex < renderData.size(); curIndex++) {

        // Tries to keep on the same stage
        if (renderData[curIndex].drawMode == renderData[curIndex - 1].drawMode      // For this, both shapes RenderData must have the same drawMode
            &&  *(renderData[curIndex].color) == *(renderData[curIndex - 1].color)  // and the same color
            &&  (   renderData[curIndex].drawMode == GL_TRIANGLES                   // Also only some drawModes allow this
                    || renderData[curIndex].drawMode == GL_POINTS 
                    || renderData[curIndex].drawMode == GL_LINES
                ) 
        ) {
            // Keeps on the same state
            stateChanges.back().vertexCount += renderData[curIndex].vertexCount;

        // A state change is necessary
        } else {
            // Gets the index that starts the new state
            uint64_t index = stateChanges.back().index + stateChanges.back().vertexCount;
            stateChanges.push_back(RenderStateChange(index, renderData[curIndex].vertexCount, Color(*renderData[curIndex].color), renderData[curIndex].drawMode));
        }

    }

}