//
//  Branch.cpp
//  BranchingExperiment2D
//
//  Created by William Chyr on 11-09-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "Branch.h"

using namespace ci;
using namespace ci::app;
using std::list;

Branch::Branch() 
{
}

void Branch::setup( Vec2f loc) 
{
    mLoc = loc;
    numberOfNodes = Rand::randInt(5, 7);
    
    for (int i = 0; i < numberOfNodes; i++) {
        mNodes.push_back( Node( mLoc) );
        float offSet = Rand::randFloat(M_PI*(0.2f), M_PI*(0.8f) );
        mLoc = mLoc + Vec2f( sin(offSet), cos(offSet) ) * 50.0f;
    }
   
    
    r = Rand::randFloat(0.0f, 1.0f);
    b = Rand::randFloat(0.0f, 1.0f);
    g = Rand::randFloat(0.0f, 1.0f);
}


void Branch::update()
{
    
    /*
    float offSet = Rand::randFloat(M_PI*(0.2f), M_PI*(0.8f) );
    mLoc = mLoc + Vec2f( sin(offSet), cos(offSet) ) * 20.0f;
    
    float chance = Rand::randFloat( 0.0f, 1.0f);
    
    if ( chance < 0.3f) {
        mNodes.push_back( Node( mLoc) );
    } else {
        Branch newBranch;
        newBranch.setup( mLoc);
        subBranches.push_back( newBranch ); 
    }
    
    for (list<Branch>::iterator j = subBranches.begin(); j != subBranches.end(); ++j){
        j->update();
    }
     */
    
}

void Branch::draw()
{
    glColor3f( 1, 1, 1);
    for (list<Node>::iterator p = mNodes.begin(); p != mNodes.end(); ++p){
        p->draw();
    }
    
    /*
    for (list<Branch>::iterator j = subBranches.begin(); j != subBranches.end(); ++j){
        j->draw();
    }
     */
}