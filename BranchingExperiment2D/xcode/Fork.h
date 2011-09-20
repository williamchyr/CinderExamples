//
//  Fork.h
//  BranchingExperiment2D
//
//  Created by Willy Chyr on 11-09-15.
//  Copyright 2011 Willy Chyr. All rights reserved.
//


#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "Node.h"
#include "Branch.h"
#include <list>

using namespace ci;

class Fork {
public:
    
    Fork();
    void setup( Vec2f loc);
    void draw();
    
    Vec2f mLoc;
    
    Branch forkBranch[3];
    
    float r, g, b;
    
    bool mGrow;
    
};

