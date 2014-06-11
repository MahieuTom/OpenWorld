/* 
 * File:   ObjectModel.cpp
 * Author: Ralph Bisschops <ralph.bisschops@student.uhasselt.be>
 * 
 * Created on June 10, 2014, 8:00 PM
 */

#include "ObjectModel.h"

ObjectModel::ObjectModel() {
    pos = new Coordinate(0, 0, 0);
    xsize = 1;
    ysize = 1;
    zsize = 1;
    model = NULL;
    modelOwner = false;
}


ObjectModel::ObjectModel(int xpos, int ypos, int zpos, double xsize, double ysize, double zsize, Model* model, bool modelOwner){
    pos = new Coordinate(xpos, ypos, zpos);
    this->xsize = xsize;
    this->ysize = ysize;
    this->zsize = zsize;
    this->model = model;
    modelOwner = modelOwner;
}

ObjectModel::ObjectModel(const ObjectModel& orig) {
    pos = orig.pos;
    xsize = orig.xsize;
    ysize = orig.ysize;
    zsize = orig.zsize;
    model = orig.model;
    modelOwner = false;
}


void ObjectModel::Draw(){
    glTranslatef(pos->x, pos->y, pos->z);
    model->Draw();
    glTranslatef(-pos->x, -pos->y, -pos->z);
}


ObjectModel::~ObjectModel() {
    if(modelOwner){
        delete model;
    }
}

