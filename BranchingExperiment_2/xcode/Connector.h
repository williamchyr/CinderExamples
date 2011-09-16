//
//  BranchConnector.h
//  BranchingExperiment_2
//
//  Created by Willy Chyr on 11-09-16.
//  Copyright 2011 Willy Chyr. All rights reserved.
//


#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "cinder/Vector.h"
#include "cinder/Color.h"

using namespace ci;

class Connector {
 public:
    
    void setup( Vec2f loc );
    void setup( Vec2f loc, float angle );
    void update();
    void draw();
    
    float mAngle;
    int length;
    int count;
    Vec2f mInitialLoc;
    Vec2f mEndLoc;
    Vec2f mLoc;
    
    bool mContinue;
    bool isFork;
};



#endif