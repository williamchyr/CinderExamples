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
    
    
    mIsDead = false;
    
}

void Connector::setup( Vec2f loc, float angle, bool isFork ) {
    
    mInitialLoc = loc;
    mAngle = angle;
    length = Rand::randInt(30, 70);
    mEndLoc = Vec2f( loc.x + cos(mAngle)*length, loc.y + sin(mAngle)*length);
    
    mLoc = mInitialLoc;
    
    mContinue = false;
    
    count = 0;
    
    mIsFork = isFork;
    
    mIsDead = false;
    age = 0;
    agePercentage = 0;
    lifeSpan = 150;
    
}

void Connector::update() {
    
    if (count < length ) {
        mLoc.x = mInitialLoc.x + cos(mAngle)*count;
        mLoc.y = mInitialLoc.y + sin(mAngle)*count;
        
        count++;
    } else if (count == length ) {
        mContinue = true;
        count++;
    } 
    
    if (!mIsFork) {
        age++;
        agePercentage = (float) age / (float) lifeSpan;
        if (agePercentage > 1.0f ) {
            mIsDead = true;
        }
    }
    
}

void Connector::draw() {
    
    if (mIsFork){
        gl::drawLine ( mInitialLoc, mLoc );
    } else {
        glColor4f(0.0f, 1.0f, 1.0f, 1.0f - agePercentage);
        gl::drawLine ( mInitialLoc, mLoc );
    }
}