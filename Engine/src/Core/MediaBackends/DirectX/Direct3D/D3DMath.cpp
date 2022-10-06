#include "D3DMath.h"

typedef Matrix<float, 4, 4> Matrix;

XMVECTOR D3DMath::Vector3ToDXM(const Vector3 v)
{
    return XMVECTOR(v.x, v.y, v.z);
}

XMMATRIX D3DMath::MatrixToDXM(const Matrix m)
{
    return XMMATRIX(m);
}

Matrix D3DMath::DXMToMatrix(const XMMATRIX m)
{
    return Matrix(m);
};

Matrix D3DMath::GeneratePerspectiveMatrix(float fov, uint window_width, uint window_height)
{
    return DXMToMatrix(XMMatrixPerspectiveFovRH(XMConvertToRadians(fov), (float) window_width / (float) window_height, 0.1f, 1000.0f));
}

Matrix D3DMath::GenerateViewMatrix(Vector3 position, Vector3 looking_at, Vector3 up)
{
    return DXMToMatrix(XMMatrixLookAtRH(Vector3ToDXM(position), Vector3ToDXM(looking_at), Vector3ToDXM(up)));

}

Matrix D3DMath::IdentityMatrix()
{
    return DXMToMatrix(XMMatrixIdentity());
}

Matrix D3DMath::GenerateModelMatrix(Vector3 position, Vector3 rotation, Vector3 scale)
{
    //TODO Inputs May Be Incorrect
    return DXMToMatrix(XMMatrixTransformation(
        Vector3ToDXM(position),
        Vector3ToDXM(scale),
        Vector3ToDXM(scale),
        Vector3ToDXM(position),
        Vector3ToDXM(rotation),
        Vector3ToDXM(position)
    ));
}

Matrix D3DMath::GenerateMVP(Matrix model, Matrix view, Matrix projection)
{
    XMMatrix model_dxm = MatrixToDXM(model);
    XMMatrix view_dxm = MatrixToDXM(view);
    XMMatrix projection_dxm = MatrixToDXM(projection);

    XMMatrix mv = XMMatrixMultiply(model, view);
    return DXMToMatrix(XMMatrixMultiply(mv, projection);
}

//projection * XMMATRIX(glm::mat3(view));
