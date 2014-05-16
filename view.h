#ifndef VIEW_H
#define VIEW_H

#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QKeyEvent>

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

private:
    double camPosX,  camPosY,  camPosZ;
    double camUpX,   camUpY,   camUpZ;
    double camViewX, camViewY, camViewZ;
    QTimer* timer;
};


#endif // VIEW_H
