#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"

#include "Branch.h"
#include "Fork.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

class BranchingExperiment2DApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
	void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void update();
	void draw();
    
    Vec2f mMouseLoc;
    bool mouseIsPressed;
    list<Branch> mBranches;
    list<Fork> mForks;
    
};

void BranchingExperiment2DApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1800, 1000 );
	settings->setFrameRate( 60.0f );
}

void BranchingExperiment2DApp::setup()
{
    /*
    Branch firstBranch;
    firstBranch.setup( Vec2f(getWindowWidth()/2, getWindowHeight()/2) , 5 );
    mBranches.push_back( firstBranch );
    */
    
    mouseIsPressed = false;
}

void BranchingExperiment2DApp::mouseDown( MouseEvent event )
{   
    mouseIsPressed = true;
    
    mMouseLoc = event.getPos();
}

void BranchingExperiment2DApp::mouseUp( MouseEvent event )
{   
    mouseIsPressed = false;
}

void BranchingExperiment2DApp::mouseMove( MouseEvent event )
{
	mMouseLoc = event.getPos();
}

void BranchingExperiment2DApp::mouseDrag( MouseEvent event )
{
	mouseMove( event );
}


void BranchingExperiment2DApp::update()
{
   
    for (list<Branch>::iterator p = mBranches.begin(); p != mBranches.end(); ++p){
        float chance = Rand::randFloat(0.0f, 1.0f );
        
     
        if (!p->mGrow) {
                if (chance > 0.0f && chance < 0.1f ) {
                    Branch subBranch;
                    subBranch.setup( p->mEndLoc, 5 );
                    mBranches.push_back ( subBranch );
                } else if ( chance > 0.1f && chance < 0.6f ) {
                    Fork subFork;
                    subFork.setup( p->mEndLoc);
                    mForks.push_back ( subFork );
                }
            p->mGrow = true;
        }        
    }
    
    for (list<Fork>::iterator p = mForks.begin(); p != mForks.end(); ++p){
         float chance = Rand::randFloat(0.0f, 1.0f );
        
        if (!p->mGrow) {
            if (chance > 0.0f && chance < 0.4f ) {
                Branch subBranch1;
                subBranch1.setup( p->forkBranch[1].mLoc, 3 );
                mBranches.push_back ( subBranch1 );
            
                Branch subBranch2;
                subBranch2.setup( p->forkBranch[2].mLoc, 3 );
                mBranches.push_back ( subBranch2);
            }
            
            p->mGrow = true;
        }        
    }

  
    
    if (mouseIsPressed) {
        
        Branch subBranch;
        subBranch.setup( mMouseLoc, 5 );
        mBranches.push_back ( subBranch );
        
    }
}

void BranchingExperiment2DApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    glColor3f(0.5f, 1.0f, 0.5f);
    for (list<Branch>::iterator p = mBranches.begin(); p != mBranches.end(); ++p){
        p->draw();
    }
    
    glColor3f(0.5f, 0.5f, 1.0f);
    for (list<Fork>::iterator p = mForks.begin(); p != mForks.end(); ++p){
        p->draw();
    }

    
}


CINDER_APP_BASIC( BranchingExperiment2DApp, RendererGl )
