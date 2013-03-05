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
#include "FSDX7.h"
#include "FSBiquadFilterModule.h"

#include <FCMidi.h>

#include <iostream>


int main(int argc, const char * argv[])
{
    /*
    FSUtils::seedRand();
    
    double times[12] = {0.2, 0.2, 0.4, 0.2, 0.2, 0.2, 0.4, 0.2, 0.1, 0.1, 0.1, 0.1};
    double frequencies[5] = {
        FSUtils::mtof(36), FSUtils::mtof(108), FSUtils::mtof(96), FSUtils::mtof(84), FSUtils::mtof(60)};
    double amps[5] = {0.5, 0.6, 0.6, 0.5, 0.5};
    
    FSPatch *mainPatch = new FSPatch(0, 2);
    
    FSTimedTriggerModule *trigger = new FSTimedTriggerModule(times, 12, 0, true);
    FSSequenceModule *sequencer = new FSSequenceModule(frequencies, 5);
    FSSequenceModule *ampSequencer = new FSSequenceModule(amps, 5);
    FSRampModule *ramp = new FSRampModule(100, 100, 0.001, 1.6);
    FSMultiplierModule *amp = new FSMultiplierModule(2);
    FSAllpassModule *allpass = new FSAllpassModule(FSEnvironment::sampleRate * 0.3, 0.2);
    FSPanningModule *pan = new FSPanningModule(0);
    
    FSDX7 *dx7 = new FSDX7(tubularBells(), FSDX7_ALGORITHM5, amp, 0, mainPatch);
    dx7->connectTrigger(trigger, 0);
    dx7->connectDuration(trigger, 1);
    dx7->connectPitch(ramp, 0);
    
    FSDX7 *dx7_2 = new FSDX7(tubularBells2(), FSDX7_ALGORITHM5, amp, 0, mainPatch);
    dx7_2->connectTrigger(trigger, 0);
    dx7_2->connectDuration(trigger, 1);
    dx7_2->connectPitch(ramp, 0);
    
    sequencer->connect(trigger, 0, 0);
    ramp->connect(trigger, 0, 0);
    ramp->connect(sequencer, 0, 2);
    ampSequencer->connect(trigger, 0, 0);
    amp->connect(ampSequencer, 0, 1);
    allpass->connect(amp, 0, 0);
    pan->connect(allpass, 0, 0);
    
    mainPatch->addModule(amp);
    mainPatch->addModule(pan);
    mainPatch->addModule(ramp);
    mainPatch->addModule(trigger);
    mainPatch->addModule(allpass);
    mainPatch->addModule(sequencer);
    mainPatch->addModule(ampSequencer);
    
    mainPatch->outputProxyAtIndex(0)->connect(pan, 0, 0);
    mainPatch->outputProxyAtIndex(1)->connect(pan, 1, 0);
    
    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 20);
    
    delete dx7;
    delete mainPatch;
    */
    
    FSUtils::seedRand();
    
    double times[1] = {1.0};
    
    FSPatch *mainPatch = new FSPatch(0, 1);
    
    double bw = 0.001;
    
    FSTimedTriggerModule *trigger = new FSTimedTriggerModule(times, 1, 0, true);
    FSBiquadFilterModule *biquad1 = new FSBiquadFilterModule(FSBiquadFilterTypeBPF, 0, 1200, bw);
    FSMultiplierModule *mult1 = new FSMultiplierModule(2.0 / bw);
    FSBiquadFilterModule *biquad2 = new FSBiquadFilterModule(FSBiquadFilterTypeBPF, 0, 720, bw);
    FSMultiplierModule *mult2 = new FSMultiplierModule(2.0 / bw);
    FSBiquadFilterModule *biquad3 = new FSBiquadFilterModule(FSBiquadFilterTypeBPF, 0, 400, bw);
    FSMultiplierModule *mult3 = new FSMultiplierModule(2.0 / bw);
    FSBiquadFilterModule *biquad4 = new FSBiquadFilterModule(FSBiquadFilterTypeBPF, 0, 240, bw);
    FSMultiplierModule *mult4 = new FSMultiplierModule(2.0 / bw);
    
    mult1->connect(biquad1, 0, 0);
    biquad1->connect(trigger, 0, 0);
    mainPatch->outputProxyAtIndex(0)->connect(mult1, 0, 0);
    mult2->connect(biquad2, 0, 0);
    biquad2->connect(trigger, 0, 0);
    mainPatch->outputProxyAtIndex(0)->connect(mult2, 0, 0);
    mult3->connect(biquad3, 0, 0);
    biquad3->connect(trigger, 0, 0);
    mainPatch->outputProxyAtIndex(0)->connect(mult3, 0, 0);
    mult4->connect(biquad4, 0, 0);
    biquad4->connect(trigger, 0, 0);
    mainPatch->outputProxyAtIndex(0)->connect(mult4, 0, 0);
    
    mainPatch->addModule(trigger);
    mainPatch->addModule(biquad1);
    mainPatch->addModule(mult1);
    mainPatch->addModule(biquad2);
    mainPatch->addModule(mult2);
    mainPatch->addModule(biquad3);
    mainPatch->addModule(mult3);
    mainPatch->addModule(biquad4);
    mainPatch->addModule(mult4);
    
    FSUtils::generateSoundFile("test.wav", mainPatch, 10);
    
    delete mainPatch;
    
    
    FCMidiFile *midiFile = new FCMidiFile();
    FCMidiErrorType error = FCMidiErrorTypeNone;
    
    if (midiFile->read("/Users/almerlucke/Desktop/teddybear.mid", &error)) {
        FCMidiTrack *tracks = midiFile->tracks();
        
        for (int i = 0; i < midiFile->numTracks(); i++) {
            FCMidiTrack *track = &tracks[i];
            FCMidiTrackEventItem *eventItem = track->events();
            
            while (eventItem != NULL) {
                printf("deltaTime %d - ", eventItem->event->deltaTime());
                eventItem->event->printEvent();
                eventItem = eventItem->next;
            }
        }
    }
    
    delete midiFile;
    
    
    return 0;
}