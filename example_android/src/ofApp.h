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

struct DataMark
{
    std::vector<ofRectangle> rt;
    std::vector<std::vector<glm::vec2>> pt;
};

class dlib_detect : public ofThread
{
public:
    shape_predictor sp;
    std::vector<std::vector<glm::vec2>> shapes;
    std::vector<dlib::rectangle> dets;
    dlib::frontal_face_detector detector;
    matrix<rgb_pixel>im;
    std::vector<ofRectangle> rt;

    void setup(string _p)
    {
        detector = dlib::get_frontal_face_detector();
        deserialize(ofToDataPath(_p,true)) >> sp;
        startThread(true);
    }

    void set(ofPixels _pix)
    {
        im = mat(_pix);
    }

    DataMark get()
    {
        DataMark m;
        m.rt = rt;
        m.pt = shapes;
        return m;
    }

    void threadedFunction()
    {
        while(isThreadRunning())
        {
            dets = detector(im);
            shapes.clear();
            rt.clear();
            for (unsigned long j = 0; j < dets.size(); j++)
            {
                full_object_detection shape = sp(im, dets[j]);
                std::vector<glm::vec2> sh;
                for(unsigned int i = 0; i < shape.num_parts(); i++) {
                    glm::vec2 v = ofxDlib::toOf(shape.part(i));
                    sh.push_back(v);
                }
                shapes.push_back(sh);
                rt.push_back(ofRectangle(ofxDlib::toOf(dets[j])));
            }
        }
    }
};

class ofApp : public ofxAndroidApp
{	
	public:
        dlib_detect dl;
        ofVideoGrabber cam;
        ofImage image,imgdr;
        int w,h,w2,h2;
        int rsw, rsh;
        int reduc;

        void exit();
        void setup();
	    void update();
	    void draw();
        void touchDown(int x, int y, int id);
        void deviceOrientationChanged(ofOrientation newOrientation);
        bool backPressed();
};
