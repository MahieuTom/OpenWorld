/* 
 * File:   Model.cpp
 * Author: Ralph Bisschops <ralph.bisschops@student.uhasselt.be>
 * 
 * Created on June 9, 2014, 3:20 PM
 */

#include "Model.h"

Model::Model() {
    modeltype = "";
    modelpad = "";
    TotalConnectedTriangles = 0;
    Faces_Triangles = new float[0];
    normals = new float[0];
    texture = 0;
}

Model::Model(QString modeltype, QString modelpad) {
    this->modeltype = modeltype;
    this->modelpad = modelpad;
    TotalConnectedTriangles = 0;
    Faces_Triangles = new float[0];
    normals = new float[0];
    texture = 0;
}

Model::Model(const Model& orig) {
    this->modeltype = orig.modeltype;
    this->modelpad = orig.modelpad;
    TotalConnectedTriangles = orig.TotalConnectedTriangles;
    Faces_Triangles = orig.Faces_Triangles;
    normals = orig.normals;
}

bool Model::loadModel() {
    this->loadOBJ();
    return true;
}

int Model::loadOBJ() {

    float* vertexBuffer; // Stores the points which make the object
    long TotalConnectedPoints = 0; // Stores the total number of connected verteces

    std::string line;
    std::ifstream objFile(modelpad.toStdString().c_str());
    if (objFile.is_open()) // If obj file is open, continue
    {
        objFile.seekg(0, std::ios::end); // Go to end of the file, 
        long fileSize = objFile.tellg(); // get file size
        objFile.seekg(0, std::ios::beg); // we'll use this to register memory for our 3d model

        delete Faces_Triangles;
        delete normals;
        vertexBuffer = new float[fileSize]; // Allocate memory for the verteces
        Faces_Triangles = new float[fileSize]; // Allocate memory for the triangles
        normals = new float[fileSize]; // Allocate memory for the normals

        int triangle_index = 0; // Set triangle index to zero
        int normal_index = 0; // Set normal index to zero

        while (!objFile.eof()) // Start reading file data
        {
            getline(objFile, line); // Get line from file

            if (line.c_str()[0] == 'v') // The first character is a v: on this line is a vertex stored.
            {
                line[0] = ' '; // Set first character to 0. This will allow us to use sscanf

                sscanf(line.c_str(), "%f %f %f ", // Read floats from the line: v X Y Z
                        &vertexBuffer[TotalConnectedPoints],
                        &vertexBuffer[TotalConnectedPoints + 1],
                        &vertexBuffer[TotalConnectedPoints + 2]);

                TotalConnectedPoints += POINTS_PER_VERTEX; // Add 3 to the total connected points
            }
            if (line.c_str()[0] == 'f') // The first character is an 'f': on this line is a point stored
            {
                line[0] = ' '; // Set first character to 0. This will allow us to use sscanf

                int vertexNumber[4] = {0, 0, 0};
                sscanf(line.c_str(), "%i%i%i", // Read integers from the line:  f 1 2 3
                        &vertexNumber[0], // First point of our triangle. This is an 
                        &vertexNumber[1], // pointer to our vertexBuffer list
                        &vertexNumber[2]); // each point represents an X,Y,Z.

                vertexNumber[0] -= 1; // OBJ file starts counting from 1
                vertexNumber[1] -= 1; // OBJ file starts counting from 1
                vertexNumber[2] -= 1; // OBJ file starts counting from 1


                /********************************************************************
                 * Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y Z) (v X Y Z). 
                 * The vertexBuffer contains all verteces
                 * The triangles will be created using the verteces we read previously
                 */

                int tCounter = 0;
                for (int i = 0; i < POINTS_PER_VERTEX; i++) {
                    Faces_Triangles[triangle_index + tCounter ] = vertexBuffer[3 * vertexNumber[i] ];
                    Faces_Triangles[triangle_index + tCounter + 1 ] = vertexBuffer[3 * vertexNumber[i] + 1 ];
                    Faces_Triangles[triangle_index + tCounter + 2 ] = vertexBuffer[3 * vertexNumber[i] + 2 ];
                    tCounter += POINTS_PER_VERTEX;
                }

                /*********************************************************************
                 * Calculate all normals, used for lighting
                 */
                float coord1[3] = {Faces_Triangles[triangle_index], Faces_Triangles[triangle_index + 1], Faces_Triangles[triangle_index + 2]};
                float coord2[3] = {Faces_Triangles[triangle_index + 3], Faces_Triangles[triangle_index + 4], Faces_Triangles[triangle_index + 5]};
                float coord3[3] = {Faces_Triangles[triangle_index + 6], Faces_Triangles[triangle_index + 7], Faces_Triangles[triangle_index + 8]};
                float *norm = this->calculateNormal(coord1, coord2, coord3);

                tCounter = 0;
                for (int i = 0; i < POINTS_PER_VERTEX; i++) {
                    normals[normal_index + tCounter ] = norm[0];
                    normals[normal_index + tCounter + 1] = norm[1];
                    normals[normal_index + tCounter + 2] = norm[2];
                    tCounter += POINTS_PER_VERTEX;
                }
                delete norm;

                triangle_index += TOTAL_FLOATS_IN_TRIANGLE;
                normal_index += TOTAL_FLOATS_IN_TRIANGLE;
                TotalConnectedTriangles += TOTAL_FLOATS_IN_TRIANGLE;
            }
        }
        delete vertexBuffer;
        objFile.close(); // Close OBJ file
    } else {
        std::cout << "Unable to open file";
    }
    return 0;
}

float* Model::calculateNormal(float *coord1, float *coord2, float *coord3) {
    /* calculate Vector1 and Vector2 */
    float va[3], vb[3], vr[3], val;
    va[0] = coord1[0] - coord2[0];
    va[1] = coord1[1] - coord2[1];
    va[2] = coord1[2] - coord2[2];

    vb[0] = coord1[0] - coord3[0];
    vb[1] = coord1[1] - coord3[1];
    vb[2] = coord1[2] - coord3[2];

    /* cross product */
    vr[0] = va[1] * vb[2] - vb[1] * va[2];
    vr[1] = vb[0] * va[2] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - vb[0] * va[1];

    /* normalization factor */
    val = sqrt(vr[0] * vr[0] + vr[1] * vr[1] + vr[2] * vr[2]);

    float* norm = new float[3];
    norm[0] = vr[0] / val;
    norm[1] = vr[1] / val;
    norm[2] = vr[2] / val;


    return norm;
}

void Model::Draw() {
    if(texture != 0){
        glBindTexture(GL_TEXTURE_2D,texture);
    }
    glEnableClientState(GL_VERTEX_ARRAY); // Enable vertex arrays
    glEnableClientState(GL_NORMAL_ARRAY); // Enable normal arrays
    glVertexPointer(3, GL_FLOAT, 0, Faces_Triangles); // Vertex Pointer to triangle array
    glNormalPointer(GL_FLOAT, 0, normals); // Normal pointer to normal array
    glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles); // Draw the triangles
    glDisableClientState(GL_VERTEX_ARRAY); // Disable vertex arrays
    glDisableClientState(GL_NORMAL_ARRAY); // Disable normal arrays
    if(texture != 0){
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Model::setTexture(unsigned int texture){
    this->texture = texture;
}

Model::~Model() {
    delete Faces_Triangles; // Stores the triangles
    delete normals; // Stores the normals
    if(texture != 0){
        glDeleteTextures(1, &texture);
    }
}