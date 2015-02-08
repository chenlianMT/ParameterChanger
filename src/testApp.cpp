#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{
	ofSetWindowTitle( "IACD-Combining two OfxAddons" );
	ofBackground( 0, 0, 0 );
	ofSetFrameRate( 60 );
	
	if ( !m_emitter.loadFromXml( "circles_beitai.pex" ) )
	{
		ofLog( OF_LOG_ERROR, "testApp::setup() - failed to load emitter config" );
	}
    
    varispeed.setup(kAudioUnitType_FormatConverter, kAudioUnitSubType_Varispeed);
    lowpass.setup(kAudioUnitType_Effect, kAudioUnitSubType_LowPassFilter);
    filePlayer.connectTo(varispeed).connectTo(lowpass).connectTo(tap).connectTo(output);
    AudioUnitSetParameter(lowpass, kLowPassParam_Resonance, kAudioUnitScope_Global, 0, 10, 0);
    lowpass.printParameterList();
    output.start();
    
    filePlayer.setFile(ofFilePath::getAbsolutePath("chopin.mp3"));
    filePlayer.loop();
    
    ofSetVerticalSync(true);

}

//--------------------------------------------------------------
void testApp::exit()
{
	// TODO
}

//--------------------------------------------------------------
void testApp::update()
{
    m_emitter.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
    ofBackground(29,65,88);
    ofSetColor(138, 137, 129);
    ofSetLineWidth(1);
    float step = float(ofGetHeight()) / 16;
    for(int x = 0; x < ofGetWidth(); x += step)
    {
        ofLine(x, 0, x, ofGetHeight());
    }
    for(int y = 0; y < ofGetHeight(); y += step)
    {
        ofLine(0, y, ofGetWidth(), y);
    }
    
    ofDrawBitmapString("|\nFilter\nFrequency\n|", ofPoint(40, ofGetHeight()/2));
    
    ofDrawBitmapString("<- Playback Speed ->", ofPoint(ofGetWidth()/2 - 100, ofGetHeight() - 40));

    m_emitter.draw(0, 0);
    
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key)
{
	// nothing
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key)
{
	// nothing
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{
    m_emitter.sourcePosition.x = x;
    m_emitter.sourcePosition.y = y;
    
    float newSpeed = ofMap(x, 0, ofGetWidth(), 0.01, 2, true);
    
    AudioUnitSetParameter(varispeed,
                          kVarispeedParam_PlaybackRate,
                          kAudioUnitScope_Global,
                          0,
                          newSpeed,
                          0);
    
    float newCutoff = ofMap(y, 0, ofGetHeight(), 10, 6900);
    
    AudioUnitSetParameter(lowpass,
                          kLowPassParam_CutoffFrequency,
                          kAudioUnitScope_Global,
                          0,
                          newCutoff,
                          0);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    // nothing
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	// nothing
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	// nothing
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
	// nothing
}
