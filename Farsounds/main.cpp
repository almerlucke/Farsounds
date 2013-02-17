//
//  main.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include <iostream>
#include "FSEnvironment.h"
#include "FSUtils.h"
#include "FSSoundFile.h"
#include "FSPatch.h"
#include "FSSoundFileModule.h"
#include "FSPhasorModule.h"
#include "FSTimedTriggerModule.h"
#include "FSTriggeredRandomModule.h"
#include "FSSampleAndHoldModule.h"
#include "FSAllpassModule.h"

int main(int argc, const char * argv[])
{
    FSUtils::seedRand();
    
    double triggerTimes[] = {0.125, 0.125, 0.5, 0.25, 0.25, 0.5, 0.25, 0.5, 1.0, 3.0};
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    FSSoundFile *soundFile = new FSSoundFile("/Users/aFrogleap/Desktop/mockin.wav");
    FSSoundFileModule  *sfModule = new FSSoundFileModule(soundFile);
    double normalSpeed = 1.0 / (soundFile->numFrames / soundFile->sampleRate);
    FSPhasorModule *phasor = new FSPhasorModule(normalSpeed);
    FSPhasorModule *sampPhasor = new FSPhasorModule(normalSpeed * 3.456);
    FSTimedTriggerModule *trigger = new FSTimedTriggerModule(triggerTimes, 9, 0, true);
    FSSampleAndHoldModule *sampHold = new FSSampleAndHoldModule();
    FSTriggeredRandomModule *speedRand = new FSTriggeredRandomModule(normalSpeed * 0.075, normalSpeed * 0.5);
    FSAllpassModule *allpass1 = new FSAllpassModule(0.375 * FSEnvironment::sampleRate, 0.75);
    FSAllpassModule *allpass2 = new FSAllpassModule(0.5 * FSEnvironment::sampleRate, 0.8);
    
    mainPatch->addModule(sampPhasor);
    mainPatch->addModule(sampHold);
    mainPatch->addModule(trigger);
    mainPatch->addModule(speedRand);
    mainPatch->addModule(sfModule);
    mainPatch->addModule(phasor);
    mainPatch->addModule(allpass1);
    mainPatch->addModule(allpass2);
    
    sampPhasor->connect(trigger, 2, 0);
    sampHold->connect(sampPhasor, 0, 0);
    sampHold->connect(trigger, 0, 1);
    speedRand->connect(trigger, 0, 0);
    phasor->connect(speedRand, 0, 0);
    phasor->connect(sampHold, 0, 1);
    phasor->connect(trigger, 0, 2);
    sfModule->connect(phasor, 0, 0);
    allpass1->connect(sfModule, 0, 0);
    allpass2->connect(sfModule, 1, 0);
    mainPatch->outputProxyAtIndex(0)->connect(allpass1, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(allpass2, 0, 0);
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 40);
    
    delete soundFile;
    delete mainPatch;
    
    return 0;
}