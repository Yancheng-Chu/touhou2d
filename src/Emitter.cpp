#include "ofMain.h"
#include "Emitter.h"

//Yanchegn Chu 012485200 part 2 of project 1. 03.21.2021. Need addon ofxGui
//Basic Emitter variable
//
Emitter::Emitter(SpriteSystem *spriteSys) {
	sys = spriteSys;

	lifespan = 3000;    // milliseconds
	started = false;

	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = false;
	velocity = ofVec3f(100, 100, 0);
	//	drawable = true;
	width = 32;
	height = 32;
	childWidth = 22;
	childHeight = 64;

	//	bSelected = false;
}

//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void Emitter::draw() {
	image.draw(-image.getWidth() / 2.0 + pos.x, -image.getHeight() / 2.0 + pos.y);
	// draw sprite system
	// got vector error
	sys->draw();
}
//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void Emitter::update() {
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

		sprite.width = childWidth;
		sprite.height = childHeight;

		sprite.birthtime = time;
		lastSpawned = time;
		if (shooting) {
			sys->add(sprite);
			shoot.load("bgm/se_damage.ogg");
			shoot.setSpeed(rate);
			shoot.play();
		}
		else {
			shoot.stop();
		}
	}
	sys->update();
}

// Start/Stop the emitter.
//
void Emitter::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void Emitter::stop() {
	started = false;
}

//set player life
//
void Emitter::setLifespan(float life) {
	lifespan = life;
}
//set player velocity
//
void Emitter::setVelocity(ofVec3f v) {
	velocity = v;
}
//set player sprite image
//
void Emitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
	childWidth = img.getWidth();
	childHeight = img.getHeight();
}
//set player image
//
void Emitter::setImage(ofImage img) {
	image = img;
	haveImage = true;
}
//set player sprite rate
//
void Emitter::setRate(float r) {
	rate = r;
}