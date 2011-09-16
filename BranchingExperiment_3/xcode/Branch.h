//
//  Branch.h
//  BranchingExperiment_2
//
//  Created by Willy Chyr  on 11-09-16.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "Connector.h"
#include "Fork.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

class Branch {
 public:
    void setup( Vec2f loc );
    void update();
    void draw();
    
    Vec2f mLoc;
    
    Connector startConnector;
    
    list<Connector> mConnectors;
    list<Fork> mForks;

};