#include "camera.h"

/**
 * Initialiseer Toestenbord & Muis.
 */
Camera::Camera() {
    camPos = Coordinate(10.0, 10.0, 25.0);
    lookAt = Coordinate(0.0, 0.0,  0.0);
    upAxis = Coordinate(0.0, 1.0,  0.0);

    deltaAngle = 0.0f;
    angle = 0.0f;
    pace = 0.5;

    //glutKeyboardFunc(processNormalKeys);
    //glutSpecialFunc(Camera::keyPress);
    //glutMotionFunc(Camera::mouseMove);
}

//-------------------------------------------------------------

void Camera::update() {
    lookAt.x = cos(angle) * cos(angle);
    lookAt.y = sin(angle);
    lookAt.z = sin(angle) * cos(angle);

    //m_strafe_lx = cos(angle - M_PI_2);
    //m_strafe_lz = sin(angle - M_PI_2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camPos.x, camPos.y, camPos.z,
              camPos.x + lookAt.x, camPos.y + lookAt.y, camPos.z + lookAt.z,
              upAxis.x,upAxis.y,upAxis.z);
}

/*void Camera::keyPress(int key, int x, int y) {
    // this->camNorm.y -= 0.5; --> Naar beneden kijken.
    // --------------------------------------------------------
    // this->camPos.z += 0.5;  --> Over X-as bewegen.
    // this->camNorm.z += 0.5;
    // --------------------------------------------------------
    //

    float fraction = 0.1f;
/*
    switch (key) {
        case GLUT_KEY_LEFT :
            angle -= 0.01f;
            lookAt.x = sin(angle);
            lookAt.z = -cos(angle);
            break;
        case GLUT_KEY_RIGHT :
            angle += 0.01f;
            lookAt.x = sin(angle);
            lookAt.z = -cos(angle);
            break;
        case GLUT_KEY_UP :
            camPos.x += lookAt.x * fraction;
            camPos.z += lookAt.z * fraction;
            break;
        case GLUT_KEY_DOWN :
            camPos.x -= lookAt.x * fraction;
            camPos.z -= lookAt.z * fraction;
            break;
    }*//*

    x=0, y=0;
}

//-------------------------------------------------------------

void Camera::mouseMove(int x, int y) {
    /*
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    //TODO:

    double dx, dy;
    if ((cursorPos.x != lookAt.x) || (cursorPos.y != lookAt.y)) {
        dx = cursorPos.x - lookAt.x - viewportWidth/2;
        dy = cursorPos.y - lookAt.y - viewportHeight/2;

        //lookAt.x += dx;
        //lookAt.y += dy;
        //lookAt.z;

        lookAt.x =  cos(dy) * sin(dx);
        lookAt.y = -sin(dy);
        lookAt.z =  cos(dy) * sin(dx);

        //lookAt.x += dx;
        //lookAt.y += dx;
        //lookAt.z += dy;
    }

    //SetCursorPos(viewportWidth/2, viewportHeight/2);
    //
    *//*


    // update deltaAngle
    deltaAngle = (x + 1) * 0.001f;

    // update camera's direction
    lookAt.x = sin(angle + deltaAngle);
    lookAt.z = -cos(angle + deltaAngle);

    x=0, y=0;
}*/