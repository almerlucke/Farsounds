//
//  markov_example.cpp
//  Farsounds
//
//  Created by Almer Lucke on 5/28/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "markov_example.h"

#include "FSEnvironment.h"
#include "FSUtils.h"
#include "FSPatch.h"
#include "FSTimedTriggerModule.h"
#include "FSMultiplierModule.h"
#include "FSAllpassModule.h"
#include "FSSequenceModule.h"
#include "FSMoogFilterModule.h"
#include "FSDX7.h"

#include "FSSequence.h"
#include "FSSingleValueGenerator.h"
#include "FSSimpleMarkovChain.h"
#include "FSMarkovChainModule.h"

#include <iostream>

FSDX7Settings tubularBells()
{
    FSDX7Settings settings;
    
    settings.setWave(FSDX7OperatorWaveSine);
    settings.setFeedbackLevel(0.0);
    settings.setFixedPitch(false, false, false, false, false, false);
    settings.setPitchScale(1, 1.001, 3.0, 1.002, 1.003, 1.004);
    settings.setVelocityLevel(0.95, 0.78, 0.99, 0.75, 0.99, 0.85);
    settings.setAttackLevel(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    settings.setAttackTime(0.003, 0.003, 0.003, 0.003, 0.003, 0.003);
    settings.setAttackShape(1, 1, 1, 1, 1, 1);
    settings.setDecayLevel(0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
    settings.setDecayTime(0.003, 0.003, 0.003, 0.003, 0.003, 0.003);
    settings.setDecayShape(1, 1, 1, 1, 1, 1);
    settings.setSustainTime(0.3, 0.3, 0.3, 0.3, 0.3, 0.3);
    settings.setReleaseShape(1, 1, 1, 1, 1, 1);
    
    return settings;
}


void markov_example()
{
    FSSequence *fSeq1 = new FSSequence(10,
                                       new FSSingleValueGenerator(FSUtils::mtof(36)),
                                       new FSSingleValueGenerator(FSUtils::mtof(38)),
                                       new FSSingleValueGenerator(FSUtils::mtof(39)),
                                       new FSSingleValueGenerator(FSUtils::mtof(41)),
                                       new FSSingleValueGenerator(FSUtils::mtof(43)),
                                       new FSSingleValueGenerator(FSUtils::mtof(48)),
                                       new FSSingleValueGenerator(FSUtils::mtof(50)),
                                       new FSSingleValueGenerator(FSUtils::mtof(51)),
                                       new FSSingleValueGenerator(FSUtils::mtof(53)),
                                       new FSSingleValueGenerator(FSUtils::mtof(55)));
    FSSequence *fSeq2 = new FSSequence(10,
                                       new FSSingleValueGenerator(FSUtils::mtof(45)),
                                       new FSSingleValueGenerator(FSUtils::mtof(46)),
                                       new FSSingleValueGenerator(FSUtils::mtof(48)),
                                       new FSSingleValueGenerator(FSUtils::mtof(50)),
                                       new FSSingleValueGenerator(FSUtils::mtof(51)),
                                       new FSSingleValueGenerator(FSUtils::mtof(57)),
                                       new FSSingleValueGenerator(FSUtils::mtof(58)),
                                       new FSSingleValueGenerator(FSUtils::mtof(60)),
                                       new FSSingleValueGenerator(FSUtils::mtof(62)),
                                       new FSSingleValueGenerator(FSUtils::mtof(63)));
    FSSequence *fSeq3 = new FSSequence(10,
                                       new FSSingleValueGenerator(FSUtils::mtof(53)),
                                       new FSSingleValueGenerator(FSUtils::mtof(55)),
                                       new FSSingleValueGenerator(FSUtils::mtof(57)),
                                       new FSSingleValueGenerator(FSUtils::mtof(58)),
                                       new FSSingleValueGenerator(FSUtils::mtof(60)),
                                       new FSSingleValueGenerator(FSUtils::mtof(65)),
                                       new FSSingleValueGenerator(FSUtils::mtof(67)),
                                       new FSSingleValueGenerator(FSUtils::mtof(69)),
                                       new FSSingleValueGenerator(FSUtils::mtof(70)),
                                       new FSSingleValueGenerator(FSUtils::mtof(72)));
    
    FSSimpleMarkovChain *freqChain = new FSSimpleMarkovChain(3, fSeq1, fSeq2, fSeq3);
    
    freqChain->setStates(0, 3,
                         new FSMarkovChainState(0, 3, 0, 0.45, 1, 0.45, 2, 0.1),
                         new FSMarkovChainState(1, 3, 0, 0.1, 1, 0.45, 2, 0.45),
                         new FSMarkovChainState(2, 3, 0, 0.45, 1, 0.1, 2, 0.45));
    
    
    double times[9] = {0.2, 0.2, 0.2, 0.2, 0.4, 0.4, 0.8, 0.6, 0.2};
    double amps[4] = {0.1, 0.2, 0.3, 0.05};
    
    FSPatch *mainPatch = new FSPatch(0, 1);
    
    FSTimedTriggerModule *trigger = new FSTimedTriggerModule(times, 9, 0, true);
    FSMarkovChainModule *markovFreq = new FSMarkovChainModule(freqChain);
    FSSequenceModule *ampSequencer = new FSSequenceModule(amps, 4);
    FSMultiplierModule *amp = new FSMultiplierModule(2);
    FSMoogFilterModule *moog = new FSMoogFilterModule(8000.0, 0.6);
    FSAllpassModule *allpass = new FSAllpassModule(FSEnvironment::sampleRate * 1.2, 0.5);
    FSMultiplierModule *dryAmp = new FSMultiplierModule(0.7);
    FSMultiplierModule *wetAmp = new FSMultiplierModule(0.2);
    
    FSDX7 *dx7 = new FSDX7(tubularBells(), FSDX7_ALGORITHM12, amp, 0, mainPatch);
    dx7->connectTrigger(trigger, 0);
    dx7->connectDuration(trigger, 1);
    dx7->connectPitch(markovFreq, 0);
    
    markovFreq->connect(trigger, 0, 0);
    ampSequencer->connect(trigger, 0, 0);
    amp->connect(ampSequencer, 0, 1);
    moog->connect(amp, 0, 0);
    allpass->connect(moog, 0, 0);
    dryAmp->connect(moog, 0, 0);
    wetAmp->connect(allpass, 0, 0);
    
    mainPatch->addModule(moog);
    mainPatch->addModule(amp);
    mainPatch->addModule(trigger);
    mainPatch->addModule(allpass);
    mainPatch->addModule(markovFreq);
    mainPatch->addModule(ampSequencer);
    mainPatch->addModule(dryAmp);
    mainPatch->addModule(wetAmp);
    
    mainPatch->outputProxyAtIndex(0)->connect(dryAmp, 0, 0);
    mainPatch->outputProxyAtIndex(0)->connect(wetAmp, 0, 0);
    
    FSUtils::generateSoundFile("/Users/almerlucke/Desktop/markov.wav", mainPatch, 120);
    
    delete dx7;
    delete mainPatch;
}