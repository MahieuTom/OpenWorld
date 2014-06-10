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
    Model(QString modeltype, QString modelpad);
    Model(const Model& orig);
    
    bool loadModel();
    int loadOBJ();
    
    float* calculateNormal( float *coord1, float *coord2, float *coord3 );
    
    void Draw();
    
    void setTexture(unsigned int texture);
    
    virtual ~Model();
private:
    QString modeltype;
    QString modelpad;
    
    float* Faces_Triangles;				// Stores the triangles
    float* normals;                                     // Stores the normals
    long TotalConnectedTriangles;			// Stores the total number of connected triangles
    
    unsigned int texture;
};

#endif	/* MODEL_H */

