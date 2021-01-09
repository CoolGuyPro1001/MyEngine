#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <Graphics/Graphics.h>
#include <Graphics/Camera.h>

#include <QOpenGLWidget>
#include <QKeyEvent>


class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
private:

protected:
    void paintGL() override;
    void initializeGL() override;
};

#endif
