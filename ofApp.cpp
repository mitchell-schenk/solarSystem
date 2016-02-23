#include "ofApp.h"
#include "orbits.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

//initialize vector
std::vector<Planet> planets;
std::vector<Sun> suns;
std::vector<int> indexes;


int startX;
int startY;


//--------------------------------------------------------------
void ofApp::setup(){
     //set background to black
     ofBackground(0,0,0);
    
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
void ofApp::update(){
 
    //accelerate and move planets
    for(int i = 0; i < planets.size(); i++){
        indexes = planets[i].collisionCheck(planets, suns, i);//maybe add to orbits.cpp as part of Planet or Sun
        if(indexes.size() != 0){
            for(int z = 0; z < indexes.size(); z++){
                planets.erase(planets.begin()+(indexes[z]));//delete planet or planets that collided from vector
            }
        }
        planets[i].acc(planets, suns,i);//accelerate the planets on themselves and the suns
        planets[i].move();//move planets
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw framerate
    ofDrawBitmapString(ofGetFrameRate(),50,10);
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //start of drag for creating a plannet
    startX = x;
    startY = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    //create plannet on mouse release
    //need to set velocity as function of a drag or something currently fixed
    Planet mars3( 2, 0, x, y, 2000, 5, 0, 255, 0);
    planets.push_back(mars3);
    mars3.~Planet();
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
//add to Planet or Sun???
/*
vector<int> collisionCheck(vector<Planet> planets, vector<Sun> suns, int index){
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
*/