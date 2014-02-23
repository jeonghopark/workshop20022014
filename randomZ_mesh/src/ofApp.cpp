#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(30);
    
    ofSetDepthTest(true);
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    numWidth = 200;
    numHeight = 200;
    vertexSpacing = 10;
    
    plateWidth = (numWidth-1) * vertexSpacing;
    plateHeight = (numHeight-1) * vertexSpacing;
    
    zSize = 60;
    
    for (int j=0; j<numHeight; j++) {
        for (int i=0; i<numWidth; i++) {
            ofVec3f _a = ofVec3f( i * vertexSpacing - plateWidth/2, j * vertexSpacing - plateHeight/2, ofRandom(zSize) );
            mesh.addVertex(_a);
            ofColor _c = ofColor::fromHsb(0, 120, 255, 255);
            mesh.addColor( _c );
        }
    }
    
    for (int j=0; j<numHeight-1; j++) {
        for (int i=0; i<numWidth-1; i++) {
            
            int _index = i + j * numWidth;
            
            mesh.addIndex(_index);
            mesh.addIndex(_index+numWidth);
            mesh.addIndex(_index+1);
            
            mesh.addIndex(_index+1);
            mesh.addIndex(_index+numWidth);
            mesh.addIndex(_index+numWidth+1);
            
        }
    }
    
    cam.setupPerspective();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();
    
    ofRotateX(82);
    
    for (int j=0; j<numHeight; j++) {
        for (int i=0; i<numWidth; i++) {
            int _index = i + j * numWidth;
            mesh.setColor( _index, ofColor::fromHsb(0,0,255,255) );
        }
    }

    mesh.draw();

    for (int j=0; j<numHeight; j++) {
        for (int i=0; i<numWidth; i++) {
            int _index = i + j * numWidth;
            mesh.setColor( _index, ofColor::fromHsb(0,0,0,255) );
        }
    }
    
    mesh.drawWireframe();
    
    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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