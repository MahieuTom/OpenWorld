#include "view.h"
#include <GL/glu.h>

View::View(QWidget *parent) : QGLWidget(parent)
{
    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), this, SLOT(updateGL()) );

    setFocusPolicy(Qt::StrongFocus);

    camPos  = Coordinate(3.0, 5.0, 25.0);
    camNorm = Coordinate(0.0, 0.0,  0.0);
    camUp   = Coordinate(0.0, 1.0,  0.0);

    hRad = 0;
    vRad = 0;
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

    // Hemelsblauw canvas.
    glClearColor(0.4f,0.6f,1.0f,0.0f);

    // Go!
    timer->start(50);
}

//-------------------------------------------------------------

void View::resizeGL ( int width, int height )
{
    if ((width<=0) || (height<=0))
        return;

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

    // Nieuwe matrix:
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );

    gluLookAt(camPos.x,  camPos.y,  camPos.z,  // Positie.
              camNorm.x, camNorm.y, camNorm.z, // Kijk naar punt.
              camUp.x,   camUp.y,   camUp.z);  // Welke kant omhoog.

    // Assenstelsel tekenen.
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

    // Opslaan:
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix( );
}

//-------------------------------------------------------------

void View::keyPressEvent( QKeyEvent * e ) {

    if(e->key() == Qt::Key_Up) { // Vooruit
        this->camPos.z -= 0.5;
        this->camNorm.z -= 0.5;
    } if(e->key() == Qt::Key_Down) { // Achteruit
        this->camPos.z += 0.5;
        this->camNorm.z += 0.5;
    } if(e->key() == Qt::Key_Right) { // Rechts
        this->camPos.x += 0.5;
        this->camNorm.x += 0.5;
    } if(e->key() == Qt::Key_Left) { // Links
        this->camPos.x -= 0.5;
        this->camNorm.x -= 0.5;
    }

    if(e->key() == Qt::Key_PageUp) {
        RotateView(0.5f,0.0f);
    } if(e->key() == Qt::Key_PageDown) {
        RotateView(-.5f,0.0f);
    }

    // this->camNorm.y -= 0.5; --> Naar beneden kijken.
    // --------------------------------------------------------
    // this->camPos.z += 0.5;  --> Over X-as bewegen.
    // this->camNorm.z += 0.5;
    // --------------------------------------------------------
    //
}

//-------------------------------------------------------------

void View::RotateView(float horizontal, float vertical)
{
  hRad += horizontal;
  vRad += vertical;

  camNorm.x = cos(vRad) * sin(hRad);
  camNorm.y = -sin(vRad);
  camNorm.z = cos(vRad) * sin(hRad);

  camUp.x = sin(vRad) * sin(hRad);
  camUp.y = cos(vRad);
  camUp.z = sin(vRad) * cos(hRad);
}
