#include "ofApp.h"
#include "orbits.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//initialize vector
std::vector<Planet> planets;
std::vector<Sun> suns;
std::vector<ofRectangle> boxes;
std::vector<int> indexes;


//--------------------------------------------------------------
void ofApp::setup(){
    // Start menu
    gameState = 0;
    setupGameState0();
}
//--------------------------------------------------------------
void ofApp::setupGameState0() {
    mofoFont.loadFont("BadMofo.ttf", 50);
    mofoFontSmall.loadFont("BadMofo.ttf", 20);
}
//--------------------------------------------------------------
void ofApp::setupGameState1() {
    
    scale = 0;
    label = "Small";
    
    //set background to black
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    timeScale = 1;
    frameCount = 35;
    
    //setup UI
    planetGeneration.setup();
    
    //planetGeneration.add(massInput.setup("Planet Mass", 2000));
    planetGeneration.add(button.setup(" "));
    planetGeneration.add(scaleButton.setup(" "));
    
    //currentMass = massInput;
    maxLength = false;
    maxDrag = 200;
    
    loadNextLevel();
    
    //load images
    planetOne.load("images/PlanetSpriteSheet1.png");
    frameCounter = 0;
    UFO1.load("images/UFO1.png");
    teleporter.load("images/teleporter.png");

    
    
    
    
}
//--------------------------------------------------------------
void ofApp::update(){
    
    //accelerate and move planets
    if (gameState == 1) {
    for(int ii = 0; ii < timeScale; ii++){
        for(int oo = 0; oo < planets.size(); oo++){
            indexes = planets[oo].collisionCheck(planets, suns, boxes, oo);//maybe add to orbits.cpp as part of Planet or Sun
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
            if(planets[oo].winCheck(target)){
                loadNextLevel();
            }
        }
    }
	//for textures
	frameCounter++;
	if (frameCounter == 5) {
        
		planetXCut++;
		if (planetXCut == 127) {
			planetXCut = 0;
		}
		frameCounter = 0;

        frameCounter2++;
        if (frameCounter2 == 3) {
            UFOXCut++;
            if (UFOXCut == 5) {
                UFOXCut = 0;
            }
            frameCounter2 = 0;
        }
		
		
		teleporterXCUT++;
		if (teleporterXCUT == 23) {
			teleporterXCUT = 0;
		}
	}

    //To stop planet spam
    if (frameCount < 35){
        frameCount++;
    }
    }
    else if (gameState == 0) {
        if (updown == "down") {
            opacity -= 5;
            if (opacity <= 5) {
                updown = "up";
            }
        }
        if (updown == "up") {
            opacity += 5;
            if (opacity >= 250) {
                updown = "down";
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (gameState == 0) {
        drawGameState0();
    }
    if (gameState == 1) {
        drawGameState1();
    }
}
//--------------------------------------------------------------
void ofApp::drawGameState0() {
    ofColor color1(0, 0, 0);
    ofColor color2(44, 36, 60);
    ofBackgroundGradient(color2, color1, OF_GRADIENT_CIRCULAR);
    ofSetColor(255, 255, 255);
    
    ofRectangle stringBounds = mofoFont.getStringBoundingBox(gameTitle, 0, 0);
    mofoFont.drawString(gameTitle, ofGetWidth() / 2 - stringBounds.width / 2, ofGetHeight() / 2 - stringBounds.height / 2);
    stringBounds = mofoFontSmall.getStringBoundingBox(gameAuthors, 0, 0);
    mofoFontSmall.drawString(gameAuthors, ofGetWidth() / 2 - stringBounds.width / 2, ofGetHeight() / 2 + 10);
    
    ofSetColor(255,255,255, opacity);
    stringBounds = mofoFontSmall.getStringBoundingBox(gameStart, 0, 0);
    mofoFontSmall.drawString(gameStart, ofGetWidth() / 2 - stringBounds.width / 2, ofGetHeight() / 2 + 100);
}
//--------------------------------------------------------------
void ofApp::drawGameState1(){
    //draw framerate
    ofDrawBitmapString(ofGetFrameRate(),730,15);
    
    
    //ofSetColor(255,0,0);
    //ofDrawRectangle(target);
    
    //draw planets
    
    for (int ii = 0; ii < planets.size(); ii++)
    {
        //ofSetColor(planets[ii].colorR, planets[ii].colorG, planets[ii].colorB);
        
        ofDrawCircle(planets[ii].xPos + ((400 - planets[ii].xPos) * scale), planets[ii].yPos + ((400 - planets[ii].yPos) * scale), planets[ii].radius - (planets[ii].radius*scale));
        
        UFOCookieCutter = UFOXCut * 64;
        UFO1Radius = (planets[ii].radius - (planets[ii].radius*scale));
        UFOCrop.cropFrom(UFO1, UFOCookieCutter, 0, 64, 64);
        UFOCrop.draw(planets[ii].xPos + ((400 - planets[ii].xPos) * scale) - UFO1Radius, planets[ii].yPos + ((400 - planets[ii].yPos) * scale) - UFO1Radius, 2 * UFO1Radius, 2 * UFO1Radius);
        
        
    }
    
    //draw Suns
    for (int ii = 0; ii < suns.size(); ii++)
    {
        //ofSetColor(suns[ii].colorR, suns[ii].colorG, suns[ii].colorB);
        
        ofDrawCircle(suns[ii].xPos + ((400 - suns[ii].xPos) * scale), suns[ii].yPos + ((400 - suns[ii].yPos) * scale), suns[ii].radius - (suns[ii].radius*scale));
        
        tempCut = planetXCut * 128;
        planetOneRadius = (suns[ii].radius - (suns[ii].radius*scale));
        planetOne2.cropFrom(planetOne, tempCut, 0, 128, 128);
        planetOne2.draw(suns[ii].xPos + ((400 - suns[ii].xPos) * scale) - planetOneRadius, suns[ii].yPos + ((400 - suns[ii].yPos) * scale) - planetOneRadius, 2 * planetOneRadius, 2 * planetOneRadius);
        
        
    }
    
    //draw teleporter
    
    teleporterCookieCutter = teleporterXCUT * 128;
    teleporterCrop.cropFrom(teleporter, teleporterCookieCutter, 0, 128, 128);
    teleporterCrop.draw(target.x-32, target.y, 64, 150);
    
    ofSetColor(0, 255, 0);
    ofDrawRectangle(startBox);
    ofSetColor(0, 0, 0);
    ofDrawRectangle(startBox.x + (startBox.width / 8), startBox.y + (startBox.height / 8), 3 * startBox.width / 4, 3 * startBox.height / 4);
    
    if (mouseDown) {
        if (maxLength) {
            ofSetColor(255, 0, 0);
        }
        else {
            ofSetColor(0, 255, 0);
        }
    }
    //draw obstacles
    for(int ii = 0; ii < boxes.size(); ii++)
    {
        ofSetColor(170,170,170);
        ofDrawRectangle(boxes[ii]);
        
    }
    
    //Check if the line is inside the start box
    if(mouseDown){
        if(startX>=startBox.x && startX <= startBox.x+startBox.width && startY>= startBox.y && startY<= startBox.y+startBox.height){
            if(maxLength){
                //ofSetColor(255,0,0);
            }
            else{
                // ofSetColor(0,255,0);
            }
            ofDrawLine(startX, startY, otherX, otherY);
        }
    }
    

}
//--------------------------------------------------------------
void ofApp::loadNextLevel(){ 
    levelCount++;
    
    //Clear the previous level
    planets.clear();
    suns.clear();
    objectDump.clear();
    boxes.clear();
    
    ifstream myfile; //Open level file and check if it works
    myfile.open(ofToDataPath("level"+std::to_string(levelCount)+".txt").c_str());
    if(myfile.is_open()){
        ofLog(OF_LOG_NOTICE,"It worked");
    }
	else{
        ofLog(OF_LOG_NOTICE,"Failed");
    }

    if (myfile.is_open()) //Go line by line to parse the strings from the text file
    {
        lineCount = 0;
        while ( getline (myfile,line) )
        {
			std::istringstream ss(line);
            objectDump.clear();
            for(int j = 0; j<2; j++){
                if(line.compare(sunFlag[j]) == 0){
                    type = j;
                    ofLog(OF_LOG_NOTICE, std::to_string(type));
                }
            }
            if(lineCount == 0){        //Zoom scale
                scale = std::stod(line);
            }
            else if(lineCount == 1){   //Time Scale
                timeScale = std::stod(line);
            }
            else if(lineCount == 2){   //Get the parameters for the start box
                int ii = 0;
                while(std::getline(ss, token, ',')) {
                    tempA[ii] = std::stod(token);
                    ii++;
                }
                startBox.x = tempA[0];
                startBox.y = tempA[1];
                startBox.width = tempA[2];
                startBox.height = tempA[3];
            }
            else if(lineCount == 3){  //Get the parameters for the target
                int ii = 0;
                while(std::getline(ss, token, ',')) {
                    tempA[ii] = std::stod(token);
                    ii++;
                }
                target.x = tempA[0];
                target.y = tempA[1];
                target.width = tempA[2];
                target.height = tempA[3];
            }
            else if (type == 0 && line.compare(sunFlag[type]) != 0) { //Get the parameters for the suns, this goes until sunTrigger is false (i.e. it hits another *)
                int ii = 0;
                while (std::getline(ss, token, ',')) {
                    if(ii == 2){
                        objectDump.push_back(std::stoll(token));
                    }
                    else{
                        objectDump.push_back(std::stod(token));
                    }
                    ii++;
                }
                Sun nextSun(objectDump[0], objectDump[1], objectDump[2], objectDump[3], objectDump[4], objectDump[5], objectDump[6]); //For reference when making objects in the text file, the order is xPos, yPos, mass, radius, then colors which me can remove later
                //Sun nextSun(400, 400, 10000000000, 20, 255, 255, 0);
                suns.push_back(nextSun);
                nextSun.~Sun();
            }
            else if(type == 1 && line.compare(sunFlag[type]) != 0){
                //obstacles
                int ii = 0;
                while (std::getline(ss, token, ',')) {
                    if(ii == 2){
                        objectDump.push_back(std::stoll(token));
                    }
                    else{
                        objectDump.push_back(std::stod(token));
                    }
                    ii++;
                    
                }

                ofRectangle rect(objectDump[0],objectDump[1],objectDump[2],objectDump[3]);
                boxes.push_back(rect);
                rect.~ofRectangle();

            }
            lineCount++;
        }
        myfile.close();
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
    if (gameState == 1) {
        startX = x;
        startY = y;
        otherX = x;
        otherY = y;
        mouseDown = true;
    }
    if (gameState == 0) {
        if (x >= 0 && x <= 800) {
            if (y >= 0 && y <= 800) {
                gameState = 1;
                setupGameState1();
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
//create plannet on mouse release
if(startX>=startBox.x && startX <= startBox.x+startBox.width && startY>= startBox.y && startY<= startBox.y+startBox.height){
    if (frameCount >= 35)
        {
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
    
  
            if (scale != 0){
                Planet newPlanet( tempX , tempY , startX - (((400 - startX) * (1/(1-scale)))-(400-startX)), startY - (((400 - startY) * (1/(1-scale)))-(400-startY)), 2000, 5, 255, 0, 0);
                planets.push_back(newPlanet);
                newPlanet.~Planet();
            }
            else{
                Planet newPlanet( tempX, tempY, startX, startY, 2000, 7, 0, 0, 255);
                planets.push_back(newPlanet);
                newPlanet.~Planet();
            }
            mouseDown = false;
        }
    }
    frameCount = 0;
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