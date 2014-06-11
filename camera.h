/* 
 * File:   camera.h
 * Author: Tom Mahieu <tom.mahieu@student.uhasselt.be>
 * 
 * Created on May 17, 2014, 2;29 PM
 */
#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "coordinate.h"

class Camera {
private:
    Coordinate camPos;
    Coordinate lookAt;
    Coordinate upAxis;
    float deltaAngle;
    float angle;
    double pace;
    int xOrigin;
public:
    Camera();
    ~Camera() { }
    void update();
    void keyPress(int key, int x, int y);
    void mouseMove(int x, int y);
    void mouseButton(int button, int state, int x, int y);
};

#endif // CAMERA_H