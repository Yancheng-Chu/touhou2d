#pragma once
#pragma once

#include "Sprite.h"
//Yanchegn Chu 012485200 part 2 of project 1. 03.21.2021. Need addon ofxGui

//Basic boss Emitter
//
class bEmitter : public BaseObject {
public:
	bEmitter(SpriteSystem *);
	void draw();
	void start();
	void stop();
	void setLifespan(float);
	void setVelocity(ofVec3f);
	void setChildImage(ofImage);
	void setImage(ofImage);
	void setRate(float);
	void update();
	SpriteSystem *sys;
	float rate;
	ofVec3f velocity;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	bool startEmitter;
	float width, height;
	ofSoundPlayer shoot;
	float childWidth, childHeight;
	void setChildSize(float w, float h) { childWidth = w; childHeight = h; }
};