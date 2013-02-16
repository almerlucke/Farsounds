//
//  timed_sequence_example.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/16/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "timed_sequence_example.h"
#include "FSEnvironment.h"
#include "FSUtils.h"
#include "FSPatch.h"
#include "FSSineModule.h"
#include "FSADSREnvelopeModule.h"
#include "FSScalerModule.h"
#include "FSAllpassModule.h"
#include "FSTimedTriggerModule.h"
#include "FSSequenceModule.h"

void timed_sequence_example()
{
    FSUtils::seedRand();
    
    double times[] = {1.0, 0.125, 0.125, 0.25, 0.25, 0.75, -1.25, 0.0625, 0.0625, 0.0625, 0.0625,
        0.0625, 0.0625, 0.03125, 0.03125, 0.03125, 0.03125, 0.03125, 0.03125, 0.125, 0.125, 0.125, 0.125, 0.25, 0.25};
    double freqSequence[] = {FSUtils::mtof(40), FSUtils::mtof(45), FSUtils::mtof(51),
        FSUtils::mtof(52), FSUtils::mtof(57), FSUtils::mtof(63), FSUtils::mtof(44),
        FSUtils::mtof(56), FSUtils::mtof(70), FSUtils::mtof(82),
        FSUtils::mtof(45), FSUtils::mtof(44), FSUtils::mtof(42), FSUtils::mtof(40)};
    double modSequence[] = {FSUtils::mtof(40), FSUtils::mtof(40) * 1.11, FSUtils::mtof(52), FSUtils::mtof(52),
        FSUtils::mtof(57), FSUtils::mtof(57) * 0.99, FSUtils::mtof(56), FSUtils::mtof(56)};
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    FSSineModule *sine = new FSSineModule(1000.0);
    FSSineModule *mod = new FSSineModule(1000.0);
    FSTimedTriggerModule *timedTrigger = new FSTimedTriggerModule(times, 25, 0, true);
    FSADSREnvelopeModule *adsrEnvelope = new FSADSREnvelopeModule();
    FSADSREnvelopeModule *modEnvelope = new FSADSREnvelopeModule();
    FSScalerModule *ampScaler = new FSScalerModule();
    FSScalerModule *modScaler = new FSScalerModule();
    FSSequenceModule *sequencer = new FSSequenceModule(freqSequence, 14);
    FSSequenceModule *modSequencer = new FSSequenceModule(modSequence, 8);
    FSAllpassModule *allpass1 = new FSAllpassModule(0.75 * FSEnvironment::sampleRate, 0.4);
    FSAllpassModule *allpass2 = new FSAllpassModule(0.5 * FSEnvironment::sampleRate, 0.4);
    
    mainPatch->addModule(sine);
    mainPatch->addModule(mod);
    mainPatch->addModule(timedTrigger);
    mainPatch->addModule(adsrEnvelope);
    mainPatch->addModule(modEnvelope);
    mainPatch->addModule(ampScaler);
    mainPatch->addModule(modScaler);
    mainPatch->addModule(sequencer);
    mainPatch->addModule(modSequencer);
    mainPatch->addModule(allpass1);
    mainPatch->addModule(allpass2);
    
    modSequencer->connect(timedTrigger, 0, 0);
    sequencer->connect(timedTrigger, 0, 0);
    mod->connect(modSequencer, 0, 0);
    sine->connect(sequencer, 0, 0);
    sine->connect(modScaler, 0, 1);
    modEnvelope->connect(timedTrigger, 0, 0);
    modEnvelope->connect(timedTrigger, 1, 1);
    adsrEnvelope->connect(timedTrigger, 0, 0);
    adsrEnvelope->connect(timedTrigger, 1, 1);
    modScaler->connect(mod, 0, 0);
    modScaler->connect(modEnvelope, 0, 1);
    ampScaler->connect(sine, 0, 0);
    ampScaler->connect(adsrEnvelope, 0, 1);
    allpass1->connect(ampScaler, 0, 0);
    allpass2->connect(ampScaler, 0, 0);
    
    mainPatch->outputProxyAtIndex(0)->connect(allpass1, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(allpass2, 0, 0);
    
    adsrEnvelope->envelope->attackTimePercentage = 0.01;
    adsrEnvelope->envelope->attackLevel = 0.7;
    adsrEnvelope->envelope->attackShape = 2.0;
    adsrEnvelope->envelope->decayTimePercentage = 0.1;
    adsrEnvelope->envelope->decayLevel = 0.2;
    adsrEnvelope->envelope->sustainTimePercentage = 0.1;
    
    modEnvelope->envelope->attackTimePercentage = 0.01;
    modEnvelope->envelope->attackLevel = 0.22;
    modEnvelope->envelope->attackShape = 2.0;
    modEnvelope->envelope->decayTimePercentage = 0.3;
    modEnvelope->envelope->decayLevel = 0.05;
    modEnvelope->envelope->sustainTimePercentage = 0.3;
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 120);
    
    delete mainPatch;
}