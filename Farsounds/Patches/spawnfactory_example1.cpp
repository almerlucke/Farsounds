//
//  spawnfactory_example1.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/20/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "spawnfactory_example1.h"

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

#include <cstddef>


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
            
            double durationInSeconds = FSUtils::randRange(0.5, 10.0);
            double triggers[] = {durationInSeconds};
            
            FSPatch *patch = new FSPatch(0, 2);
            FSSineModule *sine = new FSSineModule(FSUtils::randRange(100, 3000));
            FSADSREnvelopeModule *adsr = new FSADSREnvelopeModule();
            FSScalerModule *scaler = new FSScalerModule();
            FSTimedTriggerModule *trigger = new FSTimedTriggerModule(triggers, 1, 0, false);
            FSPanningModule *panning = new FSPanningModule(FSUtils::randRange(-1, 1));
            
            patch->addModule(sine);
            patch->addModule(adsr);
            patch->addModule(scaler);
            patch->addModule(trigger);
            patch->addModule(panning);
            
            adsr->connect(trigger, 0, 0);
            scaler->connect(sine, 0, 0);
            scaler->connect(adsr, 0, 1);
            panning->connect(scaler, 0, 0);
            
            patch->outputProxyAtIndex(0)->connect(panning, 0, 0);
            patch->outputProxyAtIndex(1)->connect(panning, 1, 0);
            
            adsr->envelope->attackLevel = FSUtils::randRange(0.5, 1.0);
            adsr->envelope->decayLevel = FSUtils::randRange(0.1, 0.3);
            adsr->envelope->attackTimePercentage = 0.1;
            adsr->envelope->decayTimePercentage = 0.1;
            adsr->envelope->sustainTimePercentage = 0.7;
            adsr->envelope->duration = FSEnvironment::sampleRate * durationInSeconds;
            
            FSSpawn *spawn = new FSSpawn();
            
            spawn->duration = FSEnvironment::sampleRate * durationInSeconds;
            spawn->module = patch;
            
            return spawn;
        }
        
        return NULL;
    }
    
    void endProductionCycle()
    {
        if (_nextSpawn == 0) {
            _nextSpawn = FSEnvironment::sampleRate * FSUtils::randRange(0.125, 2.0);
        }
        
        --_nextSpawn;
    }
};


void spawn_factory_example(void)
{
    FSPatch *mainPatch = new FSPatch(0, 2);
    FSSineRampFactory *factory = new FSSineRampFactory();
    FSSpawnModule *spawnModule = new FSSpawnModule(factory);
    FSScalerModule *leftScaler = new FSScalerModule(0.1);
    FSScalerModule *rightScaler = new FSScalerModule(0.1);
    
    mainPatch->addModule(spawnModule);
    mainPatch->addModule(leftScaler);
    mainPatch->addModule(rightScaler);
    
    leftScaler->connect(spawnModule, 0, 0);
    rightScaler->connect(spawnModule, 1, 0);
    
    mainPatch->outputProxyAtIndex(0)->connect(leftScaler, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(rightScaler, 0, 0);
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 40);
    
    delete mainPatch;
}