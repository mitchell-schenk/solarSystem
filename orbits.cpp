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
//-----------------------------------------------------------------
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
//-----------------------------------------------------------------
Sun::Sun(double xPosition, double yPosition, double bodyMass, double bodyRadius, int colorRed, int colorGreen, int colorBlue) : Body( xPosition,  yPosition, bodyMass, bodyRadius, colorRed, colorGreen, colorBlue){
  
}

//Sun destructor
//-----------------------------------------------------------------
Sun::~Sun(){
    
}

//Planet constructor
//-----------------------------------------------------------------
Planet::Planet(double xVelocity, double yVelocity, double xPosition, double yPosition, double bodyMass, double bodyRadius, int colorRed, int colorGreen, int colorBlue) : Body( xPosition,  yPosition,  bodyMass, bodyRadius,  colorRed, colorGreen,  colorBlue){
    
    xVel = xVelocity;
    yVel = yVelocity;
}

//Planet destructor
//-----------------------------------------------------------------
Planet::~Planet(){
    
}

//Accelerate planets
//-----------------------------------------------------------------
void Planet::acc(vector<Planet> planets, vector<Sun> suns, int num){
    //accelerate planet on other planets
    for(int ii = 0; ii < planets.size(); ii++ ){
        //dont accelerate it on itself
        if(ii != num){
            xAcc = sin(atan2((planets[ii].xPos - xPos), (planets[ii].yPos - yPos))) * (planets[num].mass * planets[ii].mass * pow(10, -8)) / (pow(planets[ii].xPos - xPos,2) + pow(planets[ii].yPos - yPos,2));
            yAcc = cos(atan2((planets[ii].xPos - xPos), (planets[ii].yPos - yPos))) * (planets[num].mass * planets[ii].mass * pow(10, -8))/(pow(planets[ii].xPos - xPos,2) + pow(planets[ii].yPos - yPos,2));
            
            xVel += xAcc;
            yVel += yAcc;
        }
        
    }
    //accelerate planets on sun(s)
    for(int ii = 0; ii < suns.size(); ii++ ){
            xAcc = sin(atan2((suns[ii].xPos - xPos),(suns[ii].yPos - yPos))) * (planets[num].mass * suns[ii].mass * pow(10, -10))/(pow(suns[ii].xPos - xPos, 2) + pow(suns[ii].yPos - yPos,2));
            yAcc = cos(atan2((suns[ii].xPos - xPos),(suns[ii].yPos - yPos))) * (planets[num].mass * suns[ii].mass * pow(10, -10))/(pow(suns[ii].xPos-xPos,2) + pow(suns[ii].yPos - yPos, 2));
            xVel += xAcc;
            yVel += yAcc;
    }
}
//move the planets - Does this need to be its own function???
//-----------------------------------------------------------------
void Planet::move(){
    xPos += xVel;
    yPos += yVel;
}

//-----------------------------------------------------------------
vector<int> Planet::collisionCheck(vector<Planet> planets, vector<Sun> suns, int index){
    //index is telling which planet in the vector we are checking everything else against
    vector<int> spots;
    bool destroyed = false;
    
    //check against all planets except self
    for(int oo = 0; oo < planets.size(); oo++){
        if(oo != index){
            if(sqrt(pow(planets[index].xPos - planets[oo].xPos,2) + pow(planets[index].yPos - planets[oo].yPos,2)
                    ) < (planets[index].radius + planets[oo].radius)){
                spots.push_back(index);
                destroyed = true;
                if(index > oo){
                    spots.push_back(oo);
                }
                else if(index < oo){
                    spots.push_back((oo - 1));
                }
            }
        }
    }
    //check planet agains sun(s)
    for(int oo = 0; oo < suns.size(); oo++){
        if(sqrt(pow(planets[index].xPos - suns[oo].xPos, 2) + pow(planets[index].yPos - suns[oo].yPos, 2)) < (planets[index].radius + suns[oo].radius)){
            if(destroyed == false){
                spots.push_back(index);
            }
        }
    }
    
    //if planet is collided we reference which one it is by the spot in the vector and send it back to be destroyed
    return spots;
}

