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

#include <iostream>

FSDX7Settings tubularBells()
{
    FSDX7Settings dx7Settings;
    
    dx7Settings.setPitchScale(1, 3.5, 1, 3.5, 323.6, 2);
    dx7Settings.setVelocityLevel(0.7, 0.3, 0.4, 0.4, 0.2, 0.2);
    dx7Settings.setFeedbackLevel(0.2);
    dx7Settings.setFixedPitch(false, false, false, false, true, false);
    dx7Settings.setAttackLevel(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackTime(0.01, 0.02, 0.03, 0.01, 0.01, 0.01);
    dx7Settings.setDecayLevel(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    dx7Settings.setDecayShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setDecayTime(0.01, 0.02, 0.02, 0.01, 0.01, 0.01);
    dx7Settings.setSustainTime(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
    dx7Settings.setReleaseShape(3, 3, 3, 3, 3, 3);
    dx7Settings.setWave(FSDX7OperatorWaveSine, FSDX7OperatorWaveSine, FSDX7OperatorWaveSine,
                        FSDX7OperatorWaveSine, FSDX7OperatorWaveSine, FSDX7OperatorWaveSine);
    
    return dx7Settings;
}

FSDX7Settings tubularBells2()
{
    FSDX7Settings dx7Settings;
    
    dx7Settings.setPitchScale(0.5, 3.5, 0.51, 3.5, 333.6, 2.01);
    dx7Settings.setVelocityLevel(0.7, 0.5, 0.4, 0.4, 0.2, 0.5);
    dx7Settings.setFeedbackLevel(0.2);
    dx7Settings.setFixedPitch(false, false, false, false, true, false);
    dx7Settings.setAttackLevel(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackTime(0.01, 0.02, 0.03, 0.01, 0.01, 0.01);
    dx7Settings.setDecayLevel(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    dx7Settings.setDecayShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setDecayTime(0.01, 0.02, 0.02, 0.01, 0.01, 0.01);
    dx7Settings.setSustainTime(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
    dx7Settings.setReleaseShape(3, 3, 3, 3, 3, 3);
    dx7Settings.setWave(FSDX7OperatorWaveSine, FSDX7OperatorWaveSine, FSDX7OperatorWaveSine,
                        FSDX7OperatorWaveSine, FSDX7OperatorWaveSine, FSDX7OperatorWaveSine);
    
    return dx7Settings;
}

FSDX7Settings pipes()
{
    FSDX7Settings dx7Settings;
    
    dx7Settings.setPitchScale(0.5, 0.5, 1, 4, 2, 10);
    dx7Settings.setVelocityLevel(0.7, 0.3, 0.3, 0.7, 0.7, 0.6);
    dx7Settings.setFeedbackLevel(0.2);
    dx7Settings.setFixedPitch(false, false, false, false, false, false);
    dx7Settings.setAttackLevel(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackTime(0.001, 0.002, 0.003, 0.001, 0.001, 0.001);
    dx7Settings.setDecayLevel(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    dx7Settings.setDecayShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setDecayTime(0.001, 0.002, 0.002, 0.001, 0.001, 0.001);
    dx7Settings.setSustainTime(0.001, 0.001, 0.001, 0.001, 0.001, 0.001);
    dx7Settings.setReleaseShape(3, 3, 3, 3, 3, 3);
    dx7Settings.setWave(FSDX7OperatorWaveSine);
    
    return dx7Settings;
}

FSDX7Settings solidBass()
{
    FSDX7Settings dx7Settings;
    
    dx7Settings.setPitchScale(1, 1, 0.5, 0.5, 1, 1);
    dx7Settings.setVelocityLevel(0.7, 0.3, 0.7, 0.4, 0.5, 0.6);
    dx7Settings.setFeedbackLevel(0.2);
    dx7Settings.setFixedPitch(false, false, false, false, false, false);
    dx7Settings.setAttackLevel(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackTime(0.01, 0.02, 0.03, 0.01, 0.01, 0.01);
    dx7Settings.setDecayLevel(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    dx7Settings.setDecayShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setDecayTime(0.01, 0.02, 0.02, 0.01, 0.01, 0.01);
    dx7Settings.setSustainTime(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    dx7Settings.setReleaseShape(3, 3, 3, 3, 3, 3);
    dx7Settings.setWave(FSDX7OperatorWaveTri);
    
    return dx7Settings;
}

FSDX7Settings rhodesSetting()
{
    FSDX7Settings dx7Settings;
    
    dx7Settings.setPitchScale(0.98, 12.0, 1, 1, 1.02, 1.01);
    dx7Settings.setVelocityLevel(0.3, 0.1, 0.3, 0.1, 0.3, 0.1);
    dx7Settings.setFeedbackLevel(0.1);
    dx7Settings.setFixedPitch(false, false, false, false, false, false);
    dx7Settings.setAttackLevel(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackTime(0.01, 0.02, 0.03, 0.01, 0.01, 0.01);
    dx7Settings.setDecayLevel(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    dx7Settings.setDecayShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setDecayTime(0.01, 0.02, 0.02, 0.01, 0.01, 0.01);
    dx7Settings.setSustainTime(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    dx7Settings.setReleaseShape(3, 3, 3, 3, 3, 3);
    dx7Settings.setWave(FSDX7OperatorWaveSine);
    
    return dx7Settings;
}

FSDX7Settings steelDrum()
{
    FSDX7Settings dx7Settings;
    
    dx7Settings.setPitchScale(1, 1.7, 1, 2.07, 5.32, 398.1);
    dx7Settings.setVelocityLevel(0.6, 0.34, 0.6, 0.38, 0.34, 0.29);
    dx7Settings.setFeedbackLevel(0.1);
    dx7Settings.setFixedPitch(false, false, false, false, false, true);
    dx7Settings.setAttackLevel(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackTime(0.01, 0.05, 0.01, 0.05, 0.05, 0.05);
    dx7Settings.setDecayLevel(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    dx7Settings.setDecayShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setDecayTime(0.01, 0.05, 0.01, 0.05, 0.05, 0.05);
    dx7Settings.setSustainTime(0.01, 0.1, 0.01, 0.1, 0.1, 0.1);
    dx7Settings.setReleaseShape(3, 3, 3, 3, 3, 3);
    dx7Settings.setWave(FSDX7OperatorWaveSine);
    
    return dx7Settings;
}

int main(int argc, const char * argv[])
{
    
    FSUtils::seedRand();
    
    double times[12] = {0.2, 0.2, 0.4, 0.2, 0.2, 0.2, 0.4, 0.2, 0.1, 0.1, 0.1, 0.1};
    double frequencies[5] = {
        FSUtils::mtof(36), FSUtils::mtof(108), FSUtils::mtof(96), FSUtils::mtof(84), FSUtils::mtof(60)};
    double amps[5] = {0.5, 0.6, 0.6, 0.5, 0.5};
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    
    FSTimedTriggerModule *trigger = new FSTimedTriggerModule(times, 12, 0, true);
    FSSequenceModule *sequencer = new FSSequenceModule(frequencies, 5);
    FSSequenceModule *ampSequencer = new FSSequenceModule(amps, 5);
    FSRampModule *ramp = new FSRampModule(100, 100, 0.001, 1.6);
    FSMultiplierModule *amp = new FSMultiplierModule(2);
    FSAllpassModule *allpass = new FSAllpassModule(FSEnvironment::sampleRate * 0.3, 0.2);
    FSPanningModule *pan = new FSPanningModule(0);
    
    FSDX7 *dx7 = new FSDX7(tubularBells(), FSDX7_ALGORITHM5, amp, 0, mainPatch);
    dx7->connectTrigger(trigger, 0);
    dx7->connectDuration(trigger, 1);
    dx7->connectPitch(ramp, 0);
    
    FSDX7 *dx7_2 = new FSDX7(tubularBells2(), FSDX7_ALGORITHM5, amp, 0, mainPatch);
    dx7_2->connectTrigger(trigger, 0);
    dx7_2->connectDuration(trigger, 1);
    dx7_2->connectPitch(ramp, 0);
    
    sequencer->connect(trigger, 0, 0);
    ramp->connect(trigger, 0, 0);
    ramp->connect(sequencer, 0, 2);
    ampSequencer->connect(trigger, 0, 0);
    amp->connect(ampSequencer, 0, 1);
    allpass->connect(amp, 0, 0);
    pan->connect(allpass, 0, 0);
    
    mainPatch->addModule(amp);
    mainPatch->addModule(pan);
    mainPatch->addModule(ramp);
    mainPatch->addModule(trigger);
    mainPatch->addModule(allpass);
    mainPatch->addModule(sequencer);
    mainPatch->addModule(ampSequencer);
    
    mainPatch->outputProxyAtIndex(0)->connect(pan, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(pan, 1, 0);
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 20);
    
    delete dx7;
    delete mainPatch;
    
    return 0;
}