#include "OGLMath.h"

#include "Common/Vector3.h"
#include "Common/Matrix.h"
#include "Core/Time.h"

glm::vec3 OGLMath::Vector3ToGLM(const Vector3 v)
{
    return glm::vec3(v.x, v.y, v.z);
}

glm::mat4 OGLMath::MatrixToGLM(Mat4 m)
{
    return glm::mat4
    (
        m[0][0], m[1][0], m[2][0], m[3][0],
        m[0][1], m[1][1], m[2][1], m[3][1],
        m[0][2], m[1][2], m[2][2], m[3][2],
        m[0][3], m[1][3], m[2][3], m[3][3]
    );
}

Mat4 OGLMath::GLMToMatrix(const glm::mat4 m, bool row_major)
{
    Mat4 matrix;

    memcpy(matrix.data, &m[0], 16 * sizeof(float));

    if(row_major)
    {
        for(int r = 0; r <= 2; r++)
        {
            for(int c = r + 1; c <= 3; c++)
            {
                std::swap(matrix[r][c], matrix[c][r]);
            }
        }
    }

    return matrix;
};

Mat4 OGLMath::GeneratePerspectiveMatrix(float fov, uint window_width, uint window_height)
{
    return GLMToMatrix(glm::perspective(glm::radians(fov), (float) window_width / (float) window_height, 0.1f, 1000.0f));
}

Mat4 OGLMath::GenerateViewMatrix(Vector3 position, Vector3 looking_at, Vector3 up)
{
    return GLMToMatrix(glm::lookAt(Vector3ToGLM(position), Vector3ToGLM(looking_at), Vector3ToGLM(up)));
}

Mat4 OGLMath::GenerateModelMatrix(Vector3 position, Vector3 rotation, Vector3 scale)
{
    glm::mat4 rotation_matrix =
        glm::rotate(glm::radians(rotation.pitch), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(rotation.yaw), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::radians(rotation.roll), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 translate_matrix = glm::translate(Vector3ToGLM(position));
    glm::mat4 scale_matrix = glm::scale(Vector3ToGLM(scale));

    glm::mat4 model = translate_matrix * scale_matrix * rotation_matrix;
    return GLMToMatrix(model);
}

Mat4 OGLMath::GenerateMVP(Mat4 model, Mat4 view, Mat4 projection)
{
    return GLMToMatrix(MatrixToGLM(projection) * MatrixToGLM(view) * MatrixToGLM(model), false);
}

Mat4 OGLMath::IdentityMatrix()
{
    return GLMToMatrix(glm::identity<glm::mat4>());
}

void OGLMath::MVPToSkyBoxMVP(Mat4& mvp)
{
    //The Matrix Is In Column-Major Order
    //Set Row 3 To Row 4

    for(int i = 0; i < 4; i++)
    {
        float* column = mvp[i];
        column[2] = column[3];
    }
}
