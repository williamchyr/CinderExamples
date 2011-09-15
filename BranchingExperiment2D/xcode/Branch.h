//
//  Branch.h
//  BranchingExperiment2D
//
//  Created by William Chyr on 11-09-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef BranchingExperiment2D_Branch_h
#define BranchingExperiment2D_Branch_h

#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "Node.h"
#include <list>


using namespace ci;

class Branch {
 public:
    
    Branch();
    void setup( Vec2f loc);
    void update();
    void draw();
    
    int numberOfNodes;
    
    Vec2f mLoc;
    
    std::list<Node>	mNodes;
    
    std::list<Branch> subBranches;
    
    float r, g, b;
};

#endif
