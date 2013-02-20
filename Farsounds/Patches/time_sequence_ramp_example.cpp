//
//  time_sequence_ramp_example.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/20/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "time_sequence_ramp_example.h"
#include "FSEnvironment.h"
#include "FSUtils.h"
#include "FSPatch.h"
#include "FSSineModule.h"
#include "FSPhasorModule.h"
#include "FSTimedTriggerModule.h"
#include "FSADSREnvelopeModule.h"
#include "FSSequenceModule.h"
#include "FSRampModule.h"
#include "FSScalerModule.h"
#include "FSAllpassModule.h"
#include "FSMoogFilterModule.h"



FSPatch *singleSequencer(double freqScale, double ampScale, double moogFreq, double moogSpeed, double rampTime, double rampShape,
                         double *frequencies, int numFrequencies, double *triggerTimes, int numTriggerTimes)
{
    FSPatch *sequencerPatch = new FSPatch(0, 1);
    FSPhasorModule *phasor = new FSPhasorModule();
    FSMoogFilterModule *moogFilter = new FSMoogFilterModule(moogFreq, 0.8);
    FSSineModule *moogFreqControl = new FSSineModule(moogSpeed);
    FSScalerModule *moogFreqScaler = new FSScalerModule(moogFreq, moogFreq + 500);
    FSTimedTriggerModule *trigger = new FSTimedTriggerModule(triggerTimes, numTriggerTimes, 0, true);
    FSSequenceModule *sequencer = new FSSequenceModule(frequencies, numFrequencies);
    FSRampModule *rampModule = new FSRampModule(100.0, 0.0, rampTime, rampShape);
    FSADSREnvelopeModule *adsr = new FSADSREnvelopeModule();
    FSScalerModule *freqScaler = new FSScalerModule(freqScale);
    FSScalerModule *ampScaler = new FSScalerModule();
    
    sequencerPatch->addModule(phasor);
    sequencerPatch->addModule(moogFilter);
    sequencerPatch->addModule(moogFreqControl);
    sequencerPatch->addModule(moogFreqScaler);
    sequencerPatch->addModule(trigger);
    sequencerPatch->addModule(sequencer);
    sequencerPatch->addModule(rampModule);
    sequencerPatch->addModule(adsr);
    sequencerPatch->addModule(freqScaler);
    sequencerPatch->addModule(ampScaler);
    
    sequencer->connect(trigger, 0, 0);
    rampModule->connect(trigger, 0, 0);
    rampModule->connect(sequencer, 0, 2);
    freqScaler->connect(rampModule, 0, 0);
    adsr->connect(trigger, 0, 0);
    adsr->connect(trigger, 1, 1);
    phasor->connect(freqScaler, 0, 0);
    ampScaler->connect(phasor, 0, 0);
    ampScaler->connect(adsr, 0, 1);
    moogFreqScaler->connect(moogFreqControl, 0, 0);
    moogFilter->connect(ampScaler, 0, 0);
    moogFilter->connect(moogFreqScaler, 0, 1);
    
    sequencerPatch->outputProxyAtIndex(0)->connect(moogFilter, 0, 0);
    
    adsr->envelope->attackLevel = ampScale;
    adsr->envelope->decayLevel = ampScale * 0.7;
    adsr->envelope->attackTimePercentage = 0.0125;
    adsr->envelope->decayTimePercentage = 0.0125;
    adsr->envelope->sustainTimePercentage = 0.6;
    
    return sequencerPatch;
}

void timed_sequence_ramp_example()
{
    FSUtils::seedRand();
    
    double triggerTimes[] = {0.125, 0.125, 0.125, 0.25, 0.25, 0.5, 0.25, 0.5, 1.0, 0.0625, 0.0625, 0.0625};
    double triggerTimes2[] = {0.375, 1.0, 1.75, 0.1875};
    double triggerTimes3[] = {0.625, 1.5, 1.1875};
    double frequencies[] = {FSUtils::mtof(48), FSUtils::mtof(51), FSUtils::mtof(55), FSUtils::mtof(53),
        FSUtils::mtof(51), FSUtils::mtof(50), FSUtils::mtof(62), FSUtils::mtof(62),
        FSUtils::mtof(48)};
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    FSPatch *sequencer1 = singleSequencer(1.0, 0.375, 3000.0, 0.1, 0.025, 3.0, frequencies, 9, triggerTimes, 12);
    FSPatch *sequencer2 = singleSequencer(0.5, 0.75, 700.0, 0.06, 0.0375, 3.0, frequencies, 9, triggerTimes2, 4);
    FSPatch *sequencer3 = singleSequencer(6.0, 0.275, 1000.0, 0.076, 0.175, 0.25, frequencies, 9, triggerTimes3, 3);
    FSAllpassModule *allpass = new FSAllpassModule(0.625 * FSEnvironment::sampleRate, 0.2);
    
    mainPatch->addModule(sequencer1);
    mainPatch->addModule(sequencer2);
    mainPatch->addModule(sequencer3);
    mainPatch->addModule(allpass);
    
    allpass->connect(sequencer3, 0, 0);
    
    mainPatch->outputProxyAtIndex(0)->connect(sequencer1, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(sequencer2, 0, 0);
    mainPatch->outputProxyAtIndex(0)->connect(allpass, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(allpass, 0, 0);
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 40);
    
    delete mainPatch;
}