/* 
 * File:   Loader.cpp
 * Author: Ralph Bisschops <ralph.bisschops@student.uhasselt.be>
 * 
 * Created on June 8, 2014, 5:59 PM
 */

#include "Loader.h"
#include "camera.h"

Loader::Loader() {
    location = ":/loadfile.xml";
    cam = NULL;
    modelId = 0;
}

Loader::Loader(const Loader& orig) {
    location = orig.location;
}

Loader::~Loader() {
}

std::vector<ObjectModel*> Loader::parseXML() {
    std::vector<ObjectModel*> loadedmodels;
    
    QFile* file = new QFile( QString(location.c_str()) );
    QDomDocument mDocument;
    
    int errorLine, errorColumn;
    QString errorMsg;
    
    QDomElement mDocumentElement;
    if(!file->open(QIODevice::ReadOnly)){
        std::cout << "error: can not open file" << std::endl;
        return loadedmodels;
    }
    //QTextStream in(file);
    
    //std::cout << "input is: " << in.readAll().toStdString();
    
    if (!mDocument.setContent(file, &errorMsg, &errorLine, &errorColumn)) {
        file->close();
        std::cout << "error: " << errorMsg.toStdString() << " " << errorLine << " " << errorColumn << std::endl;
        return loadedmodels;
    }
    file->close();

    mDocumentElement = mDocument.documentElement();
    QDomNodeList models = mDocumentElement.elementsByTagName("model");
    std::cout << "aantal models: " << models.size() << std::endl;
    for (int i = 0; i < models.count(); i++) {
        loadedmodels.push_back(parseXMLModel(models.at(i).toElement()));
    }

    return loadedmodels;
}

ObjectModel* Loader::parseXMLModel(QDomElement model) {
    //std::cout << model.attribute("name").toStdString(); //print object name
    
    
    
    double xpos = 0, ypos = 0, zpos = 0;
    double xsize = 1;
    double ysize = 1;
    double zsize = 1;
    QString modeltype = "";
    QString modelpad = "";
    QString modelTex = "";
    
    parsePosition(getFirstByTag(model,"position"), xpos, ypos, zpos);
    parseSize(getFirstByTag(model,"size"), xsize, ysize, zsize);
    parseModelLoc(getFirstByTag(model,"modelLoc"), modeltype, modelpad);
    parseModelTexture(getFirstByTag(model,"modelTexture"), modelTex);
    
    Model* newModel;
    
    bool modelfound = false;
    for (unsigned int i = 0; i < modelList.size(); i++) {
        if(modelpad.toStdString().compare(modelList.at(i).pad) == 0){
            modelfound = true;
            newModel = modelList.at(i).model;
        }
    }
    if(!modelfound){
        newModel = new Model(modeltype, modelpad);
        newModel->loadModel();
        newModel->setModelName(getFirstByTag(model,"modelLoc").attribute("id").toInt());
        ModelPadPair pair;
        pair.model = newModel;
        pair.pad = modelpad.toStdString();
        modelList.push_back(pair);
    }
    
    if(!modelTex.isEmpty()){
        unsigned int texture = 0;
        texture = LoadTexture(modelTex.toStdString().c_str());
        newModel->setTexture(texture);
    }
    
    ObjectModel* object = new ObjectModel(xpos, ypos, zpos, xsize, ysize, zsize, newModel, !modelfound);
    
    if(model.attribute("camover").toStdString().compare("true") == 0){
        cam = new Camera(object);
    }
    return object;
}

void Loader::parsePosition(QDomElement position, double& xpos, double& ypos, double& zpos){
    xpos = getFirstByTagS(position, "x").toDouble();
    ypos = getFirstByTagS(position, "y").toDouble();
    zpos = getFirstByTagS(position, "z").toDouble();
}

void Loader::parseSize(QDomElement size, double& xpos, double& ypos, double& zpos){
    xpos = getFirstByTagS(size, "x").toDouble();
    ypos = getFirstByTagS(size, "y").toDouble();
    zpos = getFirstByTagS(size, "z").toDouble();
}

void Loader::parseModelLoc(QDomElement modelLoc, QString& type, QString& pad){
    type = modelLoc.attribute("type");
    pad = modelLoc.text();
}

void Loader::parseModelTexture(QDomElement modelTex, QString& pad){
    pad = modelTex.text();
}

QString Loader::getFirstByTagS(QDomElement element, QString tag){
    if(element.elementsByTagName(tag).size() > 0){
        return element.elementsByTagName(tag).at(0).toElement().text();
    }
    return "";
}

QDomElement Loader::getFirstByTag(QDomElement element, QString tag){
    if(element.elementsByTagName(tag).size() > 0){
        return element.elementsByTagName(tag).at(0).toElement();
    }
    return QDomElement();
}

