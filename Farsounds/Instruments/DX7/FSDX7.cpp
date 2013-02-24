//
//  FSDX7.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/23/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSDX7.h"

FSDX7::FSDX7(FSDX7Settings settings, FSPatch *patch)
{
    _settings = settings;
    
    _operators[0] = op1 = new FSDX7Operator(settings.operatorSettings[0], patch);
    _operators[1] = op2 = new FSDX7Operator(settings.operatorSettings[1], patch);
    _operators[2] = op3 = new FSDX7Operator(settings.operatorSettings[2], patch);
    _operators[3] = op4 = new FSDX7Operator(settings.operatorSettings[3], patch);
    _operators[4] = op5 = new FSDX7Operator(settings.operatorSettings[4], patch);
    _operators[5] = op6 = new FSDX7Operator(settings.operatorSettings[5], patch);
}

FSDX7::~FSDX7()
{
    for (int i = 0; i < 6; i++) delete _operators[i];
}

void FSDX7::connectPitch(FSModule *pitch, int output)
{
    for (int i = 0; i < 6; i++) {
        if (!_settings.operatorSettings[i].pitchIndependent) {
            _operators[i]->connectPitch(pitch, output);
        }
    }
}

void FSDX7::connectTrigger(FSModule *trigger, int output)
{
    for (int i = 0; i < 6; i++) {
        _operators[i]->connectTrigger(trigger, output);
    }
}

void FSDX7::connectDuration(FSModule *duration, int output)
{
    for (int i = 0; i < 6; i++) {
        _operators[i]->connectDuration(duration, output);
    }
}
