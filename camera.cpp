/* 
 * File:   camera.cpp
 * Author: Tom Mahieu <tom.mahieu@student.uhasselt.be>
 * 
 * Created on May 17, 2014, 2;29 PM
 */
#include "camera.h"

/**
 * Initialiseer Toestenbord & Muis.
 */
Camera::Camera() {
    camPos = Coordinate(-5, 1, 5);
    lookAt = Coordinate(0.0, 0.0, 0.0);
    upAxis = Coordinate(0.0, 1.0, 0.0);

    deltaAngle = 0.0f;
    angle = 0.0f;
    pace = 0.2;

    xOrigin = -1;
		yOrigin = -1;
}

//-------------------------------------------------------------

void Camera::update() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camPos.x, camPos.y, camPos.z,
            camPos.x + lookAt.x, camPos.y + lookAt.y, camPos.z + lookAt.z,
            upAxis.x, upAxis.y, upAxis.z);
}

//-------------------------------------------------------------

void Camera::keyPress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            camPos.x += pace * lookAt.x;
            camPos.z -= pace * lookAt.z;
            break;
        case GLUT_KEY_RIGHT:
            camPos.x -= pace * lookAt.x;
            camPos.z += pace * lookAt.z;
            break;
        case GLUT_KEY_UP:
            camPos.x += pace * lookAt.x;
            camPos.z += pace * lookAt.z;
            break;
        case GLUT_KEY_DOWN:
            camPos.x -= pace * lookAt.x;
            camPos.z -= pace * lookAt.z;
            break;
    }
}

//-------------------------------------------------------------

void Camera::mouseMove(int x, int y) {
    // Enkel verplaatsen als linker muisknop ingedrukt wordt.
    if (xOrigin >= 0 && yOrigin >= 0) {
        deltaAngle = (x - xOrigin) * 0.001f;
				int deltaY = (y - yOrigin) * 0.001f;
        // Verander de richting.
        lookAt.x = sin(angle + deltaAngle);
        lookAt.z = -cos(angle + deltaAngle);
				lookAt.y += deltaY;
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
						yOrigin = -1;
        } else { // Als het ingedrukt is.
            xOrigin = x;
						yOrigin = y;
        }
    }
}