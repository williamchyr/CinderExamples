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
using std::vector;

Branch::Branch() 
{
}

void Branch::setup( Vec2f loc, int numberOfNodes) 
{
    mLoc = loc;
    mNumberOfNodes = numberOfNodes;
    
    mNodes.push_back( Node( mLoc ) );
    
    for (int i = 0; i < numberOfNodes-1; i++) {              
        float randomAngle = Rand::randFloat(0, 2*M_PI );
        float offSet = Rand::randFloat(randomAngle + M_PI*(0.2f), randomAngle + M_PI*(0.8f) );
        mLoc = mLoc + Vec2f( sin(offSet), cos(offSet) ) * 50.0f;        
        mNodes.push_back( Node( mLoc) );
    }
    
    mEndLoc = mLoc;
    
    r = Rand::randFloat(0.0f, 1.0f);
    b = Rand::randFloat(0.0f, 1.0f);
    g = Rand::randFloat(0.0f, 1.0f);  
    
    mGrow = false;
    
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
   
    /*
    for (list<Node>::iterator p = mNodes.begin(); p != mNodes.end(); ++p){
        p->draw();
    }
    */
    
    for (int i = 0; i < mNodes.size(); i++ ) {
        mNodes[i].draw();
        if ( i > 0 ) {
            gl::drawLine( mNodes[i-1].mLoc, mNodes[i].mLoc );
        } 
    }
    
    /*
    for (list<Branch>::iterator j = subBranches.begin(); j != subBranches.end(); ++j){
        j->draw();
    }
     */
}