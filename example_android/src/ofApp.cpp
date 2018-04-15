/*
        Copyright (c) 2018 Dario Longobardi
        License: MIT
*/
#include "ofApp.h" 

void ofApp::setup()
{
    ofLogNotice("ofxDlib") << "START";

    w      = ofGetWidth();
    h      = ofGetHeight();
    cam.setup( h,w );
    ofxAndroidVideoGrabber* androidGrabber = (ofxAndroidVideoGrabber*)cam.getGrabber().get();
    androidGrabber->setDeviceID(androidGrabber->getFrontCamera());
    dl.setup("shape_predictor_68_face_landmarks.dat");

    reduc  = 12;
    w2     = w/2;
    h2     = h/2;
    rsw    = cam.getWidth()/reduc;
    rsh    = cam.getHeight()/reduc;

    ofLogNotice("ofxDlib") << "dlib-frame: " << rsw << "x" << rsh;
}

void ofApp::update()
{
    cam.update();
    if(cam.isFrameNew())
    {
        /* render */
        imgdr.setFromPixels(cam.getPixels());
        imgdr.rotate90(-45);

        /* dlib frame detector */
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
    //
    ofSetColor(255);
    imgdr.draw(0, 0);

    DataMark d = dl.get();
    for(int i = 0; i < d.rt.size(); i++)
    {
        ofPushStyle();
        ofNoFill();
        ofSetColor(ofColor::yellow);
        ofRectangle r = d.rt[i];
        ofSetLineWidth(15);
        ofDrawRectangle(r.x*reduc,r.y*reduc,r.width*reduc,r.height*reduc);
        ofPopStyle();
        for(int j = 0; j < d.pt[i].size(); j++)
        {
            ofPushStyle();
            ofSetColor(ofColor::red);
            glm::vec2 p = d.pt[i][j];
            ofDrawEllipse(p.x*reduc,p.y*reduc,20,20);
            ofPopStyle();
        }
    }

    //
    ofPopMatrix();
}

void ofApp::exit()
{
    dl.stopThread();
}

void ofApp::touchDown(int x, int y, int id){ }
void ofApp::deviceOrientationChanged(ofOrientation newOrientation){}
bool ofApp::backPressed() { return false; }
