#pragma once

#include "ofMain.h"
#include "ofApp.h"

//declerations only


//Parent Class
class Body{
public:
    double xPos;
    double yPos;
    double mass;
    double radius;
    int colorR;
    int colorG;
    int colorB;
    Body(double xPosition, double yPosition, double bodyMass, double bodyRadius, int colorRed, int colorGreen, int colorBlue); //Probably don't need the colors once we get textures
};


//child of Body
class Sun: public Body{
public:
    //constructor
    Sun(double xPosition, double yPosition, double bodyMass, double bodyRadius, int colorRed, int colorGreen, int colorBlue);
    //destructor
    ~Sun();
};
    
//child of Body
class Planet: public Body{
public:
    //special pieces not in body
    double xVel;
    double yVel;
    double xAcc;
    double yAcc;
    void move();
    void acc(vector<Planet>, vector<Sun>, int);
    bool winCheck(ofRectangle);
    vector<int> collisionCheck(vector<Planet> planets, vector<Sun> suns, int index);
    //constructor
    Planet(double xVelocity, double yVelocity, double xPosition, double yPosition, double bodyMass, double bodyRadius, int colorRed, int colorGreen, int colorBlue);
    //destructor
    ~Planet();
    
};

