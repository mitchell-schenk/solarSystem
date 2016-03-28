#include "ofApp.h"
#include "orbits.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <math.h>
#include <iostream>
#include <vector>

//initialize vector
std::vector<Planet> planets;
std::vector<Sun> suns;
std::vector<int> indexes;





//--------------------------------------------------------------
void ofApp::setup(){
    
    
    //massInput.addListener(this, &ofApp::planetMassChanged);
    button.addListener(this, &ofApp::buttonPressed);//button listener
    
    //set background to black
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    timeScale = 1;
    
    //setup UI
    planetGeneration.setup();
    planetGeneration.add(massInput.setup("Planet Mass", 2000));
    planetGeneration.add(button.setup("Speed: "+std::to_string(timeScale)));
    
    
    currentMass = massInput;
    maxLength = false;
    maxDrag = 200;
    
    
    //makes planet ( xVel, yVel, xPos, yPos,mass, radius, red, green, blue)
    Planet earth(0, 1.5, 700,400,2000, 5, 255, 0, 0);
    planets.push_back(earth);
    earth.~Planet();
    
    Planet mars( 2, 0, 500, 200, 2000, 5, 0, 255, 0);
    planets.push_back(mars);
    mars.~Planet();
    
    Planet mars2( 2, 0, 400, 100, 2000, 5, 0, 0, 255);
    planets.push_back(mars2);
    mars2.~Planet();
    
    //make sun (x, y, mass, radius, R, G, B)
    Sun sunOne(400, 400, 10000000000, 20, 255, 255, 0);
    suns.push_back(sunOne);
    sunOne.~Sun();

}
//--------------------------------------------------------------
void ofApp::planetMassChanged(int &massInput){
     currentMass = (massInput);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    currentMass = massInput;//not in use for the text field in the future
    
    //accelerate and move planets
    for(int ii = 0; ii < timeScale; ii++){
        for(int oo = 0; oo < planets.size(); oo++){
            indexes = planets[oo].collisionCheck(planets, suns, oo);//maybe add to orbits.cpp as part of Planet or Sun
            if(indexes.size() != 0){
                for(int zz = 0; zz < indexes.size(); zz++){
                    planets.erase(planets.begin()+(indexes[zz]));//delete planet or planets that collided from vector
                }
            }
            if(oo >= planets.size()){
                break;
            }
            planets[oo].acc(planets, suns,oo);//accelerate the planets on themselves and the suns
            planets[oo].move();//move planets
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw framerate
    ofDrawBitmapString(ofGetFrameRate(),730,15);
    
    //draw UI elements
    planetGeneration.draw();

    
    //draw planets
    for(int ii = 0; ii < planets.size(); ii++)
    {
        ofSetColor(planets[ii].colorR, planets[ii].colorG, planets[ii].colorB);
        ofDrawCircle(planets[ii].xPos, planets[ii].yPos, planets[ii].radius);
    }
    
    //draw Suns
    for(int ii = 0; ii < suns.size(); ii++)
    {
        ofSetColor(suns[ii].colorR, suns[ii].colorG, suns[ii].colorB);
        ofDrawCircle(suns[ii].xPos, suns[ii].yPos, suns[ii].radius);
        
    }
    if(mouseDown){
        if(maxLength){
            ofSetColor(0,255,0);
        }
        else{
            ofSetColor(0,0,255);
        }
    
        ofDrawLine(startX, startY, otherX, otherY);
    }
    
}
//--------------------------------------------------------------
void ofApp::buttonPressed(){
    
    if(timeScale < 3){
        timeScale++;
    }
    else{
        timeScale = 1;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(mouseDown){
        otherX = x;
        otherY = y;
    }
    
    //used for line drag
     if (sqrt(((startX-otherX)*(startX-otherX))+((startY-otherY)*(startY-otherY))) > maxDrag){
         maxLength = true;
     }
     else{
         maxLength = false;
     }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //start of drag for creating a plannet
    startX = x;
    startY = y;
    otherX = x;
    otherY = y;
    mouseDown = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
//create plannet on mouse release
    
    //scale speed so it isnt too big
    if (sqrt(((startX-otherX)*(startX-otherX))+((startY-otherY)*(startY-otherY))) > maxDrag){
        mouseDown = false;
        ratio = maxDrag/sqrt(((startX-otherX)*(startX-otherX))+((startY-otherY)*(startY-otherY)));
        tempX = (startX - otherX) * .03 * ratio;
        tempY = (startY - otherY) * .03 * ratio;
    }
    else{
        tempX = (startX - otherX) * .03;
        tempY = (startY - otherY) * .03;
    }
    
  

    Planet newPlanet( tempX, tempY, startX, startY, currentMass, 5, 255, 0, 0);
    planets.push_back(newPlanet);
    newPlanet.~Planet();
    mouseDown = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}