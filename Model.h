/* 
 * File:   Model.h
 * Author: Ralph Bisschops <ralph.bisschops@student.uhasselt.be>
 *
 * Created on June 9, 2014, 3:20 PM
 */

#ifndef MODEL_H
#define	MODEL_H

#include "coordinate.h"

#include <QtCore/QString>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>



#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9

class Model {
public:
    Model();
    Model(int xpos, int ypos, int zpos, int xsize, int ysize, int zsize, QString modeltype, QString modelpad);
    Model(const Model& orig);
    
    bool loadModel();
    int loadOBJ();
    
    float* calculateNormal( float *coord1, float *coord2, float *coord3 );
    
    void Draw();
    
    virtual ~Model();
private:
    Coordinate* pos;
    int xsize;
    int ysize;
    int zsize;
    QString modeltype;
    QString modelpad;
    
    float* Faces_Triangles;				// Stores the triangles
    float* normals;                                     // Stores the normals
    long TotalConnectedTriangles;			// Stores the total number of connected triangles
};

#endif	/* MODEL_H */

