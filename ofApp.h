#pragma once

#include "ofMain.h"
#include "ofxGui.h"


//#include <math.h>


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        //functions for ui elements that fire when listeners are triggered
        void planetMassChanged(int & massInput);
        void buttonPressed();
		void scaleButtonPressed();
   
		//Clicking generation
        string label;
        int startX,startY,otherX,otherY;
        int maxDrag;
        float tempX, tempY, ratio; //for planet generation velocity
        int currentMass, frameCount;
        bool mouseDown, maxLength;
    
		int i = 0;
    
        //UI elements
        ofxPanel planetGeneration;
        //ofxFloatField massInput;
        ofxButton button;
        ofxButton scaleButton;
    
        ofRectangle startBox;
        ofRectangle target;

		//Level loading things
		double scale;
		int timeScale;
		bool passed;
		void loadNextLevel();
		int tempA[4] = { 0,0,0,0 };
		string line;
		string sunFlag = "*";
		int lineCount;
		std::string token;
		vector<long long>objectDump;
        int levelCount;
		bool sunTrigger = false;//bool trigger, use the same thing for other types
};


