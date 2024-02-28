#include "ofApp.h"
#include "Emitter.h"
//----------------------------------------------------------------------------------
//Yanchegn Chu 012485200 part 2 of project 1. 03.21.2021. Need addon ofxGui

//Setup boss and player HP, tri as a check area, bgm,image, add gui
void ofApp::setup() {
	font1.load("fonts/font.ttf", 20);
	HP = 10;
	HP1 = 3;
	HP2 = 3;
	Life = 30;
	ofSetVerticalSync(true);

	tri.pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 1);
	tri.rotation = 180.0;
	tri.scale = glm::vec3(3.0, 3.0, 3.0);

	btri.pos = glm::vec3(ofGetWindowWidth() / 2.0, 60, 1);
	btri.rotation = 180.0;
	btri.scale = glm::vec3(3.0, 3.0, 3.0);

	b1tri.pos = glm::vec3(ofGetWindowWidth() / 6.0, 90, 1);
	b1tri.rotation =180.0;
	b1tri.scale = glm::vec3(3.0, 3.0, 3.0);

	b2tri.pos = glm::vec3(5*ofGetWindowWidth() / 6.0, 90, 1);
	b2tri.rotation = 180.0;
	b2tri.scale = glm::vec3(3.0, 3.0, 3.0);

	bbtri.pos = glm::vec3(ofGetWindowWidth() / 2.0, 60, 1);
	bbtri.rotation = 180.0;
	bbtri.scale = glm::vec3(3.0, 3.0, 3.0);

	if (spriteImage.load("images/spells1.png")) {
		imageLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/spells1.png");
		ofExit();
	}

	if (bspriteImage.load("images/bullet.png")) {
		imageLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/bullet.png");
		ofExit();
	}

	string imageFile = "images/player0.png";
	if (!im.image.load(imageFile)) {
		cout << "FATAL ERROR: can't load image file" << imageFile << endl;
		ofExit();
	}
	//im.pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 1);
	im.pos= tri.pos;

	string bimageFile = "images/boss.png";
	if (!bim.image.load(bimageFile)) {
		cout << "FATAL ERROR: can't load image file" << bimageFile << endl;
		ofExit();
	}
	bim.pos = glm::vec3(ofGetWindowWidth() / 2.0, -15, 1);

	if (!bbim.image.load(bimageFile)) {
		cout << "FATAL ERROR: can't load image file" << bimageFile << endl;
		ofExit();
	}
	bbim.pos = glm::vec3(ofGetWindowWidth() / 6.0, -15, 1);

	if (!bbbim.image.load(bimageFile)) {
		cout << "FATAL ERROR: can't load image file" << bimageFile << endl;
		ofExit();
	}
	bbbim.pos = glm::vec3(5*ofGetWindowWidth() / 6.0, -15, 1);

	string boomFile = "images/boom.png";
	if (!boom.image.load(boomFile)) {
		cout << "FATAL ERROR: can't load image file" << boomFile << endl;
		ofExit();
	}
	boom.pos = bim.pos;

	string backFile = "bg/bk.png";
	if (!bg.load(backFile)) {
		cout << "FATAL ERROR: can't load image file" << backFile << endl;
		ofExit();
	}
	
	string end = "bg/f.png";
	if (!fs.load(end)) {
		cout << "FATAL ERROR: can't load image file" << end << endl;
		ofExit();
	}

	string over = "bg/end.png";
	if (!lose.load(over)) {
		cout << "FATAL ERROR: can't load image file" << over << endl;
		ofExit();
	}

	string start = "bg/menu1.png";
	if (!menu.load(start)) {
		cout << "FATAL ERROR: can't load image file" << start << endl;
		ofExit();
	}
	
//  
	turret = new Emitter(new SpriteSystem());
//	turret->pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 1);
	turret->pos = im.pos;

	turret->setChildSize(spriteImage.getWidth(), spriteImage.getHeight());

	turret->shooting = false;
	turret->setChildImage(spriteImage);
	turret->setImage(im.image);
	turret->start();

	radio.load("bgm/stage01.ogg");
	radio.play();
	radio.setLoop(true);

	gui.setup();
	gui.add(rate.setup("rate", 5, 1, 10));
	gui.add(life.setup("life", 5, .1, 10));
	gui.add(velocity.setup("velocity", ofVec3f(0, -200, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));

	gui.add(bRate.setup("boss rate", 3, 1, 10));
	gui.add(bLife.setup("boss life", 5, .1, 10));
	gui.add(bVelocity.setup("boss velocity", ofVec3f(0, -200, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));

	bHide = true;

	boss = new bEmitter(new SpriteSystem());
	boss->startEmitter = false;
	boss->pos = bim.pos;
	boss->setChildImage(bspriteImage);
	boss->setImage(bim.image);
	boss->setChildSize(bspriteImage.getWidth(), bspriteImage.getHeight());

	boss->start();
	
		numEmitters = 5;
		float margin = 50;
		float emitterWidth = 50;
		ofPoint winsize = ofGetWindowSize();
		float spacing = (winsize.x - emitterWidth - margin * 2) / (numEmitters - 1);
		float x = emitterWidth / 2 + margin;
		for (int i = 0; i < numEmitters; i++) {
			bEmitter *emit = new bEmitter(new SpriteSystem());
			emit->pos = ofVec3f(x, 0, 0);
			//		emit->drawable = false;                // make emitter itself invisible
			emit->setChildImage(bspriteImage);
			emit->setVelocity(ofVec3f(0, 200, 0));
			emit->setRate(2);
			x += spacing;
			invader.push_back(emit);
			emit->start();
		}

		boss1 = new bEmitter(new SpriteSystem());
		boss1->pos = bbim.pos;
		boss1->setChildImage(bspriteImage);
		boss1->setImage(bbim.image);
		boss1->setRate(2);
		boss1->setVelocity(ofVec3f(0, 200, 0));
		boss1->start();

		boss2 = new bEmitter(new SpriteSystem());
		boss2->pos = bbbim.pos;
		boss2->setChildImage(bspriteImage);
		boss2->setRate(2);
		boss2->setVelocity(ofVec3f(0, 200, 0));
		boss2->setImage(bbbim.image);
		boss2->start();

		particle.setOneShot(true);
		particle.setEmitterType(RadialEmitter);
		particle.setGroupSize(20);
		particle.setParticleRadius(2);
		particle.setLifespan(3);
		particle.setVelocity(ofVec3f(50, 0, 0));

		particle2.setOneShot(true);
		particle2.setEmitterType(RadialEmitter);
		particle2.setGroupSize(20);
		particle2.setParticleRadius(2);
		particle2.setLifespan(3);
		particle2.setVelocity(ofVec3f(50, 0, 0));
//			particle.start();
//			particle2.start();
}

//to check player sprite hit the invader and reduce the hp
//--------------------------------------------------------------
void ofApp::checkHit() {
	Sprite s;
	for (int i = 0; i < turret->sys->sprites.size(); i++) {
		s.pos = ofVec3f(turret->sys->sprites[i].pos.x, turret->sys->sprites[i].pos.y - turret->childHeight / 2, 1);
		if (HP > 0) {
			if (bim.inside(glm::inverse(btri.getMatrix()) * glm::vec4(s.pos, 1), btri.verts[0], btri.verts[1], btri.verts[2])) {
				hit.load("bgm/se_kill.ogg");
				hit.setLoop(false);
				hit.play();
				turret->sys->remove(i);
				if(beat1 && beat2)
					HP -= 1;
			}
			else if (bbim.inside(glm::inverse(b1tri.getMatrix()) * glm::vec4(s.pos, 1), btri.verts[0], btri.verts[1], btri.verts[2])) {
				hit.load("bgm/se_kill.ogg");
				hit.setLoop(false);
				hit.play();
				turret->sys->remove(i);
				HP1 -= 1;
			}
			else if (bbbim.inside(glm::inverse(b2tri.getMatrix()) * glm::vec4(s.pos, 1), btri.verts[0], btri.verts[1], btri.verts[2])) {
				hit.load("bgm/se_kill.ogg");
				hit.setLoop(false);
				hit.play();
				turret->sys->remove(i);
				HP2 -= 1;
			}
		}
		else
			break;
	}
}

//to check the invader sprite hit the player and reduce the life
void ofApp::checkLife() {
	Sprite s;
	Sprite sp;
	Sprite s1;
	Sprite s2;
	for (int i = 0; i < boss->sys->sprites.size(); i++) {
		if (Life > 0) {
			s.pos = ofVec3f(boss->sys->sprites[i].pos.x, boss->sys->sprites[i].pos.y + boss->childHeight / 2, 1);
			if (im.inside(glm::inverse(tri.getMatrix()) * glm::vec4(s.pos, 1), tri.verts[0], tri.verts[1], tri.verts[2])) {
				phit.load("bgm/toggle_sound.mp3");
				phit.setLoop(false);
				phit.play();
				boss->sys->remove(i);
				Life -= 1;
			}
		}
		else
			break;
	}
	for (int i = 0; i < boss1->sys->sprites.size(); i++) {
		if (Life > 0) {
			s1.pos = ofVec3f(boss1->sys->sprites[i].pos.x, boss1->sys->sprites[i].pos.y + boss->childHeight / 2, 1);
			if (im.inside(glm::inverse(tri.getMatrix()) * glm::vec4(s1.pos, 1), tri.verts[0], tri.verts[1], tri.verts[2])) {
				phit.load("bgm/toggle_sound.mp3");
				phit.setLoop(false);
				phit.play();
				boss1->sys->remove(i);
				Life -= 1;
			}
		}
		else
			break;
	}
	for (int i = 0; i < boss2->sys->sprites.size(); i++) {
		if (Life > 0) {
			s2.pos = ofVec3f(boss2->sys->sprites[i].pos.x, boss2->sys->sprites[i].pos.y + boss->childHeight / 2, 1);
			if (im.inside(glm::inverse(tri.getMatrix()) * glm::vec4(s2.pos, 1), tri.verts[0], tri.verts[1], tri.verts[2])) {
				phit.load("bgm/toggle_sound.mp3");
				phit.setLoop(false);
				phit.play();
				boss2->sys->remove(i);
				Life -= 1;
			}
		}
		else
			break;
	}
	for (int i = 0; i < invader.size(); i++) {
		for (int j = 0; j < invader[i]->sys->sprites.size(); j++)
			if (Life > 0) {
				sp.pos = ofVec3f(invader[i]->sys->sprites[j].pos.x, invader[i]->sys->sprites[j].pos.y + boss->childHeight / 2, 1);
				if (im.inside(glm::inverse(tri.getMatrix()) * glm::vec4(sp.pos, 1), tri.verts[0], tri.verts[1], tri.verts[2])) {
					phit.load("bgm/toggle_sound.mp3");
					phit.setLoop(false);
					phit.play();
					invader[i]->sys->remove(j);
					Life -= 1;
				}
			}
			else
				break;
	}
}

void TriangleShape::integrate() {
	float framerate = ofGetFrameRate();
	float dt = 1.0 / framerate;
	pos += (velocity * dt);
	glm::vec3 accel = acceleration;
	accel += (force * 1.0 / mass);
	velocity += accel * dt;
	velocity *= damping;
}

//update specialSprite motion, two motion of invader with sin(x) and 2^x, update velocity,life,rate, track each corresponding pos
void ofApp::update() {
	if (!turret->started)  return;
	bool startUpdate = false;
	specialSprite();

	if (drawable)
		if (HP > 0) {
			if (bim.pos != btri.pos) {
				bim.pos.y += 1;
			}
			else {
				move();
				startUpdate = true;
			}
		}
	if (HP1 <= 0) {
		beat1 = true;
	}
	if (HP2 <= 0) {
		beat2 = true;
	}
	checkHit();
	checkLife();
	turret->setRate(rate);
	turret->setLifespan(life * 1000);    // convert to milliseconds 
	turret->setVelocity(ofVec3f(velocity->x, velocity->y, velocity->z));
	turret->update();

	boss->setVelocity(ofVec3f(bVelocity->x, -bVelocity->y, bVelocity->z));
	//	boss->setRate(bRate);
	boss->setLifespan(bLife * 1000);    // convert to milliseconds 
	boss->update();

	im.pos = tri.pos;
//	tri.pos = im.pos;
	turret->pos = im.pos;
	if (startUpdate) {
		bim.pos = btri.pos;
		boss->pos = bim.pos;
		boom.pos = bim.pos;
		bbtri.pos = btri.pos;
	}

	if (HP <= 3 && HP > 0) {
		boss1->setLifespan(life * 2000);
		boss1->update();
		boss2->setLifespan(life * 2000);
		boss2->update();
		for (int i = 0; i < invader.size(); i++) {
			if (i != 2) {
				bEmitter *emitter = invader[i];
				emitter->setLifespan(life * 2000);    // convert to milliseconds 
				emitter->update();
			}
		}
		if (bbim.pos != b1tri.pos) {
			bbim.pos.y += 1;
		}
		else{
			if (bbim.rotation != -20) {
				bbim.rotation -= 1;
				boss1->velocity = attheading1() * 150, 200, 1;
			}
		}
		boss1->pos = bbim.pos;
		if (bbbim.pos != b2tri.pos) {
			bbbim.pos.y += 1;
		}
		else {
			if (bbbim.rotation != 20) {
				bbbim.rotation += 1;
				boss2->velocity = attheading2() * 150, 200, 1;
			}
		}
		boss2->pos = bbbim.pos;
	}



	tri.integrate();

	if (tri.pos.x >= 0 && tri.pos.x <= ofGetWindowWidth() && tri.pos.y>=0 && tri.pos.y <= ofGetWindowHeight()) {
		range = true;
	}
	else {
		tri.velocity = ofVec3f(0, 0, 0);
		range = false;
	}
	if (tri.pos.x > ofGetWindowWidth()) {
		tri.pos.x = ofGetWindowWidth();
	}
	else if (tri.pos.x < 0) {
		tri.pos.x = 0;
	}
	else if (tri.pos.y < 0) {
		tri.pos.y = 0;
	}
	else if (tri.pos.y > ofGetWindowHeight()) {
		tri.pos.y = ofGetWindowHeight();
	}

	if (HP1 == 0) {
		particle.start();
		HP1 = -1;
	}
	particle.update();

	if (HP2 == 0) {
		particle2.start();
		HP2 = -1;
	}
	particle2.update();
}

//Specile invader motion and control moving in some area. If invader HP is higer than 5, it's sin(x) move, else will be 2^x move
void ofApp::move() {
	if (btri.pos.x == ofGetWindowWidth()) {
		c = 1;
	}
	else if (btri.pos.x == 0) {
		c = 0;
	}
	if (HP > 5 && HP < 10) {
		boss->setRate(bRate);
		if (c == 0) {
			btri.pos.y += sin(count*PI / 180);
		}
		else if (c == 1) {
			btri.pos.y += sin(count*PI / 180);
		}
		count++;
	}
	else if(HP < 5){
		boss->setRate(7);
		if (ccount>8) {
			ccount = 0;
		}
		else {
			if (cc == 0) {
				btri.pos.y += 2 ^ (ccount/10);
			}
			else {
				btri.pos.y -= 2 ^ (ccount/10);     
			}
			if (btri.pos.y > 384) {
				cc = 1;
			}
			else if (btri.pos.y < 60) {
				cc = 0;
			}
		}
		ccount++;
	}
	if (c == 1) {
		btri.pos.x -= 1;
	}
	else {
		btri.pos.x += 1;
	}
}

//Specile sprite move if invader Hp less than 3
void ofApp::specialSprite() {
	if (HP <= 3) {
		bbtri.rotation += 2;
		bVelocity = -bheading() * 150, bVelocity->y, bVelocity->z;
	}
}
//draw the menu, if space, draw the background. and show player and invader. 
//If player was desotried by the invader, GameOver. Show the invader HP in the up-right corner, and Player Life in the down-left corner.
//If player destoried the invader, release the boom effect on the invader then show Congradulation.
//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255, 255, 255, 255);
	menu.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	if (drawable) {
		bg.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		if (!finish && !gameOver) {
			float time = ofGetElapsedTimef();
//			tri.draw();
//			b1tri.draw();
//			b2tri.draw();

			string lifeTest;
			if (Life > 0) {
				lifeTest += "Your HLife: " + std::to_string(Life);
				im.draw();
				turret->sys->draw();
			}
			else {
				gameOver = true;
			}

//			bbtri.draw();
//			btri.draw();
			string hpTest;
			if (HP > 0) {
				hpTest += "BOSS HP: " + std::to_string(HP);
				bim.draw();
				boss->sys->draw();
			}
			if (HP <= 3 && HP > 0) {
				if(HP1 >0){
					bbim.draw();
					boss1->sys->draw();
					beat1 = false;
				}
				if (HP2 > 0) {
					bbbim.draw();
					boss2->sys->draw();
					beat2 = false;
				}
				for (int i = 0; i < invader.size(); i++) {
					if (i != 2) {
						invader[i]->draw();
					}
				}
			}
			if (HP == 0) {
				hpTest += "BOSS HP: " + std::to_string(HP);
				ofResetElapsedTimeCounter();
				HP = -1;
			}
			if (time < 1) {
				bim.draw();
				boom.draw();
				HP--;
			}

			if ( HP< -45) {
				finish = true;
			}

			font1.drawString(hpTest, 3 * ofGetWindowWidth() / 4, 40);
		//	ofDrawBitmapString(hpTest, ofPoint(3*ofGetWindowWidth() / 4, 20));
			font1.drawString(lifeTest, ofGetWindowWidth() / 10, ofGetWindowHeight() - 40);
		//	ofDrawBitmapString(lifeTest, ofPoint( ofGetWindowWidth() / 6, ofGetWindowHeight()-20));

			if (!bHide) {
				gui.draw();
			}

			ofTranslate(bbim.pos.x, bbim.pos.y);
			particle.draw();
			ofTranslate(-bbim.pos.x, -bbim.pos.y);
			ofTranslate(b2tri.pos.x, b2tri.pos.y);
			particle2.draw();
		}
		else if(finish)  {
			fs.draw(ofGetWindowWidth() / 32, ofGetWindowHeight() / 8, ofGetWindowWidth(), ofGetWindowHeight());
		}
		else if (gameOver) {
			lose.draw(ofGetWindowWidth() / 6, ofGetWindowHeight() / 4, ofGetWindowWidth() , ofGetWindowHeight() / 2);
		}
	}
	else{
		ofDrawBitmapString("Press Space To Start", 3* ofGetWindowWidth() / 4.0, 3* ofGetWindowHeight() / 4.0);
	}
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//	cout << "mouse( " << x << "," << y << ")" << endl;
}

//check the distance when mouse dragged inside the image. Set the max value as pos for each side to become smoothly if mouse is out of the window
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	glm::vec3 mouse = glm::vec3(x, y, 1);
	glm::vec3 delta = mouse - mouseLast;
	if (!im.bSelected) return;

	if (x < ofGetWindowWidth() && x>0 && y < ofGetWindowHeight() && y>0) {
//		im.pos += delta;
//		turret->pos += delta;
		tri.pos += delta;
	}
	if (x > ofGetWindowWidth()) {
		if (y > ofGetWindowHeight()) {
//			turret->pos = ofVec3f(ofGetWindowWidth(), ofGetWindowHeight(), 1);
//			im.pos = glm::vec3(ofGetWindowWidth(), ofGetWindowHeight(), 1);
			tri.pos = glm::vec3(ofGetWindowWidth(), ofGetWindowHeight(), 1);
		}
		else if (y < 0) {
//			turret->pos = ofVec3f(ofGetWindowWidth(), 0, 1);
//			im.pos = glm::vec3(ofGetWindowWidth(), 0, 1);
			tri.pos = glm::vec3(ofGetWindowWidth(), 0, 1);
		}
		else {
//			turret->pos = ofVec3f(ofGetWindowWidth(), y, 1);
//			im.pos = glm::vec3(ofGetWindowWidth(), y, 1);
			tri.pos = glm::vec3(ofGetWindowWidth(), y, 1);
		}
	}
	else if (x < 0) {
		if (y > ofGetWindowHeight()) {
//			turret->pos = ofVec3f(0, ofGetWindowHeight(), 1);
//			im.pos = glm::vec3(0, ofGetWindowHeight(), 1);
			tri.pos = glm::vec3(0, ofGetWindowHeight(), 1);
		}
		else if (y < 0) {
//			turret->pos = ofVec3f(0, 0, 1);
//			im.pos = glm::vec3(0, 0, 1);
			tri.pos = glm::vec3(0, 0, 1);
		}
		else {
//			turret->pos = ofVec3f(0, y, 1);
//			im.pos = glm::vec3(0, y, 1);
			tri.pos = glm::vec3(0, y, 1);
		}
	}
	else if (y > 768) {
//		turret->pos = ofVec3f(x, ofGetWindowHeight(), 1);
//		im.pos = glm::vec3(x, ofGetWindowHeight(), 1);
		tri.pos = glm::vec3(x, ofGetWindowHeight(), 1);
	}
	else if (y < 0) {
//		turret->pos = ofVec3f(x, 0, 1);
//		im.pos = glm::vec3(x, 0, 1);
		tri.pos = glm::vec3(x, 0, 1);
	}

	mouseLast = mouse;
//	cout << im.pos << endl;
}

//check if mouse clicked, whether it's inside of the image and set be selected to calculate the distance
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	glm::vec3 mouse = glm::vec3(x, y, 1);
	if (im.inside(glm::inverse(tri.getMatrix()) * glm::vec4(mouse, 1), tri.verts[0], tri.verts[1], tri.verts[2])) {
		im.bSelected = true;
		mouseLast = mouse;   
	}
}

//when mouse released, cannot drag
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	im.bSelected = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//each motion by press the key
void ofApp::keyPressed(int key) {
//	keymap.insert(pair<char,bool>(' ',false));
	if (!drawable) {
		tri.rotation = 180;
		turret->rotation = 0;
		im.rotation = 0;
//		im.pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 1);
		tri.pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 1);
//		turret->pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 1);
	}
	switch (key) {
	case '1':
//		particle.sys->reset();
		particle.start();
//		bbim.force = -parelle() * 300;
		break;
	case '3':
//		bbim.force = parelle() * 300;
		break;
	case '5':
		radio.load("bgm/se_ok00.ogg");
		radio.play();
		break;
	case '7': 
		radio.load("bgm/stage01.ogg");
		radio.play();
		break;
	case 'C':
	case 'c':
		break;
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case 'H':
	case 'h':
		bHide = !bHide;
		break;
	case 'r':
		break;
	case 'u':
		break;
	case ' ':
		drawable = true;
		turret->shooting = true;
		boss->startEmitter = true;
		break;
	case 'Q':
	case'q':
		im.rotation -= 1;
		turret->rotation -= 1;
		tri.rotation -= 1;
		velocity = heading() * 150, velocity->y, velocity->z;
		break;
	case 'E':
	case'e':
		im.rotation += 1;
		turret->rotation += 1;
		tri.rotation += 1;
		velocity = heading() * 150, velocity->y, velocity->z;
		break;

	case OF_KEY_RIGHT:
//		if (tri.pos.x <1000) {
//			im.pos += parelle();
		if (range) {
			tri.force = parelle() * 300;
		}
//			tri.pos += parelle();
//			turret->pos += parelle();
//		}
		break;
	case OF_KEY_LEFT:
//		if (turret->pos.x > 0) {
//			im.pos -= parelle();
		if(range){
			tri.force = -parelle() * 300;
//			tri.pos -= parelle();
//			turret->pos -= parelle();
		}
		break;
	case OF_KEY_UP:
//		if (turret->pos.y > 0) {
//			im.pos += heading();
//			tri.pos += heading();
		if (range) {
			tri.force = heading() * 300;
//			turret->pos += heading();
		}
		break;
	case OF_KEY_DOWN:
//		if (turret->pos.y < ofGetWindowHeight()) {
//			im.pos -= heading();
//			tri.pos -= heading();
		if (range) {
			tri.force = -heading() * 300;
//			turret->pos -= heading();
		}
		break;
	case 'a':
	case 'A':
		if (boss->pos.x>0) {
			btri.pos -= parelle();
		}
		break;
	case 'd':
	case 'D':
		if (boss->pos.x < ofGetWindowWidth()) {
			btri.pos += parelle();
		}
		break;
	case 'w':
	case 'W':
		if (boss->pos.y > 0) {
			btri.pos += heading();
		}
		break;
	case 's':
	case 'S':
		if (boss->pos.y < ofGetWindowHeight()) {
			btri.pos -= heading();
		}
		break;
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	case OF_KEY_DEL:
		break;
	}
}


//each motion by release the key
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case OF_KEY_LEFT:
		tri.force = glm::vec3(0, 0, 0);
		break;
	case OF_KEY_RIGHT:
		tri.force = glm::vec3(0, 0, 0);
		break;
	case OF_KEY_UP:
		tri.force = glm::vec3(0, 0, 0);
		break;
	case OF_KEY_DOWN:
		tri.force = glm::vec3(0, 0, 0);
		break;
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	case ' ':
		turret->shooting = false;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

