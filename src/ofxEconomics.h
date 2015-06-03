#pragma once

#include "ofMain.h"

#define OFX_ECONOMIC_RISE 1
#define OFX_ECONOMIC_FALL 0

class ofxEconomics {
    
public:
    
    ofxEconomics();
    void update();
    void draw(int x, int y);
    
    float getValueAt(float prc);
    
    ofEvent<float> onEconomicRise;
    ofEvent<float> onEconomicFall;
    
    deque<float> data;
    int randomCounter;
    int economicState;
    
};