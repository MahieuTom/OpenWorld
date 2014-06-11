#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "coordinate.h"
#include "ObjectModel.h"

class Camera {
private:
    Coordinate camPos;
    Coordinate lookAt;
    Coordinate upAxis;
    float deltaAngle;
    float angle;
    double pace;
    int xOrigin;
    ObjectModel* fixObject;
public:
    Camera(ObjectModel* fixObject = NULL);
    ~Camera() { }
    void update();
    void keyPress(int key, int x, int y);
    void mouseMove(int x, int y);
    void mouseButton(int button, int state, int x, int y);
    Coordinate getCamPos();
};

#endif // CAMERA_H