//
//  Fork.h
//  BranchingExperiment_2
//
//  Created by Willy Chyr on 11-09-16.
//  Copyright 2011 Willy Chyr. All rights reserved.
//


#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "Connector.h"

using namespace ci;

class Fork {
 public:
    Fork();
    Fork( Vec2f loc );
    
    void update();
    void draw();
    
    Vec2f mLoc;
    
    float angle0, angle1;
    Connector forkConnector[2];
    
    bool mIsDead;
    int lifeSpan;
    int age;
    float agePercentage;
    
};
