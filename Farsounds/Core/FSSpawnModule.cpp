//
//  FSSpawnModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/20/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSpawnModule.h"
#include "FSSpawnFactory.h"
#include <cstddef>
#include <cstdio>

#pragma mark - Add/Remove Voice

void FSSpawnModule::addVoice(FSSpawn *spawn)
{
    FSSpawnVoice *voice = new FSSpawnVoice(spawn);
    
    if (_voiceList != NULL) {
        _voiceList->prev = voice;
    }
    voice->prev = NULL;
    voice->next = _voiceList;
    _voiceList = voice;
}

void FSSpawnModule::removeVoice(FSSpawnModule::FSSpawnVoice *voice)
{
    if (voice->prev != NULL) {
        voice->prev->next = voice->next;
    } else {
        _voiceList = voice->next;
    }
    
    if (voice->next != NULL) {
        voice->next->prev = voice->prev;
    }
    
    delete voice;
}


#pragma mark - Init/Delete SpawnModule

FSSpawnModule::FSSpawnModule(FSSpawnFactory *factory) : FSModule(0, factory->numOutputsPerSpawn()), _factory(factory), _voiceList(NULL) {}

FSSpawnModule::~FSSpawnModule()
{
    delete _factory;
    
    FSSpawnVoice *voice = _voiceList;
    while (voice != NULL) {
        FSSpawnVoice *tmpVoice = voice;
        voice = voice->next;
        delete tmpVoice;
    }
}


#pragma mark - Run Module

void FSSpawnModule::run()
{
    FSModule::run();
    
    // start factory production for one cycle
    _factory->startProductionCycle();
    
    // produce spawn until no more spawn can be produced for this cycle
    FSSpawn *spawn = _factory->produce();
    while (spawn != NULL) {
        this->addVoice(spawn);
        spawn = _factory->produce();
    }
    
    // end factory production for one cycle
    _factory->endProductionCycle();
    
    // zero out all output values
    for (int i = 0; i < _numOutputs; i++) {
        _outputs[i].value = 0.0;
    }
    
    // loop through all voices to combine their outputs
    FSSpawnVoice *voice = _voiceList;
    while (voice != NULL) {
        FSSpawnVoice *tmpVoice = voice;
        voice = voice->next;
        if (tmpVoice->spawn->duration > 0) {
            FSModule *spawnModule = tmpVoice->spawn->module;
            spawnModule->resetHasRun();
            spawnModule->run();
            for (int i = 0; i < _numOutputs; i++) {
                _outputs[i].value += spawnModule->outputAtIndex(i)->value;
            }
            tmpVoice->spawn->duration--;
        } else {
            // spawn's duration is over, remove spawn voice from voice list
            this->removeVoice(tmpVoice);
        }
    }
}