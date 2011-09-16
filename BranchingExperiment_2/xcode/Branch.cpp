//
//  Branch.cpp
//  BranchingExperiment_2
//
//  Created by Willy Chyr on 11-09-16.
//  Copyright 2011 Willy Chyr. All rights reserved.
//


#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/Color.h"
#include "Branch.h"


using namespace ci;

void Branch::setup( Vec2f loc ) {
    mLoc = loc;
    
    startConnector.setup( mLoc);
    mConnectors.push_back( startConnector );
}

void Branch::update(){
    
      for (list<Connector>::iterator p = mConnectors.begin(); p != mConnectors.end(); ++p){
          p->update();
                   
          if (p->mContinue) {
              
              float chance = Rand::randFloat(0.0f, 1.0f);
              
              if (chance < 0.5f ){
                  
                  //This angle determines the angle of the connector. We make it between -0.5f and 0.5f to keep it straight. (they're multiplied by pi in connector setup)
                  float angle = Rand::randFloat(-0.5f, 0.5f);
                  
                  Connector subConnector;
                  subConnector.setup( p->mEndLoc, angle );
                  mConnectors.push_back( subConnector );
              } else if ( chance > 0.5f && chance < 0.9f ) {
                  mForks.push_back( Fork( p->mEndLoc) );
              } 
            
              p->mContinue = false;
          }
      }
    
    for (list<Fork>::iterator p = mForks.begin(); p != mForks.end(); ++p){
        p->update();
        
        if (p->forkConnector[0].mContinue) {
            
            float chance0 = Rand::randFloat(0.0f, 1.0f);
            
            if (chance0 < 0.8f ){
                
                Connector subConnector;
                subConnector.setup( p->forkConnector[0].mEndLoc );
                mConnectors.push_back( subConnector );
            } 
            
            p->forkConnector[0].mContinue = false;
        }
        
        if (p->forkConnector[1].mContinue) {
            
            float chance1 = Rand::randFloat(0.0f, 1.0f);
            
            if (chance1 < 0.8f ){
                
                Connector subConnector;
                subConnector.setup( p->forkConnector[1].mEndLoc );
                mConnectors.push_back( subConnector );
            } 
            
            p->forkConnector[1].mContinue = false;
        }
    }

}

void Branch::draw() {
    
    glColor3f( 1.0f, 0.5f, 0.5f);
    for (list<Connector>::iterator p = mConnectors.begin(); p != mConnectors.end(); ++p){
        p->draw();
    }
    
    glColor3f( 0.5f, 1.0f, 0.2f);
    for (list<Fork>::iterator p = mForks.begin(); p != mForks.end(); ++p){
        p->draw();
    }

}