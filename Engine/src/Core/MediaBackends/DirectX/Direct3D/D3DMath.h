#ifndef D3DMATH_H
#define D3DMATH_H

#include "Core/Media/Graphics.h"

struct Vector3;

template<typename T, std::size_t R, std::size_t C>
struct Matrix;

class D3DMath : public GraphicsMath
{
private:
    XMVECTOR Vector3ToDXM(const Vector3 v);
    XMMATRIX MatrixToDXM(const Matrix<float, 4, 4> m);
    Matrix<float, 4, 4> DXMToMatrix(const XMMATRIX m);
};

#endif
