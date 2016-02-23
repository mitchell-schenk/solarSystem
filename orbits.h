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
    Body(double xPosition, double yPosition, double bodyMass, double bodyRadius, int colorRed, int colorGreen, int colorBlue);
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
    //constructor
    Planet(double xVelocity, double yVelocity, double xPosition, double yPosition, double bodyMass, double bodyRadius, int colorRed, int colorGreen, int colorBlue);
    //destructor
    ~Planet();
    
};

