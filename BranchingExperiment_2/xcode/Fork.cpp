//
//  Fork.cpp
//  BranchingExperiment_2
//
//  Created by Willy Chyr on 11-09-16.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "Fork.h"

using namespace ci;

Fork::Fork() {
}

Fork::Fork( Vec2f loc ) {
    mLoc = loc;
    forkConnector[0].setup( mLoc, (0.25f)*M_PI );
    forkConnector[1].setup( mLoc, (1.75f)*M_PI );
    
}

void Fork::update() {
    
    for (int i = 0; i < 2; i++ ){
        forkConnector[i].update();
    }
}


void Fork::draw() {
    
    for (int i = 0; i < 2; i++ ){
        forkConnector[i].draw();
    }
}





