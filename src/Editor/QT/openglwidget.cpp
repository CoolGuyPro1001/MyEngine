#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
{
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::paintGL()
{
    Graphics::Draw(buffer_id);
}

void OpenGLWidget::initializeGL()
{
    if(Graphics::Initialize())
    {
        doneCurrent();
    }
}