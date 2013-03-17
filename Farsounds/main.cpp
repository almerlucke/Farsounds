//
//  main.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include <iostream>
#include <FCMidi.h>
#include <stdint.h>

#include "midiread_example.h"
//
//class FSMidiTrackReader
//{
//    FCMidiTrack *_track;
//    bool *_playCurrentEvent;
//    FCMidiTrackEventItem *_currentEvent;
//    uint64_t _sampsTillNextEvent;
//    double _deltaTimeBaseInSeconds;
//    double _deltaTimeSamplesDiv;
//    
//public:
//    
//    FSMidiTrackReader(FCMidiFile *midiFile, int trackIndex) {
//        FCMidiTrack *tracks = midiFile->tracks();
//        FCMidiTrack *infoTrack = &tracks[0];
//        
//        _track = &tracks[trackIndex];
//        _playCurrentEvent = false;
//        _currentEvent = _track->events();
//        
//        if (midiFile->hasTicksPerBeat()) {
//            uint32_t ticksPerBeat = midiFile->ticksPerBeat();
//            uint32_t microSecondsPerQuarterNote = infoTrack->tempoMPQN();
//            _deltaTimeBaseInSeconds = (microSecondsPerQuarterNote / (double)ticksPerBeat) / 1000000.0;
//        }
//        
//        _deltaTimeSamplesDiv = 0.0;
//        _sampsTillNextEvent = 0;
//    }
//    
//    void next() {
//        FCMidiEvent *event = NULL;
//        
//        if (_currentEvent != NULL) {
//            if (_sampsTillNextEvent == 0) {
//                if (_playCurrentEvent > 0) {
//                    
//                }
//            }
//        }
//        
//        return event;
//    }
//};


int main(int argc, const char * argv[])
{
    midiread_example();
    return 0;
}