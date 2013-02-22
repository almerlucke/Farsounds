//
//  spawnfactory_example2.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "spawnfactory_example2.h"

#include "FSEnvironment.h"
#include "FSUtils.h"
#include "FSPatch.h"
#include "FSSpawnFactory.h"
#include "FSSpawnModule.h"

#include "FSSineModule.h"
#include "FSADSREnvelopeModule.h"
#include "FSScalerModule.h"
#include "FSPanningModule.h"
#include "FSTimedTriggerModule.h"
#include "FSOneShotTriggerModule.h"
#include "FSMultiplierModule.h"
#include "FSAllpassModule.h"

class FSSineTrainFactory : public FSSpawnFactory
{
    double _freq;
    double _freqStep;
    double _dur;
    double _durStep;
    double _pan;
    double _panStep;
    double _amp;
    double _ampStep;
    double _trigDur;
    double _trigDurStep;
    uint64_t _nextSpawn;
    bool _spawnedOnce;
    
public:
    
    FSSineTrainFactory(double freqStart, double freqEnd,
                       double durStart, double durEnd,
                       double panStart, double panEnd,
                       double ampStart, double ampEnd,
                       double trigDurStart, double trigDurEnd,
                       double duration) : FSSpawnFactory()
    {
        uint64_t numFrames = duration * FSEnvironment::sampleRate;
        
        if (numFrames < 2) numFrames = 2;
        
        _nextSpawn = 0;
        _spawnedOnce = false;
        
        _freq = freqStart;
        _freqStep = (freqEnd - freqStart) / (numFrames - 1);
        
        _dur = durStart;
        _durStep = (durEnd - durStart) / (numFrames - 1);
        
        _pan = panStart;
        _panStep = (panEnd - panStart) / (numFrames - 1);
        
        _amp = ampStart;
        _ampStep = (ampEnd - ampStart) / (numFrames - 1);
        
        _trigDur = trigDurStart;
        _trigDurStep = (trigDurEnd - trigDurStart) / (numFrames - 1);
    }
    
    int numOutputsPerSpawn() { return 2; }
    
    void startProductionCycle()
    {
        _spawnedOnce = false;
    }
    
    FSSpawn *produce()
    {
        if (_nextSpawn == 0 && !_spawnedOnce) {
            _spawnedOnce = true;
            double durationInSeconds = _dur;
            
            FSPatch *patch = new FSPatch(0, 2);
            FSSineModule *sine = new FSSineModule(_freq);
            FSADSREnvelopeModule *adsr = new FSADSREnvelopeModule();
            FSMultiplierModule *mult = new FSMultiplierModule(2);
            FSOneShotTriggerModule *trigger = new FSOneShotTriggerModule();
            FSPanningModule *panning = new FSPanningModule(_pan);
            
            patch->addModule(sine);
            patch->addModule(adsr);
            patch->addModule(mult);
            patch->addModule(trigger);
            patch->addModule(panning);
            
            adsr->connect(trigger, 0, 0);
            mult->connect(sine, 0, 0);
            mult->connect(adsr, 0, 1);
            panning->connect(mult, 0, 0);
            
            patch->outputProxyAtIndex(0)->connect(panning, 0, 0);
            patch->outputProxyAtIndex(1)->connect(panning, 1, 0);
            
            adsr->envelope->attackLevel = _amp;
            adsr->envelope->decayLevel = _amp * 0.3;
            adsr->envelope->attackTimePercentage = 0.1;
            adsr->envelope->decayTimePercentage = 0.1;
            adsr->envelope->sustainTimePercentage = 0.7;
            adsr->envelope->duration = FSEnvironment::sampleRate * durationInSeconds;
            
            return new FSSpawn(FSEnvironment::sampleRate * durationInSeconds, patch);
        }
        
        return NULL;
    }
    
    void endProductionCycle()
    {
        if (_nextSpawn == 0) {
            _nextSpawn = FSEnvironment::sampleRate * _trigDur;
        }
        
        _freq += _freqStep;
        _dur += _durStep;
        _pan += _panStep;
        _amp += _ampStep;
        _trigDur += _trigDurStep;
        
        --_nextSpawn;
    }
};


class FSSineRampFactory : public FSSpawnFactory {
private:
    uint64_t _nextSpawn;
    bool _spawnedOnce;
    
public:
    
    FSSineRampFactory() : FSSpawnFactory()
    {
        _nextSpawn = 0;
    }
    
    int numOutputsPerSpawn() { return 2; }
    
    void startProductionCycle()
    {
        _spawnedOnce = false;
    }
    
    FSSpawn *produce()
    {
        if (_nextSpawn == 0 && !_spawnedOnce) {
            _spawnedOnce = true;
            
            double durationInSeconds = FSUtils::randRange(0.5, 5.0);
            
            FSPatch *patch = new FSPatch(0, 2);
            FSSineTrainFactory *trainFactory = new FSSineTrainFactory(FSUtils::randRange(30, 2000), FSUtils::randRange(30, 2000),
                                                                      FSUtils::randRange(0.001, 1.0), FSUtils::randRange(0.001, 1.0),
                                                                      FSUtils::randRange(-1, 1), FSUtils::randRange(-1, 1),
                                                                      FSUtils::randRange(0.1, 0.8), FSUtils::randRange(0.1, 0.8),
                                                                      FSUtils::randRange(0.01, 2.3), FSUtils::randRange(0.01, 2.3),
                                                                      durationInSeconds);
            FSSpawnModule *trainModule = new FSSpawnModule(trainFactory);
            FSADSREnvelopeModule *adsr = new FSADSREnvelopeModule();
            FSMultiplierModule *mult1 = new FSMultiplierModule(2);
            FSMultiplierModule *mult2 = new FSMultiplierModule(2);
            FSOneShotTriggerModule *trigger = new FSOneShotTriggerModule();
            
            patch->addModule(trainModule);
            patch->addModule(adsr);
            patch->addModule(mult1);
            patch->addModule(mult2);
            patch->addModule(trigger);
            
            adsr->connect(trigger, 0, 0);
            mult1->connect(trainModule, 0, 0);
            mult1->connect(adsr, 0, 1);
            mult2->connect(trainModule, 1, 0);
            mult2->connect(adsr, 0, 1);
            
            patch->outputProxyAtIndex(0)->connect(mult1, 0, 0);
            patch->outputProxyAtIndex(1)->connect(mult2, 0, 0);
            
            adsr->envelope->attackLevel = FSUtils::randRange(0.8, 1.0);
            adsr->envelope->decayLevel = adsr->envelope->attackLevel;
            adsr->envelope->attackTimePercentage = 0.01;
            adsr->envelope->decayTimePercentage = 0.01;
            adsr->envelope->sustainTimePercentage = 0.96;
            adsr->envelope->duration = FSEnvironment::sampleRate * durationInSeconds;
            
            return new FSSpawn(FSEnvironment::sampleRate * durationInSeconds, patch);
        }
        
        return NULL;
    }
    
    void endProductionCycle()
    {
        if (_nextSpawn == 0) {
            _nextSpawn = FSEnvironment::sampleRate * FSUtils::randRange(0.1, 2.0);
        }
        
        --_nextSpawn;
    }
};


void spawnfactory_example2()
{
    FSUtils::seedRand();
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    FSSineRampFactory *factory = new FSSineRampFactory();
    FSSpawnModule *spawnModule = new FSSpawnModule(factory);
    FSAllpassModule *leftAllpass = new FSAllpassModule(0.4 * FSEnvironment::sampleRate, 0.3);
    FSAllpassModule *rightAllpass = new FSAllpassModule(0.402 * FSEnvironment::sampleRate, 0.3);
    FSScalerModule *leftScaler = new FSScalerModule(0.3);
    FSScalerModule *rightScaler = new FSScalerModule(0.3);
    
    mainPatch->addModule(spawnModule);
    mainPatch->addModule(leftAllpass);
    mainPatch->addModule(rightAllpass);
    mainPatch->addModule(leftScaler);
    mainPatch->addModule(rightScaler);
    
    leftAllpass->connect(spawnModule, 0, 0);
    rightAllpass->connect(spawnModule, 1, 0);
    leftScaler->connect(leftAllpass, 0, 0);
    rightScaler->connect(rightAllpass, 0, 0);
    
    mainPatch->outputProxyAtIndex(0)->connect(leftScaler, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(rightScaler, 0, 0);
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 180);
    
    delete mainPatch;
}