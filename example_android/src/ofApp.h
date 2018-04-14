/*
 	Copyright (c) 2018 Dario Longobardi
	License: MIT
*/

#pragma once

#include "ofMain.h"
#include "ofxAndroid.h"
#include "ofxAndroidVideoGrabber.h"
#include "ofxDlib.h"

using namespace dlib;

class dlib_detect : public ofThread
{
    public:
    //std::vector<dlib::full_object_detection> shapes;
    std::vector<dlib::rectangle> dets;
    dlib::frontal_face_detector detector;
    matrix<rgb_pixel>im;
    std::vector<ofRectangle> rt;

    void setup()
    {
        detector = dlib::get_frontal_face_detector();
        startThread(true);
    }

    void set(ofPixels _pix)
    {
        im = mat(_pix);
    }

    std::vector<ofRectangle> get()
    {
        return rt;
    }

    void threadedFunction()
    {
        while(isThreadRunning())
        {
            dets = detector(im);
            rt.clear();
            for(int i = 0; i < dets.size(); i++)
            {
                rt.push_back(ofRectangle(ofxDlib::toOf(dets[i])));
            }
        }
    }
};

class ofApp : public ofxAndroidApp
{	
	public:
        ofVideoGrabber cam;
        ofImage image,imgdr;
        int w,h,w2,h2;
        int rsw, rsh;
        float aspect;
        dlib_detect dl;
        int reduc;

        void setup();
	    void update();
	    void draw();
        void touchDown(int x, int y, int id);
        void deviceOrientationChanged(ofOrientation newOrientation);
        bool backPressed();
};
