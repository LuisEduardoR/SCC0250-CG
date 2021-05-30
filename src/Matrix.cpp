# include "Matrix.hpp"

// Matrix4 ====================================

Matrix4::Matrix4(Vector4 i, Vector4 j, Vector4 k, Vector4 l) {
    this->i = i;
    this->j = j;
    this->k = k;
    this->l = l;
}

// Operators
Matrix4 Matrix4::operator*(const Matrix4& m) {

    // TODO: Use a for loop
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

[[nodiscard]] auto operator*(const Matrix4& a, Vector4 b) -> Vector4
{
    return Vector4{
        a.i.x * b.x + a.i.y * b.y + a.i.z * b.z + a.i.w * b.w,
        a.j.x * b.x + a.j.y * b.y + a.j.z * b.z + a.j.w * b.w,
        a.k.x * b.x + a.k.y * b.y + a.k.z * b.z + a.k.w * b.w,
        a.l.x * b.x + a.l.y * b.y + a.l.z * b.z + a.l.w * b.w,
    };
}
