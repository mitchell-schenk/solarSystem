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
    
    levelCount = 0;
    startBox.x = 600;
    startBox.y = 600;
    startBox.width = 50;
    startBox.height = 50;
    
    target.x = 650;
    target.y = 100;
    target.height = 150;
    target.width = 7;
    
    passed = false;
    
    scale = 0;
    
    //massInput.addListener(this, &ofApp::planetMassChanged);
    button.addListener(this, &ofApp::buttonPressed);//button listener
    scaleButton.addListener(this, &ofApp::scaleButtonPressed);
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
    
    
    //makes planet ( xVel, yVel, xPos, yPos,mass, radius, red, green, blue)
   
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
    
    //currentMass = massInput;//not in use for the text field in the future
    
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
            if(planets[oo].winCheck(target)){
                loadNextLevel();
            }
        }
    }
    //To stop planet spam
    if (frameCount < 35){
        frameCount++;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw framerate
    ofDrawBitmapString(ofGetFrameRate(),730,15);
    
    //draw UI elements
    /*
    planetGeneration.draw();
    ofSetColor(255,255,255);
    ofDrawBitmapString("Speed: "+std::to_string(timeScale),32,43);
    ofDrawBitmapString("Scale: "+label,32,63);
     */
    
    ofSetColor(0,255,0);
    ofDrawRectangle(startBox);
    ofSetColor(0,0,0);
    ofDrawRectangle(startBox.x+(startBox.width/8),startBox.y+(startBox.height/8),3*startBox.width/4,3*startBox.height/4);
    ofSetColor(255,0,0);
    ofDrawRectangle(target);
    
    //draw planets
    for(int ii = 0; ii < planets.size(); ii++)
    {
        ofSetColor(planets[ii].colorR, planets[ii].colorG, planets[ii].colorB);
        ofDrawCircle(planets[ii].xPos + ((400 - planets[ii].xPos) * scale), planets[ii].yPos + ((400 - planets[ii].yPos) * scale), planets[ii].radius - (planets[ii].radius*scale));
    }
   
    
    //draw Suns
    for(int ii = 0; ii < suns.size(); ii++)
    {
        ofSetColor(suns[ii].colorR, suns[ii].colorG, suns[ii].colorB);
        ofDrawCircle(suns[ii].xPos + ((400 - suns[ii].xPos) * scale), suns[ii].yPos + ((400 - suns[ii].yPos) * scale), suns[ii].radius - (suns[ii].radius*scale));
        
    }
    for(int ii = 0; ii < boxes.size(); ii++)
    {
        ofSetColor(170,170,170);
        ofDrawRectangle(boxes[ii]);
        
    }
    

	//Check if the line is inside the start box
    if(mouseDown){
        if(startX>=startBox.x && startX <= startBox.x+startBox.width && startY>= startBox.y && startY<= startBox.y+startBox.height){
            if(maxLength){
                ofSetColor(255,0,0);
            }
            else{
                ofSetColor(0,255,0);
            }
            ofDrawLine(startX, startY, otherX, otherY);
        }
    }
    if(passed == true){
        ofDrawRectangle(100, 100, 50, 50);
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
void ofApp::scaleButtonPressed(){
    if (scale == 0){
       scale = .5;
        label = "Medium";
    }
    else if(scale == .5){
        scale = 0;
        label = "Small";
    }
    
}
//--------------------------------------------------------------
void ofApp::loadNextLevel(){ 
    levelCount++;
    planets.clear(); //Clear the previous level
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
                for(int oo =0; oo < objectDump.size(); oo++)
                {
                    ofLog(OF_LOG_NOTICE,std::to_string(objectDump[oo]));
                }
                
                ofRectangle rect(objectDump[0],objectDump[1],objectDump[2],objectDump[3]);
                boxes.push_back(rect);
                rect.~ofRectangle();

            }

            /*
			else if(line.compare(sunFlag) == 0){ //flag for suns
				ofLog(OF_LOG_NOTICE, "sun flag");
				sunTrigger = !sunTrigger;
			}
             
			else if (sunTrigger == true) { //Get the parameters for the suns, this goes until sunTrigger is false (i.e. it hits another *)
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
             */
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
    startX = x;
    startY = y;
    otherX = x;
    otherY = y;
    mouseDown = true;
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
                Planet newPlanet( tempX, tempY, startX, startY, 2000, 5, 0, 0, 255);
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