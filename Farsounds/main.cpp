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
#include "FSPatch.h"
#include "FSSineModule.h"
#include "FSPhasorModule.h"
#include "FSTimedTriggerModule.h"
#include "FSTriggeredRandomModule.h"
#include "FSSequenceModule.h"
#include "FSRampModule.h"
#include "FSScalerModule.h"
#include "FSAllpassModule.h"

int main(int argc, const char * argv[])
{
    FSUtils::seedRand();
    
    double triggerTimes[] = {0.125, 0.125, 0.125, 0.25, 0.25, 0.5, 0.25, 0.5, 1.0, 0.0625, 0.0625, 0.0625};
    double triggerTimes2[] = {0.375, 1.0, 1.75, 0.1875};
    double triggerTimes3[] = {0.625, 1.5, 1.1875};
    double frequencies[] = {400.0, 400.0, 800.0, 600.0, 300.0, 150.0, 450.0, 450.0, 1000.0};
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    FSPhasorModule *sine1 = new FSPhasorModule();
    FSPhasorModule *sine2 = new FSPhasorModule();
    FSPhasorModule *sine3 = new FSPhasorModule();
    FSTimedTriggerModule *trigger1 = new FSTimedTriggerModule(triggerTimes, 12, 0, true);
    FSTimedTriggerModule *trigger2 = new FSTimedTriggerModule(triggerTimes2, 4, 0, true);
    FSTimedTriggerModule *trigger3 = new FSTimedTriggerModule(triggerTimes3, 3, 0, true);
    FSSequenceModule *sequencer1 = new FSSequenceModule(frequencies, 9);
    FSSequenceModule *sequencer2 = new FSSequenceModule(frequencies, 9);
    FSSequenceModule *sequencer3 = new FSSequenceModule(frequencies, 9);
    FSRampModule *rampModule1 = new FSRampModule(100.0, 0.0, 0.025, 3.0);
    FSRampModule *rampModule2 = new FSRampModule(100.0, 0.0, 0.0375, 3.0);
    FSRampModule *rampModule3 = new FSRampModule(100.0, 0.0, 0.075, 0.25);
    FSScalerModule *freq2Scaler = new FSScalerModule(0.375);
    FSScalerModule *freq3Scaler = new FSScalerModule(1.5);
    FSScalerModule *scaler1 = new FSScalerModule(0.25);
    FSScalerModule *scaler2 = new FSScalerModule(0.5);
    FSScalerModule *scaler3 = new FSScalerModule(0.375);
    FSAllpassModule *allpass3 = new FSAllpassModule(0.625 * FSEnvironment::sampleRate, 0.4);
    
    mainPatch->addModule(sequencer1);
    mainPatch->addModule(sine1);
    mainPatch->addModule(trigger1);
    mainPatch->addModule(rampModule1);
    mainPatch->addModule(sequencer2);
    mainPatch->addModule(sine2);
    mainPatch->addModule(trigger2);
    mainPatch->addModule(rampModule2);
    mainPatch->addModule(sequencer3);
    mainPatch->addModule(sine3);
    mainPatch->addModule(trigger3);
    mainPatch->addModule(rampModule3);
    mainPatch->addModule(freq2Scaler);
    mainPatch->addModule(freq3Scaler);
    mainPatch->addModule(scaler1);
    mainPatch->addModule(scaler2);
    mainPatch->addModule(scaler3);
    mainPatch->addModule(allpass3);
    
    sequencer1->connect(trigger1, 0, 0);
    rampModule1->connect(trigger1, 0, 0);
    rampModule1->connect(sequencer1, 0, 2);
    sine1->connect(rampModule1, 0, 0);
    scaler1->connect(sine1, 0, 0);
    
    sequencer2->connect(trigger2, 0, 0);
    freq2Scaler->connect(sequencer2, 0, 0);
    rampModule2->connect(trigger2, 0, 0);
    rampModule2->connect(freq2Scaler, 0, 2);
    sine2->connect(rampModule2, 0, 0);
    scaler2->connect(sine2, 0, 0);
    
    sequencer3->connect(trigger3, 0, 0);
    freq3Scaler->connect(sequencer3, 0, 0);
    rampModule3->connect(trigger3, 0, 0);
    rampModule3->connect(freq3Scaler, 0, 2);
    sine3->connect(rampModule3, 0, 0);
    scaler3->connect(sine3, 0, 0);
    allpass3->connect(scaler3, 0, 0);
    
    scaler1->connect(allpass3, 0, 0);
    scaler2->connect(allpass3, 0, 0);
    
    mainPatch->outputProxyAtIndex(0)->connect(scaler1, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(scaler2, 0, 0);
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 40);
    
    delete mainPatch;
    
    return 0;
}