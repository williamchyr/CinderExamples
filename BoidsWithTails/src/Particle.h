//
//  Particle.h
//  BoidsWithTails
//
//  Created by Willy Chyr on 11-09-21.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#pragma once
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/Utilities.h"
#include <vector>
#include <list>

using namespace ci;


class Particle {
 public:
    
    Particle();
    Particle( Vec3f loc, Vec3f vel);
    void pullToCenter( const ci::Vec3f &center );
    void update();
    void draw();
    
    Vec3f mLoc;
    Vec3f mVel;
    Vec3f mAcc;
    
    float mRadius;
    int mAge;

    //std::list<Vec3f> tailPositions;
    std::vector<float> tailAlpha;
    
    std::vector<Vec3f> tailPositions;
    
    float r, g, b;
    
    
};