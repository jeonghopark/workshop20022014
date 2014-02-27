#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(30);
    ofSetDepthTest(true);
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    radius = 200;
    numHeight = 120;

    circleResolution = 60;
    heightResolution = 5;
    
    cylinderHeight = numHeight * heightResolution;
    
    for (int j=0; j<numHeight; j++) {
        for (int i=0; i<circleResolution; i++) {

            float _radiusDegree = 360*i/(float)circleResolution;
            
            float _x = cos( ofDegToRad(_radiusDegree) ) * radius;
            float _y = sin( ofDegToRad(_radiusDegree) ) * radius;
            float _z = j * heightResolution - cylinderHeight/2;

            ofVec3f _v = ofVec3f( _x, _y, _z );
            mesh.addVertex( _v );
            ofColor _c = ofColor::fromHsb(0, 0, 255, 200);
            mesh.addColor( _c );

        }
    }
    

    for (int j=0; j<numHeight-1; j++) {
        for (int i=0; i<circleResolution-1; i++) {
            
            int _index = i + j * circleResolution;
            
            mesh.addIndex(_index);
            mesh.addIndex(_index+circleResolution);
            mesh.addIndex(_index+1);

            mesh.addIndex(_index+1);
            mesh.addIndex(_index+circleResolution);
            mesh.addIndex(_index+circleResolution+1);

        }
    
        int _index = j * circleResolution;

        mesh.addIndex( circleResolution - 1 + _index);
        mesh.addIndex( circleResolution - 1 + _index + circleResolution);
        mesh.addIndex( _index);

        mesh.addIndex( _index );
        mesh.addIndex( circleResolution - 1 + _index + circleResolution);
        mesh.addIndex( _index + circleResolution );

    }

    movingMesh = mesh;
    
    cam.setupPerspective();
    
    
    
    // Audio Beispiele kommt von "audioInputExample"
    soundStream.listDevices();
	
	bufferSize = 256;
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(numHeight, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    //---------------------------------------------


}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Audio Beispiele kommt von "audioInputExample"
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 50.0, true);
    volHistory.push_back( scaledVol );
	
    if( volHistory.size() >= numHeight ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
    //---------------------------------------------

    
    for (int j=0; j<numHeight; j++) {
        
        for (int i=0; i<circleResolution; i++) {

            int _index = i + j * circleResolution;

            xyMoving = volHistory[j];
            
            float _x = mesh.getVertex(_index).x * xyMoving;
            float _y = mesh.getVertex(_index).y * xyMoving;
            float _z = mesh.getVertex(_index).z;

            ofVec3f _vec = ofVec3f( _x, _y, _z );
            
            movingMesh.setVertex( _index, _vec );
        
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();
    
    ofRotateX(82);
    
    movingMesh.drawWireframe();
    
    cam.end();
    
}


// Audio Beispiele kommt von "audioInputExample"
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	
	int numCounted = 0;
    
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	curVol /= (float)numCounted;
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}
//---------------------------------------------



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