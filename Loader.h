/* 
 * File:   Loader.h
 * Author: Ralph Bisschops <ralph.bisschops@student.uhasselt.be>
 *
 * Created on June 8, 2014, 5:59 PM
 */

#ifndef LOADER_H
#define	LOADER_H

#include <string>
#include <QtXml/QtXml> //http://stackoverflow.com/questions/11621885/how-to-add-a-library-include-path-for-netbeans-and-gcc-on-windows werkt ook voor windows maar ge moet gewoon naar locaties kijken
#include <iostream>
#include <QtCore/QFile>
#include <QtXml/QDomDocument>
#include <vector>

#include "Model.h"
#include "ObjectModel.h"
#include "texture.h"
#include "camera.h"

class Loader {
public:
    Loader();
    Loader(const Loader& orig);

    std::vector<ObjectModel*> parseXML();
    
    Camera* getCam(){return cam;};

    virtual ~Loader();
private:
    
    struct ModelPadPair{
        Model* model;
        std::string pad;
    };
    
    Camera* cam;

    std::string location;
    std::vector<ModelPadPair> modelList;


    ObjectModel* parseXMLModel(QDomElement model);

    void parsePosition(QDomElement position, double& xpos, double& ypos, double& zpos);
    void parseSize(QDomElement position, double& xpos, double& ypos, double& zpos);
    void parseModelLoc(QDomElement modelLoc, QString& type, QString& pad);
    void parseModelTexture(QDomElement modelTex, QString& pad);
    QDomElement getFirstByTag(QDomElement element, QString tag);
    QString getFirstByTagS(QDomElement element, QString tag);
    

};

#endif	/* LOADER_H */

