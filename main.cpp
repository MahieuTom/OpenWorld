#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include "camera.h"
#include "Loader.h"
#include <vector>

void init();
void reshape(int w, int h);

std::vector<Model*> models;
Camera* cam;

void renderScene(void) {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    cam->update();

    glColor3f(0, 1.0, 1.0);
    glutWireTeapot(0.5);
    
    glPushMatrix();
    glColor3f(1, 1, 1);

    for (int i = -50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glEnd();
    }

    for (int i = -50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
        glEnd();
    }

    
    
    for (unsigned int i = 0; i < models.size(); i++) {
        //glPushMatrix();
        models.at(i)->Draw();
        //glPopMatrix();
    }
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // init GLUT.
    Loader* loader = new Loader();
    models = loader->parseXML();
    
    cam = new Camera();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    // Maak viewport.
    glutCreateWindow("OpenWorld - OpenGL project");

    
    
    // Tekenen van programma.
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);

    
    
    
    init();
    
    // Go Go Glut.
    glutMainLoop();

    return EXIT_SUCCESS;
}

void init() {
    /*  select clearing (background) color       */
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth( 1.0f );

    /*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glShadeModel( GL_SMOOTH );
    //glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    
    GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
    GLfloat pos[] = { 0, 50, -100, 0 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    glLightfv( GL_LIGHT0, GL_POSITION, pos );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glShadeModel( GL_SMOOTH );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); 
}

void reshape(int w, int h) {
    //glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    //glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 1.0, 10000.0);
    //glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
