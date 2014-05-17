#ifndef VIEW_H
#define VIEW_H

#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include "coordinate.h"

class View : public QGLWidget
{
    Q_OBJECT

public:
    View(QWidget *parent=0);
    ~View();

protected:
    void initializeGL ();
    void resizeGL ( int width, int height );
    void paintGL ();

    void keyPressEvent(QKeyEvent * e);

    void RotateView(float horizontal, float vertical);

private:
    Coordinate camPos;
    Coordinate camNorm;
    Coordinate camUp;

    float hRad;
    float vRad;

    QTimer* timer;
};


#endif // VIEW_H
