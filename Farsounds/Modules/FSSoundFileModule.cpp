//
//  FSSoundFileModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/17/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSoundFileModule.h"
#include "FSUtils.h"

FSSoundFileModule::FSSoundFileModule(FSSoundFile *soundFile) : FSModule(1, soundFile->numChannels), _soundFile(soundFile) {}


void FSSoundFileModule::run()
{
    FSModule::run();
    
    FSModuleInput *posIn = _inputs[0];
    
    for (int i = 0; i < _numOutputs; i++) {
        _outputs[i].value = 0.0;
    }
    
    if (posIn != NULL && _soundFile->numFrames != 0) {
        double fpos1 = FSUtils::clip(posIn->getValue(), 0, 1);
        double fpos2 = fpos1 * (_soundFile->numFrames - 1);
        double *frames = _soundFile->frames;
        int numChannels = _soundFile->numChannels;
        sf_count_t pos1 = fpos2;
        sf_count_t pos2 = (pos1 < (_soundFile->numFrames - 1))? pos1 + 1 : pos1;
        double fraction = fpos2 - pos1;
        
        for (int i = 0; i < numChannels; i++) {
            _outputs[i].value = frames[pos1 * numChannels + i] * (1.0 - fraction) +
                                frames[pos2 * numChannels + i] * fraction;
        }
    }
}