#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
{
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::paintGL()
{
    Graphics::Draw();
}

void OpenGLWidget::initializeGL()
{
    if(Graphics::Initialize())
    {
        doneCurrent();
    }
}