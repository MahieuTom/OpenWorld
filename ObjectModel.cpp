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
}


ObjectModel::ObjectModel(int xpos, int ypos, int zpos, double xsize, double ysize, double zsize, Model* model){
    pos = new Coordinate(xpos, ypos, zpos);
    this->xsize = xsize;
    this->ysize = ysize;
    this->zsize = zsize;
    this->model = model;
    
}

ObjectModel::ObjectModel(const ObjectModel& orig) {
    pos = orig.pos;
    xsize = orig.xsize;
    ysize = orig.ysize;
    zsize = orig.zsize;
    model = orig.model;
}


void ObjectModel::Draw(){
    glTranslatef(pos->x, pos->y, pos->z);
    model->Draw();
    glTranslatef(-pos->x, -pos->y, -pos->z);
}


ObjectModel::~ObjectModel() {
}

