#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "coordinate.h"

class Camera
{
private:
    Coordinate camPos;
    Coordinate lookAt;
    Coordinate upAxis;
    float deltaAngle;
    float angle;
    double pace;
public:
    Camera();
    ~Camera(){}
    void update();
    //void keyPress(int key, int x, int y);
    //void mouseMove(int x, int y);
};

#endif // CAMERA_H
