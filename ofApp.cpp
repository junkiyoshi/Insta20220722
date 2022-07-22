#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetColor(0);
	ofSetCircleResolution(60);

	this->shader.load("shader/shader.vert", "shader/shader.frag");
	this->fbo1.allocate(ofGetWidth(), ofGetHeight());
	this->fbo2.allocate(ofGetWidth(), ofGetHeight());
	this->fbo3.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	vector<glm::vec2> location_list;
	vector<glm::vec2> next_list;

	this->fbo1.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	for (int k = 0; k < 12; k++) {

		ofMesh mesh;
		vector<glm::vec3> right, left, frame;

		glm::vec3 last_location;
		float last_theta;

		for (int i = 0; i < 28; i++) {

			auto radius = ofMap(ofNoise((ofGetFrameNum() + i + k * 30) * 0.02), 0, 1, 150, 380);
			auto next_radius = ofMap(ofNoise((ofGetFrameNum() + i + 1 + k * 30) * 0.02), 0, 1, 150, 380);

			auto location = glm::vec3(radius * cos((ofGetFrameNum() + i + k * 30) * -DEG_TO_RAD), radius * sin((ofGetFrameNum() + i + k * 30) * -DEG_TO_RAD), 0);
			auto next = glm::vec3(next_radius * cos((ofGetFrameNum() + i + 1 + k * 30) * -DEG_TO_RAD), next_radius * sin((ofGetFrameNum() + i + 1 + k * 30) * -DEG_TO_RAD), 0);

			auto direction = next - location;
			auto theta = atan2(direction.y, direction.x);

			right.push_back(location + glm::vec3(ofMap(i, 0, 25, 0, 8) * cos(theta + PI * 0.5), ofMap(i, 0, 25, 0, 8) * sin(theta + PI * 0.5), 0));
			left.push_back(location + glm::vec3(ofMap(i, 0, 25, 0, 8) * cos(theta - PI * 0.5), ofMap(i, 0, 25, 0, 8) * sin(theta - PI * 0.5), 0));

			last_location = location;
			last_theta = theta;
		}

		for (int i = 0; i < right.size(); i++) {

			mesh.addVertex(left[i]);
			mesh.addVertex(right[i]);
		}


		for (int i = 0; i < mesh.getNumVertices() - 2; i += 2) {

			mesh.addIndex(i + 0); mesh.addIndex(i + 1); mesh.addIndex(i + 3);
			mesh.addIndex(i + 0); mesh.addIndex(i + 2); mesh.addIndex(i + 3);
		}

		mesh.addVertex(last_location);
		int index = mesh.getNumVertices();
		for (auto theta = last_theta - PI * 0.5; theta <= last_theta + PI * 0.5; theta += PI / 20) {

			mesh.addVertex(last_location + glm::vec3(8 * cos(theta), 8 * sin(theta), 0));
			frame.push_back(last_location + glm::vec3(8 * cos(theta), 8 * sin(theta), 0));
		}

		for (int i = index; i < mesh.getNumVertices() - 1; i++) {

			mesh.addIndex(index); mesh.addIndex(i + 0); mesh.addIndex(i + 1);
		}

		mesh.draw();
	}

	this->fbo1.end();

	this->fbo2.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	
	//noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	for (int k = 0; k < 12; k++) {

		ofMesh mesh;
		vector<glm::vec3> right, left, frame;

		glm::vec3 last_location;
		float last_theta;

		for (int i = 0; i < 28; i++) {

			auto radius = ofMap(ofNoise((ofGetFrameNum() + i + k * 30) * 0.02), 0, 1, 150, 380);
			auto next_radius = ofMap(ofNoise((ofGetFrameNum() + i + 1 + k * 30) * 0.02), 0, 1, 150, 380);

			auto location = glm::vec3(radius * cos((ofGetFrameNum() + i + k * 30) * DEG_TO_RAD), radius * sin((ofGetFrameNum() + i + k * 30) * DEG_TO_RAD), 0);
			auto next = glm::vec3(next_radius * cos((ofGetFrameNum() + i + 1 + k * 30) * DEG_TO_RAD), next_radius * sin((ofGetFrameNum() + i + 1 + k * 30) * DEG_TO_RAD), 0);

			auto direction = next - location;
			auto theta = atan2(direction.y, direction.x);

			right.push_back(location + glm::vec3(ofMap(i, 0, 25, 0, 8) * cos(theta + PI * 0.5), ofMap(i, 0, 25, 0, 8) * sin(theta + PI * 0.5), 0));
			left.push_back(location + glm::vec3(ofMap(i, 0, 25, 0, 8) * cos(theta - PI * 0.5), ofMap(i, 0, 25, 0, 8) * sin(theta - PI * 0.5), 0));

			last_location = location;
			last_theta = theta;
		}

		for (int i = 0; i < right.size(); i++) {

			mesh.addVertex(left[i]);
			mesh.addVertex(right[i]);
		}


		for (int i = 0; i < mesh.getNumVertices() - 2; i += 2) {

			mesh.addIndex(i + 0); mesh.addIndex(i + 1); mesh.addIndex(i + 3);
			mesh.addIndex(i + 0); mesh.addIndex(i + 2); mesh.addIndex(i + 3);
		}

		mesh.addVertex(last_location);
		int index = mesh.getNumVertices();
		for (auto theta = last_theta - PI * 0.5; theta <= last_theta + PI * 0.5; theta += PI / 20) {

			mesh.addVertex(last_location + glm::vec3(8 * cos(theta), 8 * sin(theta), 0));
			frame.push_back(last_location + glm::vec3(8 * cos(theta), 8 * sin(theta), 0));
		}

		for (int i = index; i < mesh.getNumVertices() - 1; i++) {

			mesh.addIndex(index); mesh.addIndex(i + 0); mesh.addIndex(i + 1);
		}

		mesh.draw();
	}

	this->fbo2.end();

	this->fbo3.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	int out = 600;
	int in = 500;

	ofBeginShape();
	ofVertex(out * -0.5, out * -0.5);
	ofVertex(out *  0.5, out * -0.5);
	ofVertex(out *  0.5, out *  0.5);
	ofVertex(out * -0.5, out *  0.5);
	ofNextContour(true);
	ofVertex(in * -0.5, in * -0.5);
	ofVertex(in *  0.5, in * -0.5);
	ofVertex(in *  0.5, in *  0.5);
	ofVertex(in * -0.5, in *  0.5);
	ofEndShape();

	out = 300;
	in = 400;

	ofBeginShape();
	ofVertex(out * -0.5, out * -0.5);
	ofVertex(out *  0.5, out * -0.5);
	ofVertex(out *  0.5, out *  0.5);
	ofVertex(out * -0.5, out *  0.5);
	ofNextContour(true);
	ofVertex(in * -0.5, in * -0.5);
	ofVertex(in *  0.5, in * -0.5);
	ofVertex(in *  0.5, in *  0.5);
	ofVertex(in * -0.5, in *  0.5);
	ofEndShape();

	this->fbo3.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofFill();
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex1", this->fbo1.getTexture(), 1);
	this->shader.setUniformTexture("tex2", this->fbo2.getTexture(), 2);
	this->shader.setUniformTexture("tex3", this->fbo3.getTexture(), 3);

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