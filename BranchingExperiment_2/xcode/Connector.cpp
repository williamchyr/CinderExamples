//
//  BranchConnector.cpp
//  BranchingExperiment_2
//
//  Created by Willy Chyr on 11-09-16.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "Connector.h"

using namespace ci;


void Connector::setup( Vec2f loc ) {
    
    mInitialLoc = loc;
    length = Rand::randInt(10, 20);
    mEndLoc = Vec2f( loc.x + length, loc.y );
    
    mLoc = mInitialLoc;
    
    mContinue = false;
    
    count = 0;
    
    isFork = false;
}

void Connector::setup( Vec2f loc, float angle ) {
    
    mInitialLoc = loc;
    mAngle = angle;
    length = Rand::randInt(30, 70);
    mEndLoc = Vec2f( loc.x + cos(mAngle)*length, loc.y + sin(mAngle)*length);
    
    mLoc = mInitialLoc;
    
    mContinue = false;
    
    count = 0;
    
    isFork = true;
}

void Connector::update() {
    
    if (count < length ) {
        if (isFork) {
            mLoc.x = mInitialLoc.x + cos(mAngle)*count;
            mLoc.y = mInitialLoc.y + sin(mAngle)*count;
        } else {
            mLoc.x = mLoc.x + count;
            mLoc.y = mLoc.y;
        }
        count++;
    } else if (count == length ) {
        mContinue = true;
        count++;
    } 
}

void Connector::draw() {
    
    gl::drawLine ( mInitialLoc, mLoc );
}