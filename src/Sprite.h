#pragma once

#include "ofMain.h"
#include "ofxGui.h"
//Yanchegn Chu 012485200 part 2 of project 1. 03.21.2021. Need addon ofxGui
//Basic BaseObject
//
class BaseObject {
public:
	BaseObject();
	glm::vec3 pos, scale;
	float	rotation;
	bool	bSelected = false;
	void setPosition(ofVec3f);

	virtual void draw() {}
	virtual bool inside() { return false; }

	// get transformation matrix for object (based on it's current pos, rotation and scale channels)
	//
	glm::mat4 getMatrix() {
		glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
		glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), this->scale);

		return (trans *rot * scale);
	}
};

//Basic Sprite
//
class Sprite : public BaseObject {
public:
	Sprite();
	void draw();
	float age();
	void setImage(ofImage);
	float speed;    //   in pixels/sec
	ofVec3f velocity; // in pixels/sec
	ofImage image;
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	string name;
	bool haveImage;
	float width, height, hoff, voff;
};

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem :public BaseObject {
public:
	void add(Sprite);
	void remove(int);
	void update();
	void draw();
	vector<Sprite> sprites;

};
