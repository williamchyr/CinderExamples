#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
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
	void update();
	void draw();
    
    Branch mBranch;
    
    list<Branch> mBranches;
    
    bool mouseIsPressed;
    Vec2f mMouseLoc;
};

void BranchingExperiment_2App::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1800, 1000 );
	settings->setFrameRate( 60.0f );
}

void BranchingExperiment_2App::setup()
{
    mBranch.setup( Vec2f(0, getWindowHeight()/2 ) );
    mouseIsPressed = false;
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
	mMouseLoc = event.getPos();
}

void BranchingExperiment_2App::mouseDrag( MouseEvent event )
{
	mouseMove( event );
}

void BranchingExperiment_2App::update()
{
    mBranch.update();
    
    if (mouseIsPressed) {
        Branch subBranch;
        subBranch.setup( mMouseLoc );
        mBranches.push_back( subBranch );
    }
    
    for (list<Branch>::iterator p = mBranches.begin(); p != mBranches.end(); ++p){
        p->update();
        
    }
}

void BranchingExperiment_2App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    mBranch.draw();
    
    for (list<Branch>::iterator p = mBranches.begin(); p != mBranches.end(); ++p){
        p->draw();
    }
}


CINDER_APP_BASIC( BranchingExperiment_2App, RendererGl )
