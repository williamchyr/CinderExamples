#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "Branch.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

class BranchingExperiment2DApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

    
    list<Branch> mBranches;
    
};

void BranchingExperiment2DApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1800, 1000 );
	settings->setFrameRate( 60.0f );
}

void BranchingExperiment2DApp::setup()
{
    Branch firstBranch;
    firstBranch.setup( Vec2f(getWindowWidth()/2, getWindowHeight()/2) );
    mBranches.push_back( firstBranch );
}

void BranchingExperiment2DApp::mouseDown( MouseEvent event )
{
}

void BranchingExperiment2DApp::update()
{
    
    for (list<Branch>::iterator p = mBranches.begin(); p != mBranches.end(); ++p){
        float chance = Rand::randFloat(0.0f, 1.0f );
        
        if (chance < 0.3f ) {
            Branch subBranch;
            subBranch.setup( p->mLoc );
            mBranches.push_back ( subBranch );
        }
        
    }
}

void BranchingExperiment2DApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    for (list<Branch>::iterator p = mBranches.begin(); p != mBranches.end(); ++p){
        p->draw();
        
    }

    
}


CINDER_APP_BASIC( BranchingExperiment2DApp, RendererGl )
