/*
        Copyright (c) 2018 Dario Longobardi
        License: MIT
*/
#include "ofApp.h" 

void ofApp::setup()
{
    ofLogNotice("ofxDlib") << "START";
    cam.setup(1280,768);

    ofxAndroidVideoGrabber* androidGrabber = (ofxAndroidVideoGrabber*)cam.getGrabber().get();
    androidGrabber->setDeviceID(androidGrabber->getFrontCamera());
    aspect = cam.getWidth() / cam.getHeight();

    reduc = 4;
    w     = ofGetWidth();
    h     = ofGetHeight();
    w2    = w/2;
    h2    = h/2;
    rsw   = cam.getWidth()/reduc;
    rsh   = cam.getHeight()/reduc;

    dl.setup();
}

void ofApp::update()
{
    cam.update();
    if(cam.isFrameNew())
    {
        imgdr.setFromPixels(cam.getPixels());
        imgdr.rotate90(-45);
        image.setFromPixels(cam.getPixels());
        image.resize(rsw,rsh);
        image.rotate90(-45);
        dl.set(image.getPixels());
    }
}

void ofApp::draw()
{
    ofBackground(ofColor::white);

    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofTranslate(w2,h2);
    ofSetColor(255);
    imgdr.draw(0, 0);

    std::vector<ofRectangle> d = dl.get();
    for(int i = 0; i < d.size(); i++){
	    ofPushStyle();
	    ofNoFill();
	    ofSetColor(ofColor::orange);
	    ofRectangle r = d[i];
        ofSetLineWidth(10);
        ofDrawRectangle(r.x*(reduc/2),r.y*(reduc/2),r.width*reduc,r.height*reduc);
	    ofPopStyle();
    }
    ofPopMatrix();
}

void ofApp::touchDown(int x, int y, int id){ }
void ofApp::deviceOrientationChanged(ofOrientation newOrientation){}
bool ofApp::backPressed() { return false; }
