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

class Loader {
public:
    Loader();
    Loader(const Loader& orig);

    std::vector<Model*> parseXML();

    virtual ~Loader();
private:

    std::string location;


    Model* parseXMLModel(QDomElement model);

    void parsePosition(QDomElement position, int& xpos, int& ypos, int& zpos);
    void parseSize(QDomElement position, int& xpos, int& ypos, int& zpos);
    void parseModelLoc(QDomElement modelLoc, QString& type, QString& pad);
    QDomElement getFirstByTag(QDomElement element, QString tag);
    QString getFirstByTagS(QDomElement element, QString tag);

};

#endif	/* LOADER_H */

