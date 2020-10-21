#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
{
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::paintGL()
{
    if(camera != NULL)
    {
        Graphics::Draw(camera);
    }
}

void OpenGLWidget::initializeGL()
{
    if(Graphics::Initialize())
    {
        doneCurrent();
    }
}

void OpenGLWidget::AddCamera(Camera camera)
{
    this->camera = camera;
}