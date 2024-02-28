#include "ofMain.h"
#include "bEmitter.h"
//Yanchegn Chu 012485200 part 2 of project 1. 03.21.2021. Need addon ofxGui

//Basic boss Emitter variable
//
bEmitter::bEmitter(SpriteSystem *spriteSys) {
	sys = spriteSys;

	lifespan = 3000;    // milliseconds
	started = false;

	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = false;
	velocity = ofVec3f(100, 100, 0);
	//	drawable = true;
	width = 64;
	height = 64;
	childWidth = 16;
	childHeight = 16;
	//	bSelected = false;
}


//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void bEmitter::draw() {
	image.draw(-image.getWidth() / 2.0 + pos.x, -image.getHeight() / 2.0 + pos.y);
	// draw sprite system
	// got vector error
	sys->draw();
}
//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void bEmitter::update() {
	if (!started) return;

	float time = ofGetElapsedTimeMillis();
	if ((time - lastSpawned) > (1000.0 / rate)) {
		// spawn a new sprite
		Sprite sprite;
		if (haveChildImage) sprite.setImage(childImage);
		sprite.velocity = velocity;
		sprite.lifespan = lifespan;
		sprite.rotation = rotation;
		sprite.pos = pos;
		sprite.birthtime = time;
		lastSpawned = time;
		if (startEmitter) {
			sys->add(sprite);
		}
	}
	sys->update();
}

// Start/Stop the emitter.
//
void bEmitter::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void bEmitter::stop() {
	started = false;
}

//set boss life
//
void bEmitter::setLifespan(float life) {
	lifespan = life;
}
//set boss velocity
//
void bEmitter::setVelocity(ofVec3f v) {
	velocity = v;
}
//set boss sprite image
//
void bEmitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
}
//set boss image
//
void bEmitter::setImage(ofImage img) {
	image = img;
	haveImage = true;
}
//set boss sprite rate
//
void bEmitter::setRate(float r) {
	rate = r;
}