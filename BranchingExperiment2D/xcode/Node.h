//
//  Node.h
//  BranchingExperiment2D
//
//  Created by Willy Chyr on 11-09-14.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#ifndef BranchingExperiment2D_Node_h
#define BranchingExperiment2D_Node_h


#include "cinder/Vector.h"
using namespace ci;
using namespace ci::app;

class Node{
 public:
    
    Node();
    Node( Vec2f loc);
    
    void update();
    void draw();
    
    Vec2f mLoc;
    
    float mRadius;
    
};

#endif
