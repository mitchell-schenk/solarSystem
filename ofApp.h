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
   
		//Clicking generation
        string label;
        int startX,startY,otherX,otherY;
        int maxDrag;
        float tempX, tempY, ratio; //for planet generation velocity
        int frameCount;
        bool mouseDown, maxLength;
    
        int gameState;
        //GameState 0
        void setupGameState0();
        void drawGameState0();
        int opacity = 150;
        string updown = "up";
        ofTrueTypeFont mofoFont, mofoFontSmall;
        string gameTitle = "Solar System Game";
        string gameAuthors = "By MitDanCal";
        string gameStart = "Click Anywhere to Start";
    
    
        //GameState 1
        void setupGameState1();
        void drawGameState1();

    
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
		int tempA[4] = {0,0,0,0};
		string line;
        string sunFlag[2] = {"*","!"};
		int lineCount;
		std::string token;
		vector<long long>objectDump;
        int levelCount;
		bool sunTrigger = false;//bool trigger, use the same thing for other types
        int type;
    
    
		//textures
		ofImage planetOne;
		ofImage planetOne2;
		ofImage UFO1;
		ofImage UFOCrop;
		ofImage teleporter;
		ofImage teleporterCrop;
		ofImage motherShipSheet;
		ofImage motherShipSHeetCrop;
		ofImage stars;
		int UFOCookieCutter;
		int UFOXCut;
		int UFO1Radius;
		int frameCounter = 0;
		int frameCounter2 = 0;
		int planetXCut;
		int tempCut;
		int planetOneRadius;
		int teleporterCookieCutter;
		int teleporterXCUT;
		int teleporterRadius;
		int motherShipCookieCutter;
		int motherShipXCut;
		int starCookieCutter;
		int starXCut;
    
        //Dynamic camera
        int cameraX = -400, cameraY = 400;
};


