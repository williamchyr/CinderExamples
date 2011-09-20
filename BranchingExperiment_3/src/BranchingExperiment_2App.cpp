#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIO.h"
#include "cinder/Utilities.h"

#include "Branch.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

class BranchingExperiment_2App : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
	void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
   
    
    list<Branch> mBranches;
    
    bool mouseIsPressed;
    
    Vec2f mMouseVel;
    Vec2f mMouseLoc;
    
    bool mSaveFrames;
};

void BranchingExperiment_2App::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 700);
	settings->setFrameRate( 60.0f );
}

void BranchingExperiment_2App::setup()
{

    mouseIsPressed = false;
    mSaveFrames = false;
    
    gl::enableAlphaBlending();
}

void BranchingExperiment_2App::mouseDown( MouseEvent event )
{   
    mouseIsPressed = true;
    mMouseLoc = event.getPos();
}

void BranchingExperiment_2App::mouseUp( MouseEvent event )
{   
    mouseIsPressed = false;
}

void BranchingExperiment_2App::mouseMove( MouseEvent event )
{   
    mMouseVel = ( event.getPos() - mMouseLoc );
	mMouseLoc = event.getPos();
}

void BranchingExperiment_2App::mouseDrag( MouseEvent event )
{
	mouseMove( event );
}

void BranchingExperiment_2App::keyDown( KeyEvent event )
{
	if( event.getChar() == 's' ){
		mSaveFrames = ! mSaveFrames;
	}
}

void BranchingExperiment_2App::update()
{    
    if (mouseIsPressed) {
        Branch subBranch;
        subBranch.setup( mMouseLoc, mMouseVel);
        mBranches.push_back( subBranch );
    }
    
    for (list<Branch>::iterator p = mBranches.begin(); p != mBranches.end(); ++p){
        p->update();
        
    }
    
    if( mSaveFrames ){
		writeImage( getHomeDirectory() + "branching_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        
        mSaveFrames = false;
	}
}

void BranchingExperiment_2App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    for (list<Branch>::iterator p = mBranches.begin(); p != mBranches.end(); ++p){
        p->draw();
    }
}


CINDER_APP_BASIC( BranchingExperiment_2App, RendererGl )
