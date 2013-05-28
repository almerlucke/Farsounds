//
//  main.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//


#include "FSEnvironment.h"
#include "FSUtils.h"
#include "FSPatch.h"
#include "FSTimedTriggerModule.h"
#include "FSMultiplierModule.h"
#include "FSAllpassModule.h"
#include "FSSequenceModule.h"
#include "FSPanningModule.h"
#include "FSRampModule.h"
#include "FSDX7.h"
#include "FSBiquadFilterModule.h"


#include <iostream>


FSDX7Settings tubularBells()
{
    FSDX7Settings settings;
    
    settings.setWave(FSDX7OperatorWaveSine);
    settings.setFeedbackLevel(0.2);
    settings.setFixedPitch(false, false, false, false, false, false);
    settings.setPitchScale(1.0, 1.5, 2.0, 3.51, 4, 2.01);
    settings.setVelocityLevel(0.95, 0.78, 0.99, 0.75, 0.99, 0.85);
    settings.setAttackLevel(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    settings.setAttackTime(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
    settings.setAttackShape(1, 1, 1, 1, 1, 1);
    settings.setDecayLevel(0.3, 0.3, 0.3, 0.3, 0.3, 0.3);
    settings.setDecayTime(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
    settings.setDecayShape(1, 1, 1, 1, 1, 1);
    settings.setSustainTime(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
    settings.setReleaseShape(1, 1, 1, 1, 1, 1);
    
    return settings;
}

FSDX7Settings tubularBells2()
{
    FSDX7Settings settings;
    
    settings.setWave(FSDX7OperatorWaveSine);
    settings.setFeedbackLevel(0.2);
    settings.setFixedPitch(false, false, false, false, false, false);
    settings.setPitchScale(1.01, 3.5, 1.02, 3.54, 2.0, 2.01);
    settings.setVelocityLevel(0.95, 0.78, 0.99, 0.75, 0.99, 0.85);
    settings.setAttackLevel(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    settings.setAttackTime(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
    settings.setAttackShape(1, 1, 1, 1, 1, 1);
    settings.setDecayLevel(0.3, 0.3, 0.3, 0.3, 0.3, 0.3);
    settings.setDecayTime(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
    settings.setDecayShape(1, 1, 1, 1, 1, 1);
    settings.setSustainTime(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
    settings.setReleaseShape(1, 1, 1, 1, 1, 1);
    
    return settings;
}


int main(int argc, const char * argv[])
{
    FSUtils::seedRand();
    
    double times[6] = {0.2, 0.2, 0.2, 0.4, 0.40, 0.6};
    double times2[6] = {0.2, 0.20, 0.4, 0.6, 0.20, 0.6};
    double frequencies[5] = {
        FSUtils::mtof(36), FSUtils::mtof(41), FSUtils::mtof(46), FSUtils::mtof(51), FSUtils::mtof(59)};
    double frequencies2[7] = {
        FSUtils::mtof(48), FSUtils::mtof(48), FSUtils::mtof(41), FSUtils::mtof(27), FSUtils::mtof(46), FSUtils::mtof(47), FSUtils::mtof(71)};
    double amps[4] = {0.1, 0.2, 0.3, 0.05};
    double amps2[5] = {0.2, 0.2, 0.1, 0.3, 0.05};
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    
    FSTimedTriggerModule *trigger = new FSTimedTriggerModule(times, 6, 0, true);
    FSTimedTriggerModule *trigger2 = new FSTimedTriggerModule(times2, 6, 0, true);
    FSSequenceModule *sequencer = new FSSequenceModule(frequencies, 5);
    FSSequenceModule *sequencer2 = new FSSequenceModule(frequencies2, 7);
    FSSequenceModule *ampSequencer = new FSSequenceModule(amps, 4);
    FSSequenceModule *ampSequencer2 = new FSSequenceModule(amps2, 5);
    FSRampModule *ramp = new FSRampModule(100, 100, 0.01, 0.3);
    FSRampModule *ramp2 = new FSRampModule(100, 100, 0.01, 0.6);
    FSMultiplierModule *amp = new FSMultiplierModule(2);
    FSMultiplierModule *amp2 = new FSMultiplierModule(2);
    FSAllpassModule *allpass = new FSAllpassModule(FSEnvironment::sampleRate * 0.3, 0.4);
    FSAllpassModule *allpass2 = new FSAllpassModule(FSEnvironment::sampleRate * 0.6, 0.4);
    
    FSDX7 *dx7 = new FSDX7(tubularBells(), FSDX7_ALGORITHM24, amp, 0, mainPatch);
    dx7->connectTrigger(trigger, 0);
    dx7->connectDuration(trigger, 1);
    dx7->connectPitch(ramp, 0);
    
    FSDX7 *dx7_2 = new FSDX7(tubularBells2(), FSDX7_ALGORITHM25, amp2, 0, mainPatch);
    dx7_2->connectTrigger(trigger2, 0);
    dx7_2->connectDuration(trigger2, 1);
    dx7_2->connectPitch(ramp2, 0);
    
    sequencer->connect(trigger, 0, 0);
    ramp->connect(trigger, 0, 0);
    ramp->connect(sequencer, 0, 2);
    ampSequencer->connect(trigger, 0, 0);
    amp->connect(ampSequencer, 0, 1);
    allpass->connect(amp, 0, 0);
    
    sequencer2->connect(trigger2, 0, 0);
    ramp2->connect(trigger2, 0, 0);
    ramp2->connect(sequencer2, 0, 2);
    ampSequencer2->connect(trigger2, 0, 0);
    amp2->connect(ampSequencer2, 0, 1);
    allpass2->connect(amp2, 0, 0);
    
    mainPatch->addModule(amp);
    mainPatch->addModule(ramp);
    mainPatch->addModule(trigger);
    mainPatch->addModule(allpass);
    mainPatch->addModule(sequencer);
    mainPatch->addModule(ampSequencer);
    
    mainPatch->addModule(amp2);
    mainPatch->addModule(ramp2);
    mainPatch->addModule(trigger2);
    mainPatch->addModule(allpass2);
    mainPatch->addModule(sequencer2);
    mainPatch->addModule(ampSequencer2);
    
    mainPatch->outputProxyAtIndex(0)->connect(allpass, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(allpass2, 0, 0);
    
    FSUtils::generateSoundFile("/Users/almerlucke/Desktop/test3.wav", mainPatch, 120);
    
    delete dx7;
    delete mainPatch;
    
    return 0;
}