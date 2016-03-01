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
    
    //set background to black
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    timeScale = 1;
    
    //setup UI
    planetGeneration.setup();
    planetGeneration.add(massInput.setup("Planet Mass", 2000));
    
    currentMass = massInput;
    maxLength = false;
    
    
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

void ofApp::planetMassChanged(int &massInput){
     currentMass = (massInput);
}

//--------------------------------------------------------------
void ofApp::update(){
    currentMass = massInput;
    //accelerate and move planets
    for(int i = 0; i < timeScale; i++){
        for(int i = 0; i < planets.size(); i++){
        
            planets[i].acc(planets, suns,i);//accelerate the planets on themselves and the suns
            planets[i].move();//move planets
            indexes = planets[i].collisionCheck(planets, suns, i);//maybe add to orbits.cpp as part of Planet or Sun
            if(indexes.size() != 0){
                for(int z = 0; z < indexes.size(); z++){
                    planets.erase(planets.begin()+(indexes[z]));//delete planet or planets that collided from vector
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw framerate
    ofDrawBitmapString(ofGetFrameRate(),730,15);
    //ofDrawBitmapString(currentMass,50,30);
    
    //draw UI elements
    planetGeneration.draw();
    massInput.draw();
    
    //draw planets
    for(int i = 0; i < planets.size(); i++)
    {
        ofSetColor(planets[i].colorR,planets[i].colorG,planets[i].colorB);
        ofDrawCircle(planets[i].xPos, planets[i].yPos, planets[i].radius);
    }
    
    //draw Suns
    for(int i = 0; i < suns.size(); i++)
    {
        ofSetColor(suns[i].colorR,suns[i].colorG,suns[i].colorB);
        ofDrawCircle(suns[i].xPos, suns[i].yPos, suns[i].radius);
        
    }
    if(mouseDown){
        if(maxLength){
            ofSetColor(255,0,0);
        }
        else{
        ofSetColor(0,0,255);
        }
    
        ofDrawLine(startX,startY,otherX,otherY);
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
    /*
    lineX = startX - otherX;
    lineY = startX - otherY;
     */
    
    
     if (sqrt(((startX-otherX)*(startX-otherX))+((startY-otherY)*(startY-otherY))) > 300){
         //mouseDown = false;
         maxLength = true;
         //ratio = 300/sqrt(((startX-otherX)*(startX-otherX))+((startY-otherY)*(startY-otherY)));
         //lineX = (startX - otherX) *  ratio;
        // lineY = (startY - otherY) *  ratio;
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
    //need to set velocity as function of a drag or something currently fixed
    

    if (sqrt(((startX-otherX)*(startX-otherX))+((startY-otherY)*(startY-otherY))) > 300){
        mouseDown = false;
        ratio = 300/sqrt(((startX-otherX)*(startX-otherX))+((startY-otherY)*(startY-otherY)));
        tempX = (startX - otherX) * .05 * ratio;
        tempY = (startY - otherY) * .05 * ratio;
    }
    else{
        tempX = (startX - otherX) * .05;
        tempY = (startY - otherY) * .05;
    }
    
	srand(time(NULL));
	int red, green, blue;
	red = rand() % 255 + 1;
	green = rand() % 255 + 1;
	blue = rand() % 255 + 1;
    Planet mars3( tempX, tempY, startX, startY, currentMass, 5, red, green, blue);
    planets.push_back(mars3);
    mars3.~Planet();
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