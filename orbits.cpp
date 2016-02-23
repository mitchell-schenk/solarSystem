//
//  orbits.cpp
//  mySketch
//
//  Created by Mitchell on 2/5/16.
//
//

#include "orbits.h"
#include "ofMain.h"
#include "ofApp.h"

//Body constructor
Body::Body(double xPosition, double yPosition, double bodyMass, double bodyRadius, int colorRed, int colorGreen, int colorBlue){
    xPos = xPosition;
    yPos = yPosition;
    mass = bodyMass;
    radius = bodyRadius;
    colorR = colorRed;
    colorG = colorGreen;
    colorB = colorBlue;
}


//Sun constructor
Sun::Sun(double xPosition, double yPosition, double bodyMass, double bodyRadius, int colorRed, int colorGreen, int colorBlue) : Body( xPosition,  yPosition, bodyMass, bodyRadius, colorRed, colorGreen, colorBlue){
  
}

//Sun destructor
Sun::~Sun(){
    
}

//Planet constructor
Planet::Planet(double xVelocity, double yVelocity, double xPosition, double yPosition, double bodyMass, double bodyRadius, int colorRed, int colorGreen, int colorBlue) : Body( xPosition,  yPosition,  bodyMass, bodyRadius,  colorRed, colorGreen,  colorBlue){
    
    
    xVel = xVelocity;
    yVel = yVelocity;

    
}

//Planet destructor
Planet::~Planet(){
    
}

//Accelerate planets
void Planet::acc(vector<Planet> planets, vector<Sun> suns, int num){
    //accelerate planet on other planets
    for(int i = 0; i < planets.size(); i++ ){
        //dont accelerate it on itself
        if(i != num){
            xAcc = sin(atan2((planets[i].xPos-xPos),(planets[i].yPos-yPos))) * (planets[num].mass * planets[i].mass * pow(10,-10))/(pow(planets[i].xPos-xPos,2) + pow(planets[i].yPos - yPos,2));
            yAcc = cos(atan2((planets[i].xPos-xPos),(planets[i].yPos-yPos))) * (planets[num].mass * planets[i].mass * pow(10,-10))/(pow(planets[i].xPos-xPos,2) + pow(planets[i].yPos - yPos,2));
            
            xVel += xAcc;
            yVel += yAcc;
        }
        
    }
    //accelerate planets on sun(s)
    for(int i = 0; i < suns.size(); i++ ){
        
        
            xAcc = sin(atan2((suns[i].xPos-xPos),(suns[i].yPos-yPos))) * (planets[num].mass * suns[i].mass * pow(10,-10))/(pow(suns[i].xPos-xPos,2) + pow(suns[i].yPos - yPos,2));
            yAcc = cos(atan2((suns[i].xPos-xPos),(suns[i].yPos-yPos))) * (planets[num].mass * suns[i].mass * pow(10,-10))/(pow(suns[i].xPos-xPos,2) + pow(suns[i].yPos - yPos,2));
            
            xVel += xAcc;
            yVel += yAcc;
        
        
    }
}
//move the planets - Does this need to be its own function???
void Planet::move(){
    xPos += xVel;
    yPos += yVel;
}

vector<int> Planet::collisionCheck(vector<Planet> planets, vector<Sun> suns, int index){
    vector<int> spots;
    bool destroyed = false;
    
    for(int o = 0; o < planets.size(); o++){
        if(o != index){
            if(sqrt(pow(planets[index].xPos-planets[o].xPos,2) + pow(planets[index].yPos - planets[o].yPos,2)
                    ) < (planets[index].radius + planets[o].radius)){
                spots.push_back(index);
                destroyed = true;
                if(index > o){
                    spots.push_back(o);
                }
                else if(index < o){
                    spots.push_back((o-1));
                }
            }
        }
    }
    for(int o = 0; o < suns.size(); o++){
        if(sqrt(pow(planets[index].xPos-suns[o].xPos,2) + pow(planets[index].yPos - suns[o].yPos,2)) < (planets[index].radius + suns[o].radius)){
            if(destroyed== false){
                spots.push_back(index);
            }
        }
    }
    return spots;
}

