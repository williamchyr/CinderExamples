//
//  Particle.h
//  ParticleSystemExperiment
//
//  Created by Willy Chyr on 11-09-13.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "cinder/Vector.h"
#include "cinder/Color.h"

#include <vector>

using namespace ci;


class Particle {
 public:  
    
    Particle();
    Particle( Vec2f loc, Vec2f vel);
    void update();
    void draw();
    
    Vec2f mLoc;
    Vec2f mVel;
    
    float mRadius;
    Color mColor;
    
    int mAge;
    int mLifespan;
    float mAgePercentage;
    float mDecay;
    bool mIsDead;
    
    float mXPercentage, mYPercentage;
    
};