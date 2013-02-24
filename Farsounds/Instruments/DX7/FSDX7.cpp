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

FSDX7::FSDX7(FSDX7Settings settings, FSDX7Algorithm algorithm, FSModule *output, int outputIndex, FSPatch *patch)
{
    _settings = settings;
    
    _operators[0] = op1 = new FSDX7Operator(settings.operatorSettings[0], patch);
    _operators[1] = op2 = new FSDX7Operator(settings.operatorSettings[1], patch);
    _operators[2] = op3 = new FSDX7Operator(settings.operatorSettings[2], patch);
    _operators[3] = op4 = new FSDX7Operator(settings.operatorSettings[3], patch);
    _operators[4] = op5 = new FSDX7Operator(settings.operatorSettings[4], patch);
    _operators[5] = op6 = new FSDX7Operator(settings.operatorSettings[5], patch);
    
    switch (algorithm) {
        case FSDX7_ALGORITHM1:
            op1->connectModulator(op2);
            op5->connectModulator(op6);
            op4->connectModulator(op5);
            op3->connectModulator(op4);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM2:
            op1->connectModulator(op2);
            op5->connectModulator(op6);
            op4->connectModulator(op5);
            op3->connectModulator(op4);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM3:
            op2->connectModulator(op3);
            op1->connectModulator(op2);
            op5->connectModulator(op6);
            op4->connectModulator(op5);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM4:
            op2->connectModulator(op3);
            op1->connectModulator(op2);
            op5->connectModulator(op6);
            op4->connectModulator(op5);
            op6->connectModulator(op4);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM5:
            op1->connectModulator(op2);
            op3->connectModulator(op4);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM6:
            op1->connectModulator(op2);
            op3->connectModulator(op4);
            op5->connectModulator(op6);
            op6->connectModulator(op5);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM7:
            op1->connectModulator(op2);
            op3->connectModulator(op4);
            op3->connectModulator(op5);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM8:
            op1->connectModulator(op2);
            op3->connectModulator(op4);
            op3->connectModulator(op5);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM9:
            op1->connectModulator(op2);
            op3->connectModulator(op4);
            op3->connectModulator(op5);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM10:
            op1->connectModulator(op2);
            op2->connectModulator(op3);
            op4->connectModulator(op5);
            op4->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM11:
            op1->connectModulator(op2);
            op2->connectModulator(op3);
            op4->connectModulator(op5);
            op4->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM12:
            op1->connectModulator(op2);
            op3->connectModulator(op4);
            op3->connectModulator(op5);
            op3->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM13:
            op1->connectModulator(op2);
            op3->connectModulator(op4);
            op3->connectModulator(op5);
            op3->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM14:
            op1->connectModulator(op2);
            op3->connectModulator(op4);
            op4->connectModulator(op5);
            op4->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM15:
            op1->connectModulator(op2);
            op3->connectModulator(op4);
            op4->connectModulator(op5);
            op4->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM16:
            op1->connectModulator(op2);
            op1->connectModulator(op3);
            op1->connectModulator(op5);
            op3->connectModulator(op4);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM17:
            op1->connectModulator(op2);
            op1->connectModulator(op3);
            op1->connectModulator(op5);
            op3->connectModulator(op4);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM18:
            op1->connectModulator(op2);
            op1->connectModulator(op3);
            op1->connectModulator(op4);
            op4->connectModulator(op5);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM19:
            op1->connectModulator(op2);
            op2->connectModulator(op3);
            op4->connectModulator(op6);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM20:
            op1->connectModulator(op3);
            op2->connectModulator(op3);
            op4->connectModulator(op5);
            op4->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM21:
            op1->connectModulator(op3);
            op2->connectModulator(op3);
            op4->connectModulator(op6);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM22:
            op1->connectModulator(op2);
            op3->connectModulator(op6);
            op4->connectModulator(op6);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM23:
            op2->connectModulator(op3);
            op4->connectModulator(op6);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM24:
            op3->connectModulator(op6);
            op4->connectModulator(op6);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM25:
            op4->connectModulator(op6);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM26:
            op2->connectModulator(op3);
            op4->connectModulator(op5);
            op4->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM27:
            op2->connectModulator(op3);
            op4->connectModulator(op5);
            op4->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM28:
            op1->connectModulator(op2);
            op3->connectModulator(op4);
            op4->connectModulator(op5);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            output->connect(op6->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM29:
            op3->connectModulator(op4);
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM30:
            op3->connectModulator(op4);
            op4->connectModulator(op5);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            output->connect(op6->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM31:
            op5->connectModulator(op6);
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            break;
        case FSDX7_ALGORITHM32:
            output->connect(op1->amp, 0, outputIndex);
            output->connect(op2->amp, 0, outputIndex);
            output->connect(op3->amp, 0, outputIndex);
            output->connect(op4->amp, 0, outputIndex);
            output->connect(op5->amp, 0, outputIndex);
            output->connect(op6->amp, 0, outputIndex);
            break;
        default: break;
    }
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
