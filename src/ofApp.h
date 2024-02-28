#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"
#include "Emitter.h"
#include "Shape.h"
#include "bEmitter.h"
#include "Particle.h"
#include "ParticleEmitter.h"

//Yanchegn Chu 012485200 part 2 of project 1. 03.21.2021. Need addon ofxGui
typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

//Base ofApp
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
		void checkHit();
		void checkLife();
		void move();
		void specialSprite();

		ofSoundPlayer radio;
		ofSoundPlayer hit;
		ofSoundPlayer phit;

		bool drawable = false;
//		map<char, bool> keymap;
		bool finish = false;
		bool gameOver = false;

		Emitter  *turret = NULL;
		TriangleShape tri = TriangleShape(glm::vec3(-5, -6, 0), glm::vec3(0, 8, 0), glm::vec3(5, -6, 0));

		bool imageLoaded;
		bool playerLoaded;
		bool backLoaded;
		bool bHide;

		ofxFloatSlider rate;
		ofxFloatSlider life;
		ofxVec3Slider velocity;
		ofxLabel screenSize;

		ofxFloatSlider bRate;
		ofxFloatSlider bLife;
		ofxVec3Slider bVelocity;

		ofxPanel gui;
		
		ImageShape im;	//player image
		glm::vec3 parelle() {	//move parelle
			glm::vec3 initialParelle = glm::vec3(1, 0, 0);    // heading at start
			glm::mat4 Mrot = glm::rotate(glm::mat4(1.0), glm::radians(im.rotation), glm::vec3(0, 0, 1));
			glm::vec3 h = Mrot * glm::vec4(initialParelle, 1);
			return glm::normalize(h);
		}
		glm::vec3 heading() {	//move straight of the heading vector
			glm::vec3 initialHeading = glm::vec3(0, -1, 0);    // heading at start
			glm::mat4 Mrot = glm::rotate(glm::mat4(1.0), glm::radians(im.rotation), glm::vec3(0, 0, 1));
			glm::vec3 h = Mrot * glm::vec4(initialHeading, 1);
			return glm::normalize(h);
		}

		bEmitter  *boss = NULL;
		bEmitter  *boss1 = NULL;
		bEmitter  *boss2 = NULL;
		ImageShape bim;	// invader image
		ImageShape bbim;
		ImageShape bbbim;
		ofImage bspriteImage;
		TriangleShape btri = TriangleShape(glm::vec3(-10, -10, 0), glm::vec3(0, 11, 0), glm::vec3(10, -10, 0)); //area of invader
		TriangleShape bbtri = TriangleShape(glm::vec3(-10, -10, 0), glm::vec3(0, sin(-60) * 20, 0), glm::vec3(10, -10, 0)); //control sprite motion
		TriangleShape b1tri = TriangleShape(glm::vec3(-10, -10, 0), glm::vec3(0, 11, 0), glm::vec3(10, -10, 0));
		TriangleShape b2tri = TriangleShape(glm::vec3(-10, -10, 0), glm::vec3(0, 11, 0), glm::vec3(10, -10, 0));

		glm::vec3 bheading() {	//move straight of the heading vector
			glm::vec3 initialHeading = glm::vec3(0, -1, 0);    // heading at start
			glm::mat4 Mrot = glm::rotate(glm::mat4(1.0), glm::radians(bbtri.rotation), glm::vec3(0, 0, 1));
			glm::vec3 h = Mrot * glm::vec4(initialHeading, 1);
			return glm::normalize(h);
		}

		glm::vec3 attheading1() {	//move straight of the heading vector
			glm::vec3 initialHeading = glm::vec3(0, 1, 0);    // heading at start
			glm::mat4 Mrot = glm::rotate(glm::mat4(1.0), glm::radians(bbim.rotation), glm::vec3(0, 0, 1));
			glm::vec3 h = Mrot * glm::vec4(initialHeading, 1);
			return glm::normalize(h);
		}

		glm::vec3 attheading2() {	//move straight of the heading vector
			glm::vec3 initialHeading = glm::vec3(0, 1, 0);    // heading at start
			glm::mat4 Mrot = glm::rotate(glm::mat4(1.0), glm::radians(bbbim.rotation), glm::vec3(0, 0, 1));
			glm::vec3 h = Mrot * glm::vec4(initialHeading, 1);
			return glm::normalize(h);
		}

		glm::vec3 mouseLast;
		ofImage spriteImage;	//sprite image
		ofImage bg;			//playing background
		ofImage menu;		//start menu
		ImageShape boom;	//effect of boom when invader HP is 0

		ofImage fs;		//destory the invader congradulation
		ofImage lose;	//lose image

		int HP;		//invader HP
		int Life;	//player Life
		int HP1;
		int HP2;

		int c = 0;	//check pos.x is at 0 or at the max width to lock in the window size
		int count = 0;	//as x value for sin(x)

		int cc = 0; //check pos.y's range of height to control the moving area of invader
		int ccount = 0;	//as x value for 2^x

		vector<bEmitter *> invader;
		int numEmitters;
		bool range = false;

		bool beat1 = true;
		bool beat2 = true;

		ParticleEmitter particle;
		ParticleEmitter particle2;
		ofTrueTypeFont font1;
};
