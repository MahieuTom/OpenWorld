#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include "camera.h"


void renderScene(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
    glColor3f(1,1,1);

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glEnd();
    }

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
        glEnd();
    }

    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // init GLUT.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,600);
    // Maak viewport.
    glutCreateWindow("OpenWorld · OpenGL project");

    // Tekenen van programma.
    glutDisplayFunc(renderScene);

    Camera* cam = new Camera();
    cam->update();

    // Go Go Glut.
    glutMainLoop();

    return EXIT_SUCCESS;
}
