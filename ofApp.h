#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxInputField.h"


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
    
        int timeScale;
        int startX,startY,otherX,otherY;
        int maxDrag;
        float tempX, tempY, ratio; //for planet generation velocity
        float lineX,lineY;
        int currentMass;
        bool mouseDown, maxLength;
    
        //UI elements
        ofxPanel planetGeneration;
        ofxFloatField massInput;
        ofxButton button;
    
};


