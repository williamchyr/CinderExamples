//
//  Particle.h
//  ParticleSystemExperiment
//
//  Created by Willy Chyr on 11-09-13.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/Perlin.h"

#include <vector>

using namespace ci;


class Particle {
 public:  
    
    Particle();
    Particle( Vec3f loc, Vec3f vel);
    void update(const Perlin &perlin);
    void draw();
    
    Vec3f mLoc;
    Vec3f mVel;
    
    float mRadius;
    Color mColor;
    
    int mAge;
    int mLifespan;
    float mAgePercentage;
    float mDecay;
    bool mIsDead;
    
    float mXPercentage, mYPercentage;
    
};