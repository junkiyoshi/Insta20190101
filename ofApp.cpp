#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(0);
	ofEnableDepthTest();

	this->shader.load("shader/shader.vert", "shader/shader.frag");
	this->font.loadFont("fonts/Kazesawa-bold.ttf", 150, true, true, true);
	
	this->tex1.allocate(ofGetWidth(), ofGetHeight());
	this->tex2.allocate(ofGetWidth(), ofGetHeight());

	this->tex1.begin();
	ofClear(0);

	string word = "2019";
	this->font.drawString(word, ofGetWidth() * 0.5 - this->font.stringWidth(word) * 0.5, ofGetHeight() -  this->font.stringHeight(word) * 0.5);

	ofBeginShape();
	for (int deg = 0; deg < 360; deg += 5) {

		ofVertex(200 * cos(deg * DEG_TO_RAD) + ofGetWidth() * 0.5, 200 * sin(deg * DEG_TO_RAD) + ofGetHeight() * 0.35);
	}
	ofEndShape();

	this->tex1.end();

}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->tex2.begin();
	ofClear(0);

	for (int i = 0; i < 8; i++) {

		vector<glm::vec2> vertices;
		float noise_seed = ofRandom(1000);
		float noise_step = ofRandom(0.001, 0.0005);
		for (int x = 0; x <= ofGetWidth(); x += 10) {

			vertices.push_back(glm::vec2(x, ofNoise(noise_seed, x * noise_step, ofGetFrameNum() * 0.001) * ofGetHeight()));
		}
	
		int count = vertices.size();
		for (int vertices_index = count - 1; vertices_index > -1; vertices_index--) {

			vertices.push_back(vertices[vertices_index] - glm::vec2(0, -5));
		}		

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();
	}

	this->tex2.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofFill();
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex1", this->tex1.getTexture(), 1);
	this->shader.setUniformTexture("tex2", this->tex2.getTexture(), 2);

	ofDrawRectangle(glm::vec2(0, 0), ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}