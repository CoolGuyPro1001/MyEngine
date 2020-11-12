#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Graphics/Camera.h"

#include <QOpenGLWidget>
#include <QKeyEvent>
#include <iostream>


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

#endif // OPENGLWIDGET_H
