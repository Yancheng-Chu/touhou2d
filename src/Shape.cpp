#include "Shape.h"
//Yanchegn Chu 012485200 part 2 of project 1. 03.21.2021. Need addon ofxGui

//draw Triangle
//
void TriangleShape::draw() {
	ofPushMatrix();
	ofMultMatrix(getMatrix());
	ofDrawTriangle(verts[0], verts[1], verts[2]);
	ofPopMatrix();
}
//draw Image
//
void ImageShape::draw() {
	ofPushMatrix();
	ofMultMatrix(getMatrix());
	image.draw(-image.getWidth() / 2.0, -image.getHeight() / 2.0);
	ofPopMatrix();
}
//Check whether this point inside
//
bool ImageShape::inside(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	glm::vec3 v1 = glm::normalize(p1 - p);
	glm::vec3 v2 = glm::normalize(p2 - p);
	glm::vec3 v3 = glm::normalize(p3 - p);
	float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
	float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
	float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));
	if (a1 < 0 && a2 < 0 && a3 < 0) return true;
	else return false;
}
