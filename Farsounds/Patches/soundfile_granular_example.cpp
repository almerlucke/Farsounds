//
//  soundfile_granular_example.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/23/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "soundfile_granular_example.h"


#include <iostream>
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
#include "FSTriangleModule.h"
#include "FSSquareModule.h"
#include "FSRampModule.h"
#include "FSTableModule.h"

#include "FSSoundFile.h"
#include "FSSoundFileModule.h"


class FSGranularFactory :public FSSpawnFactory {
private:
    uint64_t _nextSpawn;
    bool _spawnedOnce;
    FSSoundFile *_soundFile;
    double _window[1024];
    double _posInFile;
    double _posStep;
    double _normalSpeed;
    
public:
    
    FSGranularFactory() : FSSpawnFactory()
    {
        _nextSpawn = 0;
        _soundFile = new FSSoundFile("/Users/aFrogleap/Desktop/string.wav");
        FSUtils::hanningWindow(_window, 1024);
        _posInFile = 0.0;
        _normalSpeed = 1.0 / (_soundFile->numFrames / _soundFile->sampleRate);
        _posStep = 1.0 / (FSEnvironment::sampleRate * 120);
    }
    
    ~FSGranularFactory()
    {
        delete _soundFile;
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
            
            double durationInSeconds = FSUtils::randRange(0.05, 0.5);
            
            FSPatch *patch = new FSPatch(0, 2);
            FSPhasorModule *phasor = new FSPhasorModule(FSUtils::randRange(_normalSpeed * 0.5, _normalSpeed * 0.55), _posInFile);
            FSRampModule *windowRamp = new FSRampModule(0, 1, durationInSeconds);
            FSTableModule *tableModule = new FSTableModule(_window, 1024);
            FSOneShotTriggerModule *trigger = new FSOneShotTriggerModule();
            FSMultiplierModule *multLeft = new FSMultiplierModule(2);
            FSMultiplierModule *multRight = new FSMultiplierModule(2);
            FSSoundFileModule *sfmod = new FSSoundFileModule(_soundFile);
            
            patch->addModule(phasor);
            patch->addModule(windowRamp);
            patch->addModule(tableModule);
            patch->addModule(trigger);
            patch->addModule(multLeft);
            patch->addModule(multRight);
            patch->addModule(sfmod);
            
            windowRamp->connect(trigger, 0, 0);
            tableModule->connect(windowRamp, 0, 0);
            sfmod->connect(phasor, 0, 0);
            multLeft->connect(sfmod, 0, 0);
            multLeft->connect(tableModule, 0, 1);
            multRight->connect(sfmod, 1, 0);
            multRight->connect(tableModule, 0, 1);
            
            patch->outputProxyAtIndex(0)->connect(multLeft, 0, 0);
            patch->outputProxyAtIndex(1)->connect(multRight, 0, 0);
            
            return new FSSpawn(FSEnvironment::sampleRate * durationInSeconds, patch);
        }
        
        return NULL;
    }
    
    void endProductionCycle()
    {
        _posInFile += _posStep;
        if (_posInFile >= 1.0) {
            _posInFile -= 1.0;
        }
        
        if (_nextSpawn == 0) {
            _nextSpawn = FSEnvironment::sampleRate * FSUtils::randRange(0.001, 0.01);
        }
        
        --_nextSpawn;
    }
};


void soundfile_granular_example()
{
    FSUtils::seedRand();
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    FSGranularFactory *grainFactory = new FSGranularFactory();
    FSSpawnModule *spawnModule = new FSSpawnModule(grainFactory);
    FSMultiplierModule *leftMult = new FSMultiplierModule(0.2);
    FSMultiplierModule *rightMult = new FSMultiplierModule(0.2);
    
    mainPatch->addModule(spawnModule);
    mainPatch->addModule(leftMult);
    mainPatch->addModule(rightMult);
    
    leftMult->connect(spawnModule, 0, 0);
    rightMult->connect(spawnModule, 1, 0);
    
    mainPatch->outputProxyAtIndex(0)->connect(leftMult, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(rightMult, 0, 0);
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 120);
    
    delete mainPatch;
}