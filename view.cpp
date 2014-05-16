#include "view.h"
#include <GL/glu.h>

View::View(QWidget *parent) : QGLWidget(parent)
{
    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), this, SLOT(updateGL()) );

    setFocusPolicy(Qt::StrongFocus);

    camPosX = 3.0;
    camPosY = 5.0;
    camPosZ = 25.0;

    camViewX = 0.0;
    camViewY = 0.0;
    camViewZ = 0.0;

    camUpX = 0.0;
    camUpY = 1.0;
    camUpZ = 0.0;
}

//-------------------------------------------------------------

View::~View()
{
}

//-------------------------------------------------------------

void View::initializeGL ()
{
    // Eerst de ouder initializeren.
    QGLWidget::initializeGL();

    glShadeModel(GL_SMOOTH);

    // Blauw canvas.
    glClearColor(0.4f,0.6f,1.0f,0.0f);

    // Go!
    timer->start(50);
}

//-------------------------------------------------------------

void View::resizeGL ( int width, int height )
{
    if ((width<=0) || (height<=0))
        return;

    //set viewport
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //set persepective
    //change the next line order to have a different perspective
    GLdouble aspect_ratio=(GLdouble)width/(GLdouble)height;
    gluPerspective(40.0f, aspect_ratio, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//-------------------------------------------------------------

void View::paintGL ()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // store current matrix
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );

    gluLookAt(camPosX,  camPosY,  camPosZ,  // Vooruit.
              camViewX, camViewY, camViewZ, //
              camUpX,   camUpY,   camUpZ);  // Welke kant omhoog?

    //Draw Axes
    glDisable( GL_LIGHTING );
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
    glEnable( GL_LIGHTING );

    // restore current matrix
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix( );
}

//-------------------------------------------------------------

void View::keyPressEvent( QKeyEvent * e ) {

    if(e->key() == Qt::Key_Up) {
        this->camPosZ -= 0.5;
        this->camViewZ -= 0.5;
    } if(e->key() == Qt::Key_Down) {
        this->camPosZ += 0.5;
        this->camViewZ += 0.5;
    } if(e->key() == Qt::Key_Right) {
        this->camPosX += 0.5;
        this->camViewX += 0.5;
    } if(e->key() == Qt::Key_Left) {
        this->camPosX -= 0.5;
        this->camViewX -= 0.5;
    }

    if(e->key() == Qt::Key_PageUp) {
        this->camViewX += 0.5;
        this->camViewZ -= 0.5;
    } if(e->key() == Qt::Key_PageDown) {
        this->camViewX -= 0.5;
        this->camViewZ += 0.5;
    }

    // this->camViewY -= 0.5; --> Naar beneden kijken.
    // --------------------------------------------------------
    // this->camPosZ += 0.5;  --> Over X-as bewegen.
    // this->camViewZ += 0.5;
    // --------------------------------------------------------
    //
}
