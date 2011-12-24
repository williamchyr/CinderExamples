//
//  Turtle.cpp
//  AngleConversion
//
//  Created by Willy Chyr on 12/20/11.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "Turtle.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h" 
#include <iostream.h>

using namespace ci;

Turtle::Turtle()
{
}

void Turtle::init( Vec3f position, Vec3f previousAngle, Vec3f rotateAngle, float length, float radius)
{
    mStartPosition = position;
    
    mPreviousAngle = previousAngle;
    mRotateAngle = rotateAngle;
    mAddAngle.set( 0.0f, 0.0f, 0.0f );
    
    mSetAngle = mRotateAngle + mAddAngle;
    
    mFinalAngle = mPreviousAngle + mRotateAngle + mAddAngle;
    
  
    
    mLength = 0.0f;
    mFinalLength = length;
    
    mCartesianDirection = cartesianConvert( mSetAngle );
    mLocalPosition = mCartesianDirection*mFinalLength;
    
    mWorldPosition = coordinateTransform( mLocalPosition );
    
    mRadius = radius;
    

    
    branchNow1 = false;
    branched1 = false;
    
    branchNow2 = false;
    branched2 = false;
}

void Turtle::update( float rotateX, float rotateY, float rotateZ)
{
    mAddAngle.set( rotateX, rotateY, rotateZ);
    
    
    mSetAngle = mRotateAngle + mAddAngle;
    
    mFinalAngle = mPreviousAngle + mRotateAngle + mAddAngle;
    
    mCartesianDirection = cartesianConvert( mSetAngle );
    mLocalPosition = mCartesianDirection*mFinalLength;
    
      mWorldPosition = coordinateTransform( mLocalPosition );
    //mFinalAngle = mPreviousAngleCartesian + mRotateAngleCartesian + mAddAngleCartesian;
    //mFinalAngle.safeNormalize();
    
    //mFinalPosition = mStartPosition + mCartesianDirection * mFinalLength;
    //mFinalPosition = mStartPosition + mFinalAngle*mFinalLength;
    
    if (mLength < mFinalLength) {
        mLength += 1.0f;
        mCurrentPosition = mStartPosition + mCartesianDirection*mLength;
    }
 
    if (mLength > mFinalLength*(3.0f/4.0f) ) {
 
        if (branched1){
            branchNow1 = false;
        }
 
        if (!branched1){
            branchNow1 = true;
            branched1 = true;
        }
    }
 
    if (mLength > mFinalLength*(3.0f/4.0f) ) {
 
        if (branched2){
            branchNow2 = false;
        }
 
        if (!branched2){
            branchNow2 = true;
            branched2 = true;
        }
    }
}

void Turtle::update()
{   
    if (mLength < mFinalLength) {
        mLength += 1.0f;
        //mCurrentPosition = mStartPosition + mCartesianDirection*mLength;
    }
    
    if (mLength > mFinalLength*(2.0f/4.0f) ) {
        
        if (branched1){
            branchNow1 = false;
        }
        
        if (!branched1){
            branchNow1 = true;
            branched1 = true;
        }
    }
    
    if (mLength >= mFinalLength) {
        
        if (branched2){
            branchNow2 = false;
        }
        
        
        if (!branched2){
            branchNow2 = true;
            branched2 = true;
        }
    }
}

void Turtle::draw()
{
    ci::ColorA color1( CM_RGB, 1.0f, 0.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 );
    
    gl::pushMatrices();
    gl::translate( mStartPosition );
    //gl::rotate( mFinalAngle);
    gl::rotate( mPreviousAngle);
    
    // DRAW AXIS
        ci::ColorA colorX( CM_RGB, 1.0f, 1.0f, 0.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorX );
        gl::drawLine( Vec3f(-500.0f, 0.0f, 0.0f), Vec3f(500.0f, 0.0f, 0.0f) );

        ci::ColorA colorY( CM_RGB, 0.0f, 1.0f, 1.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorY );
        gl::drawLine( Vec3f(0.0f, -500.0f, 0.0f), Vec3f(0.0f, 500.0f, 0.0f) );

        ci::ColorA colorZ( CM_RGB, 1.0f, 0.0f, 1.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorZ );
        gl::drawLine( Vec3f(0.0f, 0.0f, -500.0f), Vec3f(0.0f, 0.0f, 500.0f) );

        gl::drawCube( mLocalPosition, Vec3f( 10.0f, 10.0f, 10.0f) );
    gl::pushMatrices();
        gl::rotate( mSetAngle );
        gl::drawCylinder( mRadius, mRadius, mLength, 12, 1 );
        gl::popMatrices();
    gl::popMatrices();
    
    
}

Vec3f Turtle::cartesianConvert( Vec3f angle)
{
    //Converts angle from spherical to cartesian coordinate 
    
    float yAngleAdjust, zAngleAdjust;
    Vec3f cartesianDirection;
    
    yAngleAdjust = ((360.0f -angle.y)/180.0f)*M_PI;
    zAngleAdjust = ((360.0f -angle.z)/180.0f)*M_PI;
    
    cartesianDirection.x = cos(yAngleAdjust)*sin(zAngleAdjust);    
    cartesianDirection.y = cos(zAngleAdjust);
    cartesianDirection.z = sin(yAngleAdjust)*sin(zAngleAdjust);    
    
    return cartesianDirection;
}

Vec3f Turtle::coordinateTransform( Vec3f position )
{
    float xAngle, yAngle, zAngle;
    
    xAngle = ((mPreviousAngle.x)/180.0f)*M_PI;
    yAngle = ((mPreviousAngle.y)/180.0f)*M_PI;
    zAngle = ((mPreviousAngle.z)/180.0f)*M_PI;
    
    Vec3f worldCoordinate;
    
    worldCoordinate.x = position.x + position.x*cos(yAngle) + position.y*sin(yAngle) + cos(xAngle)*position.x - sin(xAngle)*position.z;
    
    worldCoordinate.y = position.y*cos(zAngle) + position.z*sin(zAngle) + position.y - sin(yAngle)*position.x + cos(yAngle)*position.y;
    
    worldCoordinate.z = -position.y*sin(zAngle) + position.z*cos(zAngle) + position.z + sin(xAngle)*position.x + position.z*cos(xAngle);
                                                                                                                
                                                                                                    
    return worldCoordinate;
}