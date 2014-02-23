#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(30);
    
    ofSetDepthTest(true);
    
    texture.loadImage("texture.jpg");
    mesh.enableTextures();

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    numWidth = 200;
    numHeight = 200;
    vertexSpacing = 10;
    
    plateWidth = (numWidth-1) * vertexSpacing;
    plateHeight = (numHeight-1) * vertexSpacing;
    
    zSize = 60;
    
    float _texWidhtRatio = texture.getWidth() / plateWidth;
    float _texHeightRatio = texture.getHeight() / plateHeight;
    
    float _xRandom = ofRandom(24,48);
    float _yRandom = ofRandom(24,48);

    for (int j=0; j<numHeight; j++) {
        for (int i=0; i<numWidth; i++) {
            ofVec3f _a = ofVec3f( i * vertexSpacing - plateWidth/2, j * vertexSpacing - plateHeight/2, 0 );
            mesh.addVertex(_a);
            ofColor _c = ofColor::fromHsb(0, 120, 255, 255);
            mesh.addColor( _c );
            
            
            ofVec2f _t = ofVec2f( i * vertexSpacing * _texWidhtRatio, j * vertexSpacing * _texHeightRatio );
            mesh.addTexCoord( _t );
            
            float _movingSpeed = 0.5;
            
            // _noise wird als zPosition Ÿbersetzt. (0-1)
            float _noise = ofNoise( i/_xRandom, j/_yRandom ) * zSize;
            
            if (_noise>zSize/2) {
                zPos.push_back( zSize-_noise );
                zDirection.push_back( -_movingSpeed );
            } else {
                zPos.push_back( _noise );
                zDirection.push_back( _movingSpeed );
            }
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
    lighting.setPosition(0, -200, 1000);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int j=0; j<numHeight; j++) {
        for (int i=0; i<numWidth; i++) {
            int _index = i + j * numWidth;
            
            zPos[_index] = zPos[_index] + zDirection[_index];
            if (zPos[_index]>zSize/2) zDirection[_index] = -zDirection[_index];
            if (zPos[_index]<0) zDirection[_index] = -zDirection[_index];
            
        }
    }
    
    for (int j=0; j<numHeight; j++) {
        for (int i=0; i<numWidth; i++) {
            int _index = i + j * numWidth;
            
            ofVec3f _vec = mesh.getVertex(_index);
            mesh.setVertex( _index, ofVec3f( _vec.x, _vec.y, zPos[_index]));
            
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    
//    lighting.enable();
    cam.begin();
    ofRotateX(82);
    
    for (int j=0; j<numHeight; j++) {
        for (int i=0; i<numWidth; i++) {
            int _index = i + j * numWidth;
            mesh.setColor( _index, ofColor::fromHsb(0,0,255,255) );
        }
    }

    mesh.draw();

    texture.bind();

    
    for (int j=0; j<numHeight; j++) {
        for (int i=0; i<numWidth; i++) {
            int _index = i + j * numWidth;
            mesh.setColor( _index, ofColor::fromHsb(0,0,255,255) );
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