//
//  Fork.cpp
//  BranchingExperiment2D
//
//  Created by Aesthetec on 11-09-15.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "Fork.h"

using namespace ci;
using namespace ci::app;
using std::list;

Fork::Fork(){
}

void Fork::setup( Vec2f loc ) {
   
    mLoc = loc;
    
    forkBranch[0].setup( mLoc, 2);
    forkBranch[1].setup( forkBranch[0].mLoc, 2 );
    forkBranch[2].setup( forkBranch[0].mLoc, 2 );
    
    mGrow = false;
}


void Fork::draw() {
    
  
    for (int i = 0; i < 3; i++ ) {
        forkBranch[i].draw();
    }
}