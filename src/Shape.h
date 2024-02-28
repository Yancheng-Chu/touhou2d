#pragma once
#include "ofMain.h"
#include "Sprite.h"
//Yanchegn Chu 012485200 part 2 of project 1. 03.21.2021. Need addon ofxGui

//Basic Shape
//
class Shape {
public:
	Shape() {}
	virtual void draw() {}
	virtual bool inside() { return false; }

	glm::vec3 pos;
	float rotation = 0.0;
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);

	glm::mat4 getMatrix() {
		glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
		glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), this->scale);

		return (trans * rot * scale);
	}

	vector<glm::vec3> verts;
	bool bSelected = false;
};
//Basic TriangleShape to modify the area of emitter
//
class TriangleShape : public Shape {
public:
	TriangleShape(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
		verts.push_back(p1);
		verts.push_back(p2);
		verts.push_back(p3);
	}
	void draw();

	void integrate();
	ofVec3f velocity;
	ofVec3f acceleration;
	ofVec3f force;
	float w;
	int mass = 1;
	float damping = 0.99;
};

//Basic ImageShape to show emitter image
//
class ImageShape : public Shape {
public:
	ImageShape(ofImage image) {
		this->image = image;
	}
	ImageShape() {}

	void draw();

	bool inside(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

	ofImage image;

	void integrate();
	ofVec3f velocity;
	ofVec3f acceleration;
	ofVec3f force;
	float w;
	int mass = 1;
	float damping = 0.99;
};