//
//  midiread_example.cpp
//  Farsounds
//
//  Created by Almer Lucke on 3/11/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "midiread_example.h"

#include "FSEnvironment.h"
#include "FSUtils.h"
#include "FSPatch.h"
#include "FSTimedTriggerModule.h"
#include "FSOneShotTriggerModule.h"
#include "FSMultiplierModule.h"
#include "FSAllpassModule.h"
#include "FSSequenceModule.h"
#include "FSPanningModule.h"
#include "FSRampModule.h"
#include "FSScalerModule.h"
#include "FSSpawnModule.h"
#include "FSDCSineModule.h"
#include "FSDX7.h"
#include "FSMoogFilterModule.h"
#include "FSBiquadFilterModule.h"
#include "FSSpawnFactory.h"
#include <FCMidi.h>


class FSMidiMan :public FSSpawnFactory {
    double _deltaTimeBaseInSeconds;
    FCMidiTrackEventItem *_eventItem;
    FCMidiTrack *_playTrack;
    uint64_t _deltaTimeSamples;
    double _deltaTimeSamplesDiv;
    bool _firstProduce;
    
public:
    FSMidiMan(FCMidiFile *midiFile, int channel) : FSSpawnFactory()
    {
        FCMidiTrack *tracks = midiFile->tracks();
        FCMidiTrack *infoTrack = &tracks[0];
        FCMidiTrack *playTrack = &tracks[channel];
        
        _playTrack = playTrack;
        _eventItem = playTrack->events();
        
        if (midiFile->hasTicksPerBeat()) {
            uint32_t ticksPerBeat = midiFile->ticksPerBeat();
            uint32_t microSecondsPerQuarterNote = infoTrack->tempoMPQN();
            _deltaTimeBaseInSeconds = (microSecondsPerQuarterNote / (double)ticksPerBeat) / 1000000.0;
        }
        
        double _deltaTimeSampleReal = playTrack->SMPTEOffset() * FSEnvironment::sampleRate;
        
        if (_eventItem != NULL) {
            if (_eventItem->event->deltaTime() > 0) {
                _deltaTimeSampleReal += _deltaTimeBaseInSeconds * _eventItem->event->deltaTime() * FSEnvironment::sampleRate;
            }
        }
        
        _deltaTimeSamples = _deltaTimeSampleReal;
        _deltaTimeSamplesDiv = _deltaTimeSampleReal - _deltaTimeSamples;
    }
    
    ~FSMidiMan()
    {
        
    }
    
    int numOutputsPerSpawn() { return 1; }
    
    void startProductionCycle()
    {
    }
    
    FSSpawn *generateSpawnWithEventItem(FCMidiTrackEventItem *eventItem)
    {
        FCMidiChannelEvent *event = (FCMidiChannelEvent *)eventItem->event;
        
        uint32_t deltaTimeTotal = 0;
        bool noteOffFound = false;
        FCMidiTrackEventItem *item = eventItem->next;
        while (item != NULL) {
            deltaTimeTotal += item->event->deltaTime();
            if (item->event->eventType() == FCMidiEventTypeChannel) {
                FCMidiChannelEvent *noteOffEvent = (FCMidiChannelEvent *)item->event;
                if (noteOffEvent->channelEventType() == FCMidiChannelEventTypeNoteOff &&
                    noteOffEvent->channel() == event->channel() &&
                    noteOffEvent->param1() == event->param1()) {
                    noteOffFound = true;
                    break;
                }
            }
            item = item->next;
        }
        
        if (!noteOffFound) {
            deltaTimeTotal = 0;
            printf("no matching note off found");
            fflush(stdout);
        }
        
        double durationInSeconds = deltaTimeTotal * _deltaTimeBaseInSeconds * 1.2;
        
        FSPatch *patch = new FSPatch(0, 1);
        FSSquareModule *square = new FSSquareModule(FSUtils::mtof(event->param1()));
        FSADSREnvelopeModule *adsr = new FSADSREnvelopeModule();
        FSScalerModule *scaler = new FSScalerModule();
        FSOneShotTriggerModule *trigger = new FSOneShotTriggerModule();
        
        patch->addModule(square);
        patch->addModule(adsr);
        patch->addModule(scaler);
        patch->addModule(trigger);
        
        adsr->connect(trigger, 0, 0);
        scaler->connect(square, 0, 0);
        scaler->connect(adsr, 0, 1);
        
        patch->outputProxyAtIndex(0)->connect(scaler, 0, 0);
        
        adsr->envelope->attackLevel = event->param2() / 127.0;
        adsr->envelope->decayLevel = 0.2;
        adsr->envelope->attackTimePercentage = 0.000001;
        adsr->envelope->decayTimePercentage = 0.000001;
        adsr->envelope->sustainTimePercentage = 0.1;
        adsr->envelope->duration = FSEnvironment::sampleRate * durationInSeconds;
        
        FSSpawn *spawn = new FSSpawn();
        
        spawn->duration = FSEnvironment::sampleRate * durationInSeconds;
        spawn->module = patch;
        
        return spawn;
    }
    
    FSSpawn *produce()
    {
        FSSpawn *spawn = NULL;
        
        if (_eventItem != NULL) {
            
            if (_deltaTimeSamples == 0) {
                if (_eventItem->event->eventType() == FCMidiEventTypeChannel &&
                    ((FCMidiChannelEvent *)_eventItem->event)->channelEventType() == FCMidiChannelEventTypeNoteOn) {
                    spawn = this->generateSpawnWithEventItem(_eventItem);
                }
                
                _eventItem = _eventItem->next;
                
                while (_eventItem != NULL) {
                    uint32_t deltaTime = _eventItem->event->deltaTime();
                    
                    if (deltaTime != 0) {
                        double deltaTimeSamplesReal = _deltaTimeBaseInSeconds * deltaTime * FSEnvironment::sampleRate;
                        _deltaTimeSamples = deltaTimeSamplesReal;
                        _deltaTimeSamplesDiv += deltaTimeSamplesReal - _deltaTimeSamples;
                        int deltaTimeSamplesAdd = (int)_deltaTimeSamplesDiv;
                        _deltaTimeSamples += deltaTimeSamplesAdd;
                        _deltaTimeSamplesDiv -= deltaTimeSamplesAdd;
                        break;
                    } else if (_eventItem->event->eventType() == FCMidiEventTypeChannel &&
                               ((FCMidiChannelEvent *)_eventItem->event)->channelEventType() == FCMidiChannelEventTypeNoteOn) {
                        if (spawn == NULL) {
                            spawn = this->generateSpawnWithEventItem(_eventItem);
                            _eventItem = _eventItem->next;
                            if (_eventItem != NULL && _eventItem->event->deltaTime() > 0) {
                                deltaTime = _eventItem->event->deltaTime();
                                double deltaTimeSamplesReal = _deltaTimeBaseInSeconds * deltaTime * FSEnvironment::sampleRate;
                                _deltaTimeSamples = deltaTimeSamplesReal;
                                _deltaTimeSamplesDiv += deltaTimeSamplesReal - _deltaTimeSamples;
                                int deltaTimeSamplesAdd = (int)_deltaTimeSamplesDiv;
                                _deltaTimeSamples += deltaTimeSamplesAdd;
                                _deltaTimeSamplesDiv -= deltaTimeSamplesAdd;
                            }
                        }
                        break;
                    }
                    
                    _eventItem = _eventItem->next;
                }
            }
        }
        
        return spawn;
    }
    
    void endProductionCycle()
    {
        if (_eventItem != NULL && _deltaTimeSamples > 0) {
            _deltaTimeSamples--;
        } 
    }
};


void midiread_example()
{
    FSUtils::seedRand();
    
    FCMidiFile *midiFile;
    FCMidiErrorType error = FCMidiErrorTypeNone;
    midiFile = new FCMidiFile();
    midiFile->read("/Users/almerlucke/Documents/MidiFiles/MSX/GALIOUS.mid", &error);
    
    FCMidiTrack *track = &midiFile->tracks()[0];
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    FSScalerModule *scaler = new FSScalerModule(0.2);
    
    uint32_t microSecondsPerQuarterNote = track->tempoMPQN();
    double secondsPerQuarterNote = microSecondsPerQuarterNote / 1000000.0;
    
    FSAllpassModule *allpass1 = new FSAllpassModule(FSEnvironment::sampleRate * secondsPerQuarterNote * 0.375, 0.5);
    FSAllpassModule *allpass2 = new FSAllpassModule(FSEnvironment::sampleRate * secondsPerQuarterNote * 0.875, 0.6);
    FSMultiplierModule *allpassMult1 = new FSMultiplierModule(0.3);
    FSMultiplierModule *allpassMult2 = new FSMultiplierModule(0.3);
    
    mainPatch->addModule(scaler);
    mainPatch->addModule(allpass1);
    mainPatch->addModule(allpass2);
    mainPatch->addModule(allpassMult1);
    mainPatch->addModule(allpassMult2);
    
    allpass1->connect(scaler, 0, 0);
    allpass2->connect(scaler, 0, 0);
    allpassMult1->connect(allpass1, 0, 0);
    allpassMult2->connect(allpass2, 0, 0);
    
    for (int i = 0; i < midiFile->numTracks(); i++) {
        FSMidiMan *midiMan = new FSMidiMan(midiFile, i);
        FSSpawnModule *spawnModule = new FSSpawnModule(midiMan);
        mainPatch->addModule(spawnModule);
        scaler->connect(spawnModule, 0, 0);
    }
    
    mainPatch->outputProxyAtIndex(0)->connect(allpassMult1, 0, 0);
    mainPatch->outputProxyAtIndex(0)->connect(scaler, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(allpassMult2, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(scaler, 0, 0);
    
    FSUtils::generateSoundFile("test.wav", mainPatch, 180);
    
    delete midiFile;
    delete mainPatch;
}