/* 
 * File:   ObjectModel.h
 * Author: Ralph Bisschops <ralph.bisschops@student.uhasselt.be>
 *
 * Created on June 10, 2014, 8:00 PM
 */

#ifndef OBJECTMODEL_H
#define	OBJECTMODEL_H

#include "Model.h"

class ObjectModel {
public:
    ObjectModel();
    ObjectModel(int xpos, int ypos, int zpos, double xsize, double ysize, double zsize, Model* model, bool modelOwner = false);
    ObjectModel(const ObjectModel& orig);
    
    void Draw();
    
    virtual ~ObjectModel();
private:
    Coordinate* pos;
    double xsize;
    double ysize;
    double zsize;
    Model* model;
    bool modelOwner;
};

#endif	/* OBJECTMODEL_H */

