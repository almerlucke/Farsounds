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
    DX7Settings dx7Settings;
    DX7OperatorSettings *dx7OperatorSettings = &dx7Settings.operatorSettings[0];
    dx7OperatorSettings->pitchScale = 200.1;
    dx7OperatorSettings->velocityLevel = 0.4;
    dx7OperatorSettings->feedbackLevel = 0.2;
    dx7OperatorSettings->pitchIndependent = true;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.021;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.1;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[1];
    dx7OperatorSettings->pitchScale = 2.03;
    dx7OperatorSettings->velocityLevel = 0.4;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.02;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.02;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[2];
    dx7OperatorSettings->pitchScale = 1.01;
    dx7OperatorSettings->velocityLevel = 0.8;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.03;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.02;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[3];
    dx7OperatorSettings->pitchScale = 1.02;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.04;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.021;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[4];
    dx7OperatorSettings->pitchScale = 2.02;
    dx7OperatorSettings->velocityLevel = 0.8;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.01;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[5];
    dx7OperatorSettings->pitchScale = 0.99;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.01;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    return dx7Settings;
}

FSDX7Settings tubularBells2()
{
    DX7Settings dx7Settings;
    DX7OperatorSettings *dx7OperatorSettings = &dx7Settings.operatorSettings[0];
    dx7OperatorSettings->pitchScale = 0.25;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.2;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.01;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[1];
    dx7OperatorSettings->pitchScale = 3.02;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.02;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.02;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[2];
    dx7OperatorSettings->pitchScale = 2.0;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.03;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.02;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[3];
    dx7OperatorSettings->pitchScale = 1.05;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.01;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[4];
    dx7OperatorSettings->pitchScale = 2.01;
    dx7OperatorSettings->velocityLevel = 0.4;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.02;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[5];
    dx7OperatorSettings->pitchScale = 400.1;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = true;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.01;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    return dx7Settings;
}


int main(int argc, const char * argv[])
{
    FSUtils::seedRand();

    double times[5] = {0.15, 0.15, 0.15, 0.3, -0.15};
    double frequencies[12] = {
        FSUtils::mtof(72), FSUtils::mtof(71), FSUtils::mtof(45),
        FSUtils::mtof(67), FSUtils::mtof(41), FSUtils::mtof(55),
        FSUtils::mtof(33), FSUtils::mtof(47), FSUtils::mtof(48),
        FSUtils::mtof(74), FSUtils::mtof(88), FSUtils::mtof(53)};
    double amps1[5] = {1.0, 0.6, 0.4, 0.6, 0.7};
    
    double times2[8] = {0.15, 0.15, 0.15, 0.3, -0.15, 0.15, 0.15, -0.3};
    double frequencies2[4] = {
        FSUtils::mtof(24), FSUtils::mtof(38), FSUtils::mtof(52), FSUtils::mtof(41)};
    double amps2[5] = {1.0, 0.6, 0.4, 0.6, 0.7};
    
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
    FSAllpassModule *allpass1 = new FSAllpassModule(FSEnvironment::sampleRate * 0.6, 0.3);
    FSAllpassModule *allpass2 = new FSAllpassModule(FSEnvironment::sampleRate * 0.45, 0.2);

    DX7 *dx7 = new DX7(settings1(), mainPatch);
    dx7->connectTrigger(trigger1, 0);
    dx7->connectDuration(trigger1, 1);
    dx7->connectPitch(sequencer1, 0);
    dx7->op2->connectModulator(dx7->op1);
    dx7->op3->connectModulator(dx7->op2);
    dx7->op4->connectModulator(dx7->op3);
    dx7->op6->connectModulator(dx7->op5);
    
    DX7 *dx72 = new DX7(settings2(), mainPatch);
    dx72->connectTrigger(trigger2, 0);
    dx72->connectDuration(trigger2, 1);
    dx72->connectPitch(sequencer2, 0);
    dx72->op2->connectModulator(dx72->op1);
    dx72->op3->connectModulator(dx72->op2);
    dx72->op4->connectModulator(dx72->op3);
    dx72->op6->connectModulator(dx72->op5);
    
    sequencer1->connect(trigger1, 0, 0);
    ampSequencer1->connect(trigger1, 0, 0);
    amp1->connect(dx7->op4->amp, 0, 0);
    amp1->connect(dx7->op6->amp, 0, 0);
    amp1->connect(ampSequencer1, 0, 1);
    mainPatch->addModule(amp1);
    mainPatch->addModule(trigger1);
    mainPatch->addModule(allpass1);
    mainPatch->addModule(sequencer1);
    mainPatch->addModule(ampSequencer1);
    
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
    
    mainPatch->outputProxyAtIndex(0)->connect(allpass1, 0, 0);
    mainPatch->outputProxyAtIndex(0)->connect(allpass2, 0, 0);

    FSUtils::generateSoundFile("/Users/almerlucke/Desktop/test2.wav", mainPatch, 60);
    
    delete dx7;
    delete mainPatch;
    
    return 0;
}