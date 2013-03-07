//
//  main.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//


#include "FSEnvironment.h"
#include "FSUtils.h"
#include "FSPatch.h"
#include "FSTimedTriggerModule.h"
#include "FSMultiplierModule.h"
#include "FSAllpassModule.h"
#include "FSSequenceModule.h"
#include "FSPanningModule.h"
#include "FSRampModule.h"
#include "FSScalerModule.h"
#include "FSSpawnModule.h"
#include "FSDX7.h"
#include "FSBiquadFilterModule.h"
#include "FSSpawnFactory.h"
#include <FCMidi.h>
#include <iostream>


class FSMidiMan :public FSSpawnFactory {
    double _deltaTimeBaseInSeconds;
    FCMidiTrackEventItem *_eventItem;
    uint64_t _deltaTimeSamples;
    double _deltaTimeSamplesDiv;
    bool _firstProduce;
    
public:
    FSMidiMan(FCMidiFile *midiFile, int channel) : FSSpawnFactory()
    {
        FCMidiTrack *tracks = midiFile->tracks();
        FCMidiTrack *infoTrack = &tracks[0];
        FCMidiTrack *playTrack = &tracks[channel];
        
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
        _firstProduce = false;
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
        
        double durationInSeconds = deltaTimeTotal * _deltaTimeBaseInSeconds;
        double triggers[] = {durationInSeconds};
        
        FSPatch *patch = new FSPatch(0, 1);
        FSSquareModule *square = new FSSquareModule(FSUtils::mtof(event->param1()));
        FSADSREnvelopeModule *adsr = new FSADSREnvelopeModule();
        FSScalerModule *scaler = new FSScalerModule();
        FSTimedTriggerModule *trigger = new FSTimedTriggerModule(triggers, 1, 0, false);
        
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
                if (_eventItem->event->deltaTime() != 0) {
                    if (!_firstProduce) {
                        _firstProduce = true;
                        if (_eventItem->event->eventType() == FCMidiEventTypeChannel &&
                            ((FCMidiChannelEvent *)_eventItem->event)->channelEventType() == FCMidiChannelEventTypeNoteOn) {
                            spawn = this->generateSpawnWithEventItem(_eventItem);
                            _eventItem = _eventItem->next;
                        } else {
                            _eventItem = _eventItem->next;
                            spawn = this->produce();
                        }
                    } else {
                        double deltaTimeSamplesReal = _deltaTimeBaseInSeconds * _eventItem->event->deltaTime() * FSEnvironment::sampleRate;
                        _deltaTimeSamples = deltaTimeSamplesReal;
                        _deltaTimeSamplesDiv += deltaTimeSamplesReal - _deltaTimeSamples;
                        int deltaTimeSamplesAdd = (int)_deltaTimeSamplesDiv;
                        _deltaTimeSamples += deltaTimeSamplesAdd;
                        _deltaTimeSamplesDiv -= deltaTimeSamplesAdd;
                    }
                } else {
                    if (_eventItem->event->eventType() == FCMidiEventTypeChannel &&
                        ((FCMidiChannelEvent *)_eventItem->event)->channelEventType() == FCMidiChannelEventTypeNoteOn) {
                        spawn = this->generateSpawnWithEventItem(_eventItem);
                        _eventItem = _eventItem->next;
                    } else {
                        _eventItem = _eventItem->next;
                        spawn = this->produce();
                    }
                }
            }
        }
        
        return spawn;
    }
    
    void endProductionCycle()
    {
        _deltaTimeSamples--;
    }
};


int main(int argc, const char * argv[])
{
    FSUtils::seedRand();
    
    FCMidiFile *midiFile;
    FCMidiErrorType error = FCMidiErrorTypeNone;
    midiFile = new FCMidiFile();
    midiFile->read("/Users/almerlucke/Documents/MidiFiles/take5.mid", &error);
    
    FSPatch *mainPatch = new FSPatch(0, 1);
    FSScalerModule *scaler = new FSScalerModule(0.2);

    mainPatch->addModule(scaler);
    
    for (int i = 0; i < midiFile->numTracks(); i++) {
        FSMidiMan *midiMan = new FSMidiMan(midiFile, i);
        FSSpawnModule *spawnModule = new FSSpawnModule(midiMan);
        mainPatch->addModule(spawnModule);
        scaler->connect(spawnModule, 0, 0);
    }
    
    mainPatch->outputProxyAtIndex(0)->connect(scaler, 0, 0);
    
    FSUtils::generateSoundFile("test.wav", mainPatch, 60);
    
    delete midiFile;
    delete mainPatch;
    
    return 0;
}