//
//  Node.cpp
//  BranchingExperiment2D
//
//  Created by Willy Chyr on 11-09-14.
//  Copyright 2011 Willy Chyr. All rights reserved.
//


#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

#include "Node.h"

using namespace ci;
using namespace ci::app;

Node::Node()
{
}

Node::Node( Vec2f loc ) 
{
    mLoc = loc;
    mRadius = 5.0f;
}

void Node::update()
{
}

void Node::draw()
{
    gl::drawSolidCircle( mLoc, mRadius );
}

