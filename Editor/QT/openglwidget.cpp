#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
{
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::paintGL()
{

}

void OpenGLWidget::initializeGL()
{
    //if(Graphics::Initialize())
   // {
    //    doneCurrent();
   // }
}
#include "moc_openglwidget.cpp"