#include "camera.h"
#include "ObjectModel.h"

/**
 * Initialiseer Toestenbord & Muis.
 */
Camera::Camera(ObjectModel* fixObject) {
    camPos = Coordinate(-5, 1, 5);
    lookAt = Coordinate(0.0, 0.0, 0.0);
    upAxis = Coordinate(0.0, 1.0, 0.0);

    deltaAngle = 0.0f;
    angle = 0.0f;
    pace = 0.2;

    xOrigin = -1;
    this->fixObject = fixObject;
}

//-------------------------------------------------------------

void Camera::update() {
    glMatrixMode(GL_MODELVIEW);
    if(fixObject != NULL){
        camPos.y = (fixObject->getModelZ(camPos.x,camPos.z) + camPos.y)/2;
    }
    //cam boven landschape
    camPos.y += 1;
    glLoadIdentity();
    gluLookAt(camPos.x, camPos.y, camPos.z,
            camPos.x + lookAt.x, camPos.y + lookAt.y, camPos.z + lookAt.z,
            upAxis.x, upAxis.y, upAxis.z);
}

//-------------------------------------------------------------

void Camera::keyPress(int key, int x, int y) {
    float fraction = 0.1f;

    switch (key) {
        case GLUT_KEY_LEFT:
            angle -= 0.01f;
            lookAt.x = sin(angle);
            lookAt.z = -cos(angle);
            break;
        case GLUT_KEY_RIGHT:
            angle += 0.01f;
            lookAt.x = sin(angle);
            lookAt.z = -cos(angle);
            break;
        case GLUT_KEY_UP:
            /*
                        camPos.x += lookAt.x * pace;
                        camPos.z += lookAt.z * pace;
             */
            camPos.x += pace * lookAt.x; // *0.1f;
            camPos.z += pace * lookAt.z; // *0.1f;
            break;
        case GLUT_KEY_DOWN:
            /*
                        camPos.x -= lookAt.x * pace;
                        camPos.z -= lookAt.z * pace;
             */
            camPos.x -= pace * lookAt.x; // *0.1f;
            camPos.z -= pace * lookAt.z; // *0.1f;
            break;
    }
}

//-------------------------------------------------------------

void Camera::mouseMove(int x, int y) {
    // Enkel verplaatsen als linker muisknop ingedrukt wordt.
    if (xOrigin >= 0) {
        deltaAngle = (x - xOrigin) * 0.001f;
        // Verander de richting.
        lookAt.x = sin(angle + deltaAngle);
        lookAt.z = -cos(angle + deltaAngle);
    }
}

//-------------------------------------------------------------

void Camera::mouseButton(int button, int state, int x, int y) {
    // Enkel als er links wordt geklikt.
    if (button == GLUT_LEFT_BUTTON) {
        // Als het niet ingedrukt is.
        if (state == GLUT_UP) {
            angle += deltaAngle;
            deltaAngle = 0.0f;
            xOrigin = -1;
        } else { // Als het ingedrukt is.
            xOrigin = x;

        }
    }
}

Coordinate Camera::getCamPos(){
    return camPos;
}



