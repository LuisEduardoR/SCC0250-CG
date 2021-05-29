// Abner Eduardo Silveira Santos - NUSP 10692012
// Amanda de Moura Peres - NUSP 10734522
// Luís Eduardo Rozante de Freitas Pereira - NUSP 10734794
// Desenvolvido para a disciplina:
//  SCC0250 - Computação Gráfica (2021)
//  Prof. Ricardo M. Marcacini

# include "Geometry.hpp"

// Vector2 ====================================

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

// Vector3 ====================================

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

// Vector4 ====================================

Vector4::Vector4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

// Matrix4 ====================================

Matrix4::Matrix4(Vector4 i, Vector4 j, Vector4 k, Vector4 l) {
    this->i = i;
    this->j = j;
    this->k = k;
    this->l = l;
}

// Operators
Matrix4 Matrix4::operator*(const Matrix4& m) {

    return  {
                {
                    (this->i.x * m.i.x) + (this->i.y * m.j.x) + (this->i.z * m.k.x) + (this->i.w * m.l.x), 
                    (this->i.x * m.i.y) + (this->i.y * m.j.y) + (this->i.z * m.k.y) + (this->i.w * m.l.y),  
                    (this->i.x * m.i.z) + (this->i.y * m.j.z) + (this->i.z * m.k.z) + (this->i.w * m.l.z),  
                    (this->i.x * m.i.w) + (this->i.y * m.j.w) + (this->i.z * m.k.w) + (this->i.w * m.l.w), 
                },
                {
                    (this->j.x * m.i.x) + (this->j.y * m.j.x) + (this->j.z * m.k.x) + (this->j.w * m.l.x), 
                    (this->j.x * m.i.y) + (this->j.y * m.j.y) + (this->j.z * m.k.y) + (this->j.w * m.l.y),  
                    (this->j.x * m.i.z) + (this->j.y * m.j.z) + (this->j.z * m.k.z) + (this->j.w * m.l.z),  
                    (this->j.x * m.i.w) + (this->j.y * m.j.w) + (this->j.z * m.k.w) + (this->j.w * m.l.w),
                }, 
                {
                    (this->k.x * m.i.x) + (this->k.y * m.j.x) + (this->k.z * m.k.x) + (this->k.w * m.l.x), 
                    (this->k.x * m.i.y) + (this->k.y * m.j.y) + (this->k.z * m.k.y) + (this->k.w * m.l.y),  
                    (this->k.x * m.i.z) + (this->k.y * m.j.z) + (this->k.z * m.k.z) + (this->k.w * m.l.z),  
                    (this->k.x * m.i.w) + (this->k.y * m.j.w) + (this->k.z * m.k.w) + (this->k.w * m.l.w), 
                },
                {
                    (this->l.x * m.i.x) + (this->l.y * m.j.x) + (this->l.z * m.k.x) + (this->l.w * m.l.x), 
                    (this->l.x * m.i.y) + (this->l.y * m.j.y) + (this->l.z * m.k.y) + (this->l.w * m.l.y),  
                    (this->l.x * m.i.z) + (this->l.y * m.j.z) + (this->l.z * m.k.z) + (this->l.w * m.l.z),  
                    (this->l.x * m.i.w) + (this->l.y * m.j.w) + (this->l.z * m.k.w) + (this->l.w * m.l.w), 
                }
            };

}

// Line =======================================

Line::Line(Vector2 a, Vector2 b) {
    this->a = a;
    this->b = b;
}

// Polyline ===================================

Polyline::Polyline() {
    points.clear();
}

Polyline::Polyline(Vector2 a, Vector2 b) {
    this->points.push_back(a);
    this->points.push_back(b);
}

Polyline::Polyline(std::vector<Vector2> points) {
    this->points = points;
}

// Triangle ===================================

Triangle::Triangle(Vector2 a, Vector2 b, Vector2 c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

// Quad =======================================

Quad::Quad(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

// Circle =====================================

Circle::Circle(Vector2 center, float radius, int precision) {
    this->center = center;
    this->radius = radius;
    this->precision = precision;
}

// Returns a approximation of the Circle represented by a vector with a certain number of points
std::vector<Vector2> Circle::GetPoints() const {

    // Calculates some points to represent the circle
    std::vector<Vector2> points;
    float angle = 0.0;
    for(int i = 0; i < this->precision; i++){
        angle += (2.0f * CONST_PI) / this->precision;
        float x = this->center.x + cos(angle) * this->radius;
        float y = this->center.y + sin(angle) * this->radius;
        points.push_back(Vector2(x, y));
    }

    return points;

}

// Triangle3D =================================
Triangle3D::Triangle3D(Vector3 a, Vector3 b, Vector3 c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

// Mesh3D =====================================

Mesh3D::Mesh3D(std::vector<Triangle3D> triangles) {
    this->triangles = triangles;
}

// Returns the triangles of our mesh
std::vector<Triangle3D> Mesh3D::GetTriangles() const {
    return this->triangles;
}