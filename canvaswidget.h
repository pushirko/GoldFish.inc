
#ifndef CANVASWIDGET_H_
#define CANVASWIDGET_H_
//#include <gl/gl.h>
#include <QGLWidget>
//#include <QtOpenGL>

class CanvasWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = 0 , const char *name = 0);
    virtual void initializeGL();
    virtual void resizeGL( int width, int height );
    virtual void paintGL();
signals:
public slots:
};


#endif
