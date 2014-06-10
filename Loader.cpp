/* 
 * File:   Loader.cpp
 * Author: Ralph Bisschops <ralph.bisschops@student.uhasselt.be>
 * 
 * Created on June 8, 2014, 5:59 PM
 */

#include "Loader.h"

Loader::Loader() {
    location = ":/loadfile.xml";
}

Loader::Loader(const Loader& orig) {
    location = orig.location;
}

Loader::~Loader() {
}

std::vector<Model*> Loader::parseXML() {
    std::vector<Model*> loadedmodels;
    
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
    QDomNodeList models = mDocumentElement.childNodes();
    for (int i = 0; i < models.count(); i++) {
        loadedmodels.push_back(parseXMLModel(models.at(i).toElement()));
    }
    

    return loadedmodels;
}

Model* Loader::parseXMLModel(QDomElement model) {
    //std::cout << model.attribute("name").toStdString(); print object name
    
    QDomNodeList modelparts = model.childNodes();
    
    int xpos = 0, ypos = 0, zpos = 0;
    int xsize = 1;
    int ysize = 1;
    int zsize = 1;
    QString modeltype = "";
    QString modelpad = "";
    
    parsePosition(getFirstByTag(model,"position"), xpos, ypos, zpos);
    parseSize(getFirstByTag(model,"size"), xpos, ypos, zpos);
    parseModelLoc(getFirstByTag(model,"modelLoc"), modeltype, modelpad);
    
    
    Model* newModel = new Model(xpos, ypos, zpos, xsize, ysize, zsize, modeltype, modelpad);
    newModel->loadModel();
    return newModel;
}

void Loader::parsePosition(QDomElement position, int& xpos, int& ypos, int& zpos){
    xpos = getFirstByTagS(position, "x").toInt();
    ypos = getFirstByTagS(position, "y").toInt();
    zpos = getFirstByTagS(position, "z").toInt();
}

void Loader::parseSize(QDomElement size, int& xpos, int& ypos, int& zpos){
    xpos = getFirstByTagS(size, "x").toInt();
    ypos = getFirstByTagS(size, "y").toInt();
    zpos = getFirstByTagS(size, "z").toInt();
}

void Loader::parseModelLoc(QDomElement modelLoc, QString& type, QString& pad){
    type = modelLoc.attribute("type");
    pad = modelLoc.text();
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

