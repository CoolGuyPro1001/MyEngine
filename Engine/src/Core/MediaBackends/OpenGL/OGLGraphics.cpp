#include "OGLGraphics.h"

#include "OGLDebug.h"
#include "OGLMath.h"
#include "OGLTextureManager.h"

#include "OGLBuffers/OGLFrameBuffer.h"
#include "OGLBuffers/OGLIndexBuffer.h"
#include "OGLBuffers/OGLUniformBuffer.h"
#include "OGLBuffers/OGLVertexBuffer.h"

#include "Common/Error.h"
#include "Common/Vertex.h"
#include "Common/Matrix.h"

#include "Events/WindowEvents.h"

OGLRenderer::OGLRenderer(MWindow& window)
{
    vb_instance = CreateShared<OGLVertexBuffer>(m_instance_id_ptr, m_instance_vao_ptr, false);
    ib_instance = CreateShared<OGLIndexBuffer>(m_index_id_ptr, false);
    ub_model = CreateShared<OGLUniformBuffer>(m_model_id_ptr, true);
    ub_mvp = CreateShared<OGLUniformBuffer>(m_mvp_id_ptr, true);

    Shared<Delegate<void, EWindowResized*>> resize_delegate = CreateShared<Delegate<void, EWindowResized*>>();
    resize_delegate->Bind(this, &OGLRenderer::UpdateViewPort);
    window.resize_event->AddListener(resize_delegate);

    //swapbuffers_func = Delegate<void>();
    //swapbuffers_func.Bind(&window, &Window::UpdateGraphics);

    Math = CreateShared<OGLMath>();
    TextureManager = CreateShared<OGLTextureManager>();
}

void OGLRenderer::Init()
{
    GLenum error = glewInit();
    const char* c;
    if(GLEW_OK != error)
        //FatalError(OPENGL_ERROR, "GLEW Failed To Initialize\n%s",
        c = (const char*) glewGetErrorString(error);

    m_initialized = true;
    GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_max_texture_units));

    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LESS));
    GLCall(glPrimitiveRestartIndex(PRIMITIVE_RESTART));

    vb_instance->Init();
    ib_instance->Init();

    ub_model->Init(1024);
    ub_mvp->Init(1024);
}


void OGLRenderer::AddShader(const std::string vertex_path, const std::string fragment_path)
{
    uint vs = OGLCompileShader(vertex_path, GL_VERTEX_SHADER);
    uint fs = OGLCompileShader(fragment_path, GL_FRAGMENT_SHADER);

    uint program_id;
    if(OGLCreateProgram(vs, fs, program_id))
        m_shader_programs.push_back(program_id);
}

void OGLRenderer::SetUniforms()
{
    m_model_block_index = glGetUniformBlockIndex(m_shader_programs[0], "ModelBlock");
    m_mvp_block_index = glGetUniformBlockIndex(m_shader_programs[0], "MVPBlock");

    GLCall(glUniformBlockBinding(m_shader_programs[0], m_model_block_index, 0));
    GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, 0, *m_model_id_ptr));

    GLCall(glUniformBlockBinding(m_shader_programs[0], m_mvp_block_index, 1));
    GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, 1, *m_mvp_id_ptr));

    m_mvp_index_uniform = glGetUniformLocation(m_shader_programs[0], "mvp_index");
}

void OGLRenderer::UpdateViewPort(EWindowResized* e)
{
    glViewport(0, 0, (uint) e->new_size.x, (uint) e->new_size.y);
}

void OGLRenderer::SetAmbientFactor(float factor)
{
    GLCall(glUseProgram(m_shader_programs[0]));

    int ambient_uniform = glGetUniformLocation(m_shader_programs[0], "ambient_factor");
    GLCall(glUniform1f(ambient_uniform, factor));
}

void OGLRenderer::SetLightSourcePosition(Vector3 position)
{
    GLCall(glUseProgram(m_shader_programs[0]));

    int light_source_uniform = glGetUniformLocation(m_shader_programs[0], "light_source_position");
    GLCall(glUniform3f(light_source_uniform, position.x, position.y, position.z));
}

void OGLRenderer::SetLightColor(Color color)
{
    GLCall(glUseProgram(m_shader_programs[0]));

    int light_color_uniform = glGetUniformLocation(m_shader_programs[0], "light_color");

    std::array<float, 4> normalized_color = color.Normalized();
    GLCall(glUniform3f(light_color_uniform, normalized_color[0], normalized_color[1], normalized_color[2]));
}

void OGLRenderer::SetCameraPosition(Vector3 position)
{
    GLCall(glUseProgram(m_shader_programs[0]));

    int camera_position_uniform = glGetUniformLocation(m_shader_programs[0], "camera_position");
    GLCall(glUniform3f(camera_position_uniform, position.x, position.y, position.z));
}

void OGLRenderer::SetSpecularFactor(float factor)
{
    GLCall(glUseProgram(m_shader_programs[0]));

    int specular_uniform = glGetUniformLocation(m_shader_programs[0], "specular_factor");
    GLCall(glUniform1f(specular_uniform, factor));
}

void OGLRenderer::ClearDrawBuffers()
{
    if(!m_initialized) //|| shader_program == NULL_ID)
        return;

    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void OGLRenderer::DrawText(std::vector<uint> current_text_textures)
{
    /*if(!initialized || !shader_programs[1].Use())
        return;

    int texture_index = 0;
    int batch = 1;
    for(VertexBuffer& batch_buffer : batch_buffers)
    {
        if(batch_buffer.GetSize() == 0)
        {
            batch++;
            continue;
        }

        std::vector<int> texture_batch(max_texture_units);
        for(int i = 0; i < texture_batch.size(); i++)
            texture_batch[i] = i;

        uint* texture_id = &(current_text_textures[texture_index]);
        int batch_ending = max_texture_units * batch + 2;

        while((*texture_id - 2) < batch_ending && texture_index < current_text_textures.size())
        {
            int slot = (*texture_id - 2) % max_texture_units;
            GLCall(glActiveTexture(GL_TEXTURE0 + slot));
            GLCall(glBindTexture(GL_TEXTURE_2D, *texture_id));
            texture_index++;
            texture_id++;
        }

        int text_uniform = glGetUniformLocation(shader_programs[1], "text_textures");
        GLCall(glUniform1iv(text_uniform, texture_batch.size(), &texture_batch[0]));

        batch_buffer.Bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, batch_buffer.GetSize() / sizeof(Vertex)));

        batch++;
    }*/
}

bool OGLRenderer::PrepareDraw()
{
    if(!m_initialized)
        return false;

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, *m_instance_id_ptr));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_index_id_ptr));

    GLCall(glBindVertexArray(*m_instance_vao_ptr));

    GLCall(glUseProgram(m_shader_programs[0]));
    TextureManager->Use(m_shader_programs[0]);

    return true;
}

void OGLRenderer::Draw(uint indices_count, uint model_instance_amount, uint index_offset, uint mvp_index)
{
    //Draw Objects
    GLCall(glUniform1i(m_mvp_index_uniform, mvp_index));
    GLCall(glDrawElementsInstanced(GL_TRIANGLE_STRIP, indices_count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(index_offset * sizeof(ushort)), model_instance_amount));

    //Draw Widgets
    //sprite_buffer.Bind();
    //GLCall(glUniform1i(object_num_uniform, object_count));
    //GLCall(glDrawArrays(GL_TRIANGLES, 0, sprite_buffer.GetSize() / sizeof(Vertex)));
}

void OGLRenderer::DrawSkyBox(uint skybox_offset, uint skybox_mvp_index)
{
    GLCall(glDepthFunc(GL_LEQUAL));

    int mvp_index_uniform = glGetUniformLocation(m_shader_programs[0], "mvp_index");

    GLCall(glUniform1i(mvp_index_uniform, skybox_mvp_index));
    GLCall(glDrawElementsInstanced(GL_TRIANGLE_STRIP, 30, GL_UNSIGNED_SHORT, BUFFER_OFFSET(skybox_offset * sizeof(ushort)), skybox_mvp_index));

    GLCall(glDepthFunc(GL_LESS));
}

void OGLRenderer::SwapBuffers()
{
    m_swapbuffers_func.Execute();
}
