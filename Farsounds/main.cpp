//
//  main.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include <iostream>
#include "FSSineModule.h"
#include "FSPatch.h"
#include "FSUtils.h"
#include "FSADSREnvelopeModule.h"
#include "FSScalerModule.h"
#include "FSTriggerModule.h"
#include "FSSampleAndHoldModule.h"
#include "FSDivisorModule.h"
#include "FSAllpassModule.h"
#include "FSPanningModule.h"
#include "FSTriggeredRandomModule.h"


FSPatch *sinePatch()
{
    FSPatch *mainPatch = new FSPatch(0, 2);
    FSSineModule *sine = new FSSineModule(1000.0);
    FSSineModule *sineModulator = new FSSineModule(1000.0);
    FSTriggeredRandomModule *modRand = new FSTriggeredRandomModule(4.0, 40.0);
    FSTriggeredRandomModule *modAmpRand = new FSTriggeredRandomModule(0.1, 1.0);
    FSScalerModule *modAmpScaler = new FSScalerModule();
    FSPhasorModule *durPhasor = new FSPhasorModule(FSUtils::randRange(0.05, 0.2));
    FSScalerModule *durScaler = new FSScalerModule(FSUtils::randRange(0.4, 1), FSUtils::randRange(0.1, 0.2));
    FSDivisorModule *durDiv = new FSDivisorModule(0.5);
    FSSineModule *panSine = new FSSineModule(FSUtils::randRange(0.04, 0.08), FSUtils::randRange(0, 1));
    FSScalerModule *panScale = new FSScalerModule(0.8);
    FSPhasorModule *freqPhasor = new FSPhasorModule(FSUtils::randRange(0.1, 1.3));
    FSScalerModule *freqScaler = new FSScalerModule(FSUtils::randRange(300, 6000), FSUtils::randRange(40, 100));
    FSSampleAndHoldModule *freqHold = new FSSampleAndHoldModule();
    FSPhasorModule *tickPhasor = new FSPhasorModule(2.0, 0.5);
    FSTriggerModule *tickGen = new FSTriggerModule();
    FSADSREnvelopeModule *adsr = new FSADSREnvelopeModule();
    FSScalerModule *multiplier = new FSScalerModule();
    FSAllpassModule *allpass = new FSAllpassModule(FSUtils::randRange(0.1, 1.0) * FSEnvironment::sampleRate, FSUtils::randRange(0.4, 0.8));
    FSPanningModule *pan = new FSPanningModule(0.8);
    
    mainPatch->addModule(modAmpRand);
    mainPatch->addModule(modAmpScaler);
    mainPatch->addModule(durPhasor);
    mainPatch->addModule(sineModulator);
    mainPatch->addModule(modRand);
    mainPatch->addModule(durScaler);
    mainPatch->addModule(durDiv);
    mainPatch->addModule(panSine);
    mainPatch->addModule(panScale);
    mainPatch->addModule(tickPhasor);
    mainPatch->addModule(tickGen);
    mainPatch->addModule(adsr);
    mainPatch->addModule(multiplier);
    mainPatch->addModule(sine);
    mainPatch->addModule(freqPhasor);
    mainPatch->addModule(freqScaler);
    mainPatch->addModule(freqHold);
    mainPatch->addModule(allpass);
    mainPatch->addModule(pan);
    
    durScaler->connect(durPhasor, 0, 0);
    tickPhasor->connect(durScaler, 0, 0);
    durDiv->connect(durScaler, 0, 1);
    tickGen->connect(tickPhasor, 0, 0);
    adsr->connect(durDiv, 0, 1);
    adsr->connect(tickGen, 0, 0);
    freqScaler->connect(freqPhasor, 0, 0);
    freqHold->connect(freqScaler, 0, 0);
    freqHold->connect(tickGen, 0, 1);
    sine->connect(freqHold, 0, 0);
    modRand->connect(tickGen, 0, 0);
    modAmpRand->connect(tickGen, 0, 0);
    sineModulator->connect(modRand, 0, 0);
    modAmpScaler->connect(sineModulator, 0, 0);
    modAmpScaler->connect(modAmpRand, 0, 1);
    sine->connect(modAmpScaler, 0, 1);
    multiplier->connect(sine, 0, 0);
    multiplier->connect(adsr, 0, 1);
    allpass->connect(multiplier, 0, 0);
    panScale->connect(panSine, 0, 0);
    pan->connect(allpass, 0, 0);
    pan->connect(panScale, 0, 1);
    
    mainPatch->outputProxyAtIndex(0)->connect(pan, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(pan, 1, 0);
    
    adsr->envelope->duration = 0.5 * FSEnvironment::sampleRate;
    adsr->envelope->attackLevel = 1;
    adsr->envelope->attackShape = 1.5;
    adsr->envelope->attackTimePercentage = 0.01;
    adsr->envelope->decayShape = 0.53;
    adsr->envelope->releaseShape = 0.53;
    adsr->envelope->decayLevel = 1;
    adsr->envelope->decayTimePercentage = 0.0;
    adsr->envelope->sustainTimePercentage = 0.0;
    
    return mainPatch;
}

int main(int argc, const char * argv[])
{
    FSUtils::seedRand();
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    FSPatch *patch1 = sinePatch();
    FSPatch *patch2 = sinePatch();
    FSPatch *patch3 = sinePatch();
    FSPatch *patch4 = sinePatch();
    FSPatch *patch5 = sinePatch();
    FSPatch *patch6 = sinePatch();
    FSPatch *patch7 = sinePatch();
    FSPatch *patch8 = sinePatch();
    FSScalerModule *scalerLeft = new FSScalerModule(0.2);
    FSScalerModule *scalerRight = new FSScalerModule(0.2);
    
    mainPatch->addModule(patch1);
    mainPatch->addModule(patch2);
    mainPatch->addModule(patch3);
    mainPatch->addModule(patch4);
    mainPatch->addModule(patch5);
    mainPatch->addModule(patch6);
    mainPatch->addModule(patch7);
    mainPatch->addModule(patch8);
    mainPatch->addModule(scalerLeft);
    mainPatch->addModule(scalerRight);
    
    scalerLeft->connect(patch1, 0, 0);
    scalerLeft->connect(patch2, 0, 0);
    scalerLeft->connect(patch3, 0, 0);
    scalerLeft->connect(patch4, 0, 0);
    scalerLeft->connect(patch5, 0, 0);
    scalerLeft->connect(patch6, 0, 0);
    scalerLeft->connect(patch7, 0, 0);
    scalerLeft->connect(patch8, 0, 0);
    
    scalerRight->connect(patch1, 1, 0);
    scalerRight->connect(patch2, 1, 0);
    scalerRight->connect(patch3, 1, 0);
    scalerRight->connect(patch4, 1, 0);
    scalerRight->connect(patch5, 1, 0);
    scalerRight->connect(patch6, 1, 0);
    scalerRight->connect(patch7, 1, 0);
    scalerRight->connect(patch8, 1, 0);
    
    mainPatch->outputProxyAtIndex(0)->connect(scalerLeft, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(scalerRight, 0, 0);
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 120);
    
    delete mainPatch;
    
    return 0;
}