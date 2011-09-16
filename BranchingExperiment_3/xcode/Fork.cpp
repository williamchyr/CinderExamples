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
    
    //These two angles determine the angle of the fork branches.
    angle0 = Rand::randFloat(0.0f, 0.5f);
    angle1 = Rand::randFloat(1.5f, 2.0f);
    
    forkConnector[0].setup( mLoc, angle0*M_PI, true);
    forkConnector[1].setup( mLoc, angle1*M_PI, true );
    
    lifeSpan = Rand::randInt(150, 200);
    age = 0;
    agePercentage = 0.0f;
    mIsDead = false;
    
    
}

void Fork::update() {
    
    for (int i = 0; i < 2; i++ ){
        forkConnector[i].update();
    }
    
    age++;
    agePercentage = (float) age / (float) lifeSpan;
    
    if (agePercentage > 1.0f )  {
        mIsDead = true;
    }
     
}


void Fork::draw() {
    
    glColor4f( 0.5f, 1.0f, 0.2f, 1.0f - agePercentage);
    
    for (int i = 0; i < 2; i++ ){
        forkConnector[i].draw();
    }
}





