#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include "camera.h"
#include "Loader.h"
#include <vector>



void init();
void reshape(int w, int h);
void clearRam();
void OnExit();
void menu(int id);
void changeDisplayType();
void keyPress(int key, int x, int y);
void mouseMove(int x, int y);
void mouseButton(int button, int state, int x, int y);

std::vector<ObjectModel*> models;
Camera* cam;
int mainWindow;

enum displayType {
    WIRE,
    SMOOTHSHADED,
    FLATSHADED
} drawType;

bool flashOn;

/**
 * Teken de scene.
 */
void renderScene(void) {
    glutSetWindow(mainWindow);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, 0);


    cam->update();


    if (flashOn) {
        //flashlight
        Coordinate camPos = cam->getCamPos();
        Coordinate camLook = cam->getCamLook();
        GLfloat flashPos[] = {(GLfloat) camPos.x, (GLfloat) camPos.y, (GLfloat) camPos.z, 1};
        GLfloat flashDir[] = {(GLfloat) camPos.x + (GLfloat) camLook.x, (GLfloat) camPos.y + (GLfloat) camLook.y, (GLfloat) camPos.z + (GLfloat) camLook.z};
        glLightfv(GL_LIGHT1, GL_POSITION, flashPos);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, flashDir);

        glEnable(GL_LIGHT1);
        //flashOn = false;
    } else {
        glDisable(GL_LIGHT1); 
    }

    glTranslatef(0, 2.4, 0);
    glutSolidTeapot(0.3);
    glTranslatef(0, -2.4, 0);
    
    for (unsigned int i = 0; i < models.size(); i++) {
        models.at(i)->Draw();
    }
    

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // init GLUT.

    flashOn = false;

    drawType = SMOOTHSHADED;
    changeDisplayType();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    // Maak viewport.
    mainWindow = glutCreateWindow("OpenWorld - OpenGL project");

    // Tekenen van programma.
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);

    // Camera manipulatie
    glutSpecialFunc(keyPress);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    glutCreateMenu(menu);
    glutAddMenuEntry("Wire", 0);
    glutAddMenuEntry("Flat shading", 1);
    glutAddMenuEntry("Smooth shading", 2);
    glutAddMenuEntry("Quit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);


    init();

    Loader* loader = new Loader();
    models = loader->parseXML();
    if (loader->getCam() == NULL) {
        cam = new Camera();
    } else {
        cam = loader->getCam();
    }
    delete loader;

    atexit(OnExit);

    // Go Go Glut.
    glutMainLoop();


    //delete everything
    //clearRam(); //TODO

    return EXIT_SUCCESS;
}

void init() {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    GLfloat amb_light[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat diffuse[] = {0.6, 0.6, 0.6, 1};
    GLfloat specular[] = {0.7, 0.7, 0.3, 1};
    GLfloat pos[] = {-20, 50, 50, 0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    //flashlight
    GLfloat diffuse1[] = {0.1, 0, 0, 1};
    GLfloat specular1[] = {1, 0.2, 0.2, 1};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 128.0);

    GLfloat flashPos[] = {0, 2, 0, 1};
    GLfloat flashDir[] = {0, 0, 0};
    glLightfv(GL_LIGHT1, GL_POSITION, flashPos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, flashDir);
    glEnable(GL_LIGHT1);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
        glMateriali(GL_FRONT, GL_SHININESS,128);

    // enable texturing
    glEnable(GL_TEXTURE_2D);

    // tell openGL to generate the texture coords for a sphere map
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

    // enable automatic texture coordinate generation
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

}

void reshape(int w, int h) {
    if (h == 0) {
        h = 1;
    }
    //glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 1.0, 10000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OnExit() {
    clearRam();
}

void clearRam() {
    delete cam;
    for (unsigned int i = 0; i < models.size(); i++) {
        delete models.at(i);
    }
}

void menu(int id) {
    if (id == 3) {
        exit(0);
    } else if (id == 0) {
        drawType = WIRE;
        changeDisplayType();
        glutPostRedisplay();
    } else if (id == 1) {
        drawType = FLATSHADED;
        changeDisplayType();
        glutPostRedisplay();
    } else if (id == 2) {
        drawType = SMOOTHSHADED;
        changeDisplayType();
        glutPostRedisplay();
    }
}

void changeDisplayType() {

    if (drawType == WIRE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (drawType == FLATSHADED) {
        glEnable(GL_FLAT);
        glShadeModel(GL_FLAT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (drawType == SMOOTHSHADED) {
        glEnable(GL_SMOOTH);
        glShadeModel(GL_SMOOTH);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

/**
 * Als er een toest wordt ingedrukt handel het hier af.
 */
void keyPress(int key, int x, int y) {
    cam->keyPress(key, x, y);
    switch (key) {
        case GLUT_KEY_F5:
            flashOn = !flashOn;
            break;
    }
    glutPostRedisplay();
}

/**
 * Een bewegin op het scherm?
 */
void mouseMove(int x, int y) {
    cam->mouseMove(x, y);
    glutPostRedisplay();
}

/**
 * Muisknop ingedrukt?
 */
void mouseButton(int button, int state, int x, int y) {
    cam->mouseButton(button, state, x, y);
    glutPostRedisplay();
}