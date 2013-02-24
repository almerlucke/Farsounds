//
//  dx7_example.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/23/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "dx7_example.h"


#include <iostream>
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

FSDX7Settings settings1()
{
    FSDX7Settings dx7Settings;
    
    dx7Settings.setPitchScale(3.51, 5.2, 3, 2.0, 4, 2.0);
    dx7Settings.setVelocityLevel(0.3, 0.2, 0.2, 0.3, 0.1, 0.3);
    dx7Settings.setFeedbackLevel(0.0, 0, 0, 0, 0.25, 0);
    dx7Settings.setPitchIndependent(false, false, false, false, false, false);
    dx7Settings.setAttackLevel(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackTime(0.01, 0.02, 0.03, 0.01, 0.01, 0.01);
    dx7Settings.setDecayLevel(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    dx7Settings.setDecayShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setDecayTime(0.1, 0.2, 0.02, 0.01, 0.01, 0.01);
    dx7Settings.setSustainTime(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
    dx7Settings.setReleaseShape(3, 3, 3, 3, 3, 3);
    dx7Settings.setWave(FSDX7OperatorWaveSine);
        
    return dx7Settings;
}

FSDX7Settings settings2()
{
    FSDX7Settings dx7Settings;
    
    dx7Settings.setPitchScale(4.0, 3.1, 2.0, 0.5, 5.5, 1.0);
    dx7Settings.setVelocityLevel(0.6, 0.3, 0.3, 0.3, 0.4, 0.3);
    dx7Settings.setFeedbackLevel(0.3, 0, 0, 0, 0, 0);
    dx7Settings.setPitchIndependent(false, false, false, false, false, false);
    dx7Settings.setAttackLevel(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackTime(0.01, 0.02, 0.03, 0.01, 0.01, 0.01);
    dx7Settings.setDecayLevel(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    dx7Settings.setDecayShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setDecayTime(0.01, 0.02, 0.02, 0.01, 0.01, 0.01);
    dx7Settings.setSustainTime(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    dx7Settings.setReleaseShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setWave(FSDX7OperatorWaveSine);
    
    return dx7Settings;
}

FSDX7Settings settings3()
{
    FSDX7Settings dx7Settings;
    
    dx7Settings.setPitchScale(12.1, 2.0, 4.01, 8.01, 4.0, 2.01);
    dx7Settings.setVelocityLevel(0.1, 0.3, 0.3, 0.2, 0.2, 0.3);
    dx7Settings.setFeedbackLevel(0.15, 0, 0, 0, 0, 0);
    dx7Settings.setPitchIndependent(false, false, false, false, false, false);
    dx7Settings.setAttackLevel(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setAttackTime(0.01, 0.01, 0.01, 0.01, 0.02, 0.02);
    dx7Settings.setDecayLevel(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    dx7Settings.setDecayShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setDecayTime(0.01, 0.01, 0.01, 0.01, 0.02, 0.02);
    dx7Settings.setSustainTime(0.01, 0.02, 0.02, 0.02, 0.02, 0.02);
    dx7Settings.setReleaseShape(1, 1, 1, 1, 1, 1);
    dx7Settings.setWave(FSDX7OperatorWaveSine);
    
    return dx7Settings;
}

void dx7_example()
{
    FSUtils::seedRand();
    
    double times[8] = {0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.8, -0.8};
    double frequencies[12] = {
        FSUtils::mtof(36), FSUtils::mtof(53), FSUtils::mtof(69),
        FSUtils::mtof(48), FSUtils::mtof(41), FSUtils::mtof(45),
        FSUtils::mtof(84), FSUtils::mtof(83), FSUtils::mtof(79),
        FSUtils::mtof(60), FSUtils::mtof(72), FSUtils::mtof(71)};
    double amps1[5] = {0.5, 0.6, 0.4, 0.6, 0.7};
    
    double times2[9] = {0.6, 0.6, 0.1, 0.1, -0.6, 1.2, 0.1, 0.1, -0.6};
    double frequencies2[12] = {
        FSUtils::mtof(60), FSUtils::mtof(62), FSUtils::mtof(64), FSUtils::mtof(65),
        FSUtils::mtof(72), FSUtils::mtof(74), FSUtils::mtof(77), FSUtils::mtof(76),
        FSUtils::mtof(96), FSUtils::mtof(98), FSUtils::mtof(96), FSUtils::mtof(101)};
    double amps2[5] = {1.0, 0.6, 0.4, 0.6, 0.7};
    
    double times3[7] = {1.2, 1.2, 1.2, 1.2, 1.2, 0.8, 0.4};
    double frequencies3[8] = {
        FSUtils::mtof(36), FSUtils::mtof(41), FSUtils::mtof(48), FSUtils::mtof(53),
        FSUtils::mtof(38), FSUtils::mtof(43), FSUtils::mtof(48), FSUtils::mtof(47)};
    double amps3[5] = {1.0, 0.8, 0.7, 0.9, 0.7};
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    
    FSTimedTriggerModule *trigger1 = new FSTimedTriggerModule(times, 8, 0, true);
    FSSequenceModule *sequencer1 = new FSSequenceModule(frequencies, 12);
    FSSequenceModule *ampSequencer1 = new FSSequenceModule(amps1, 5);
    FSRampModule *ramp1 = new FSRampModule(100, 100, 0.02, 1.6);
    
    FSTimedTriggerModule *trigger2 = new FSTimedTriggerModule(times2, 9, 0, true);
    FSSequenceModule *sequencer2 = new FSSequenceModule(frequencies2, 12);
    FSSequenceModule *ampSequencer2 = new FSSequenceModule(amps2, 5);
    FSRampModule *ramp2 = new FSRampModule(100, 100, 0.02, 1.6);
    
    FSTimedTriggerModule *trigger3 = new FSTimedTriggerModule(times3, 7, 0, true);
    FSSequenceModule *sequencer3 = new FSSequenceModule(frequencies3, 8);
    FSSequenceModule *ampSequencer3 = new FSSequenceModule(amps3, 5);
    FSRampModule *ramp3 = new FSRampModule(100, 100, 0.003, 1.6);
    
    FSMultiplierModule *amp1 = new FSMultiplierModule(2);
    FSMultiplierModule *amp2 = new FSMultiplierModule(2);
    FSMultiplierModule *amp3 = new FSMultiplierModule(2);
    FSAllpassModule *allpass1 = new FSAllpassModule(FSEnvironment::sampleRate * 0.6, 0.5);
    FSAllpassModule *allpass2 = new FSAllpassModule(FSEnvironment::sampleRate * 0.6, 0.6);
    FSAllpassModule *allpass3 = new FSAllpassModule(FSEnvironment::sampleRate * 0.8, 0.3);
    FSPanningModule *pan1 = new FSPanningModule(-0.4);
    FSPanningModule *pan2 = new FSPanningModule(0.0);
    FSPanningModule *pan3 = new FSPanningModule(0.2);
    
    FSDX7 *dx7 = new FSDX7(settings1(), mainPatch);
    dx7->connectTrigger(trigger1, 0);
    dx7->connectDuration(trigger1, 1);
    dx7->connectPitch(ramp1, 0);
    dx7->op4->connectModulator(dx7->op1);
    dx7->op4->connectModulator(dx7->op2);
    dx7->op4->connectModulator(dx7->op3);
    dx7->op6->connectModulator(dx7->op5);
    
    FSDX7 *dx72 = new FSDX7(settings2(), mainPatch);
    dx72->connectTrigger(trigger2, 0);
    dx72->connectDuration(trigger2, 1);
    dx72->connectPitch(ramp2, 0);
    dx72->op2->connectModulator(dx72->op1);
    dx72->op3->connectModulator(dx72->op2);
    dx72->op4->connectModulator(dx72->op3);
    dx72->op6->connectModulator(dx72->op5);
    
    FSDX7 *dx73 = new FSDX7(settings3(), mainPatch);
    dx73->connectTrigger(trigger3, 0);
    dx73->connectDuration(trigger3, 1);
    dx73->connectPitch(ramp3, 0);
    dx73->op2->connectModulator(dx73->op1);
    dx73->op3->connectModulator(dx73->op1);
    dx73->op6->connectModulator(dx73->op4);
    dx73->op6->connectModulator(dx73->op5);
    
    sequencer1->connect(trigger1, 0, 0);
    ramp1->connect(trigger1, 0, 0);
    ramp1->connect(sequencer1, 0, 2);
    ampSequencer1->connect(trigger1, 0, 0);
    amp1->connect(dx7->op4->amp, 0, 0);
    amp1->connect(dx7->op6->amp, 0, 0);
    amp1->connect(ampSequencer1, 0, 1);
    allpass1->connect(amp1, 0, 0);
    pan1->connect(allpass1, 0, 0);
    mainPatch->addModule(amp1);
    mainPatch->addModule(pan1);
    mainPatch->addModule(ramp1);
    mainPatch->addModule(trigger1);
    mainPatch->addModule(allpass1);
    mainPatch->addModule(sequencer1);
    mainPatch->addModule(ampSequencer1);
    
    sequencer2->connect(trigger2, 0, 0);
    ramp2->connect(trigger2, 0, 0);
    ramp2->connect(sequencer2, 0, 2);
    ampSequencer2->connect(trigger2, 0, 0);
    amp2->connect(dx72->op4->amp, 0, 0);
    amp2->connect(dx72->op6->amp, 0, 0);
    amp2->connect(ampSequencer2, 0, 1);
    allpass2->connect(amp2, 0, 0);
    pan2->connect(allpass2, 0, 0);
    mainPatch->addModule(amp2);
    mainPatch->addModule(pan2);
    mainPatch->addModule(ramp2);
    mainPatch->addModule(trigger2);
    mainPatch->addModule(allpass2);
    mainPatch->addModule(sequencer2);
    mainPatch->addModule(ampSequencer2);
    
    sequencer3->connect(trigger3, 0, 0);
    ramp3->connect(trigger3, 0, 0);
    ramp3->connect(sequencer3, 0, 2);
    ampSequencer3->connect(trigger3, 0, 0);
    amp3->connect(dx73->op2->amp, 0, 0);
    amp3->connect(dx73->op3->amp, 0, 0);
    amp3->connect(dx73->op6->amp, 0, 0);
    amp3->connect(ampSequencer3, 0, 1);
    allpass3->connect(amp3, 0, 0);
    pan3->connect(allpass3, 0, 0);
    mainPatch->addModule(amp3);
    mainPatch->addModule(pan3);
    mainPatch->addModule(ramp3);
    mainPatch->addModule(trigger3);
    mainPatch->addModule(allpass3);
    mainPatch->addModule(sequencer3);
    mainPatch->addModule(ampSequencer3);
    
    mainPatch->outputProxyAtIndex(0)->connect(pan1, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(pan1, 1, 0);
    mainPatch->outputProxyAtIndex(0)->connect(pan2, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(pan2, 1, 0);
    mainPatch->outputProxyAtIndex(0)->connect(pan3, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(pan3, 1, 0);
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 120);
    
    delete dx7;
    delete dx72;
    delete dx73;
    delete mainPatch;
}