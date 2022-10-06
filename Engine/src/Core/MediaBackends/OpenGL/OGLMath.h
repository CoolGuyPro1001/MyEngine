#ifndef OGLMATH_H
#define OGLMATH_H

#include "Core/Media/GraphicsMedia.h"

struct Vector3;

template<typename T, std::size_t R, std::size_t C>
struct Matrix;

class OGLMath : public GraphicsMath
{
private:
    glm::vec3 Vector3ToGLM(const Vector3 v);
    glm::mat4 MatrixToGLM(Mat4 m);
    Mat4 GLMToMatrix(const glm::mat4 m, bool row_major = true);

    Mat4 GenerateModelMatrix(Vector3 position, Vector3 rotation, Vector3 scale);
    Mat4 GenerateViewMatrix(Vector3 position, Vector3 looking_at, Vector3 up);
    Mat4 GeneratePerspectiveMatrix(float fov, uint window_width, uint window_height);
    Mat4 GenerateMVP(Mat4 model, Mat4 view, Mat4 projection);

    Mat4 IdentityMatrix();
    void MVPToSkyBoxMVP(Mat4& mvp);
    //Matrix<float, 4, 4> TransformationMatrix(Vector3 position, Vector3 rotation, Vector3 scale);

};

#endif
