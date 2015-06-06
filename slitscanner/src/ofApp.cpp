#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::play(){
    isPlaying = true;
    video.setPaused(false);
}

//--------------------------------------------------------------
void ofApp::pause(){
    isPlaying = false;
    video.setPaused(true);
}

//--------------------------------------------------------------
void ofApp::togglePlay(){
    if (isPlaying){
        isPlaying = false;
        video.setPaused(true);
    } else {
        isPlaying = true;
        video.setPaused(false);
    }
}

//--------------------------------------------------------------
void ofApp::onEconomicRise(float &difference){
    // update the glitchOffset which keeps getting added to the timeline
    glitchOffset = difference*10;
    
    cout << "up " << difference*10 << endl;
}

//--------------------------------------------------------------
void ofApp::onEconomicFall(float &difference){
    // update the glitchOffset which keeps getting added to the timeline
    glitchOffset = difference*10;
    
    cout << "down " << difference*10 << endl;
}


int video_width = 800;
int video_height = 450;



//--------------------------------------------------------------
void ofApp::setup() {
    isFullscreen = false;
    isPlaying = false;
    
    // fill the timeline with nothing
    for (int i = 0; i < 800; i++) {
        timeline.push_back( 0.0f );
    }
    
    // setup the economics numbers
    ofAddListener(economics.onEconomicRise, this, &ofApp::onEconomicRise);
    ofAddListener(economics.onEconomicFall, this, &ofApp::onEconomicFall);
    
    texture.allocate(video_width, video_height, GL_RGB);
    
    // setup the videoplayer
    video.loadMovie("/Users/lukesturgeon/Dropbox/4 - RCA/11 - Glitch Films/2 - Production/Assets/BigFreezeSecondEditSansSon.mp4");
    video.setLoopState(OF_LOOP_NORMAL );
    play();
    
    gui.setup();
    gui.add( yOffsetAmount.set("Y Offset", 100, 0, 500) );
    gui.add( yOffsetSpeed.set("Y Speed", 15, 1, 30) );
    gui.add( yElasticity.set("Elasticity", 0.01f, 0.005f, 0.1f) );
    gui.add( economics.updateThreshold );
    gui.add( col1.set("colour1", ofColor(255,0,0), ofColor(0), ofColor(255)) );
    gui.add( col2.set("colour2", ofColor(0,255,0), ofColor(0), ofColor(255)) );
    gui.add( col3.set("colour3", ofColor(0,0,255), ofColor(0), ofColor(255)) );
}

//--------------------------------------------------------------
void ofApp::update() {
    
    // update video
    video.update();
    if (video.isFrameNew()){
        texture.loadData(video.getPixelsRef());
    }
    
    // update economics
    economics.update();
    
    for (int i = 0; i < yOffsetSpeed; i++) {
        // update timeline
        timeline.pop_front();
        timeline.push_back(glitchOffset);
        
        if (glitchOffset != 0) {
            glitchOffset += (0 - glitchOffset) * yElasticity;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(0);
    
    
    if (noGlitch)
    {
        // draw the original
        video.draw((ofGetWidth() - video.width) / 2, (ofGetHeight() - video.height) / 2, video.width, video.height);
    }
    else
    {
        // draw a glitch
        ofPushMatrix();
        ofTranslate((ofGetWidth() - video.width) / 2, (ofGetHeight() - video.height) / 2);
        
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        
        //draw RED
        ofSetColor(col1);
        video.draw(0, 0);
        
        //draw GREED
        ofSetColor(col2);
        for (int x = 0; x < video_width; x++) {
            texture.drawSubsection(x, timeline[x]*yOffsetAmount, 1, video_height, x, 0);
        }
        
        // draw BLUE
        ofSetColor(col3);
        video.draw(0, 0);
        
        ofDisableBlendMode();
        
        ofPopMatrix();
        
        if (!isFullscreen){
            
            /*ofPushMatrix();
            ofTranslate(0, ofGetHeight()/2);
            
            // draw the offset timeline
            ofSetColor(255);
            for (int i = 0; i < timeline.size()-1; i++) {
                ofLine(i, timeline[i]*100, i+1, timeline[i+1]*100);
            }
            
            ofLine(820, 0, 870, 0);
            ofRect(830, 0, 30, glitchOffset*100);
            
            ofPopMatrix();*/
            
            // debugger
            ofSetColor(255);
            economics.draw(10,ofGetHeight()-130);
            ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, ofGetHeight()-10);
            gui.draw();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'f')
    {
        isFullscreen = !isFullscreen;
        ofSetFullscreen(isFullscreen);
	}
    if (key == 'o')
    {
        noGlitch = !noGlitch;
    }
    if(key == ' ')
    {
        togglePlay();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
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
    string file = dragInfo.files[0];
    video.loadMovie(file);
}
