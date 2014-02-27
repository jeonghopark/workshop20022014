#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(30);
    ofSetDepthTest(true);
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    radius = 200;
    numHeight = 30;

    circleResolution = 60;
    heightResolution = 20;
    
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
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    for (int j=0; j<numHeight; j++) {
        
        for (int i=0; i<circleResolution; i++) {

            int _index = i + j * circleResolution;


            xyMoving = sin( ofDegToRad( ofGetFrameNum() ) + j/6 );
            
//            xyMoving = ofMap( j, 0, numHeight, 0, 1 );

//            float _zFactor = ofMap( j, 0, numHeight-1, 0, PI );
//            xyMoving = sin( _zFactor );

//            float _zFactor = ofMap( j, 0, numHeight-1, 0, PI/2 );
//            xyMoving = tan( _zFactor );

//            float _zFactor = ofMap( j, 0, numHeight-1, 0, PI );
//            xyMoving = cos( _zFactor );

            
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