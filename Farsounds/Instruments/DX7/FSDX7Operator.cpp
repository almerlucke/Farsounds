//
//  FSDX7Operator.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/23/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSDX7Operator.h"


FSDX7Operator::FSDX7Operator(FSDX7OperatorSettings settings, FSPatch *patch)
{
    if (settings.wave == FSDX7OperatorWaveSine) {
        osc = new FSSineModule();
    } else if (settings.wave == FSDX7OperatorWaveTri) {
        osc = new FSTriangleModule();
    } else if (settings.wave == FSDX7OperatorWaveSaw) {
        osc = new FSSawModule();
    } else if (settings.wave == FSDX7OperatorWaveSquare) {
        osc = new FSSquareModule();
    }
    
    adsr = new FSADSREnvelopeModule();
    feedback = new FSMultiplierModule(settings.feedbackLevel);
    amp = new FSMultiplierModule(settings.velocityLevel, 2);
    freq = new FSMultiplierModule(settings.pitchScale);
    
    feedback->connect(osc, 0, 0);
    // connect feedback to phase
    osc->connect(feedback, 0, 1);
    amp->connect(osc, 0, 0);
    amp->connect(adsr, 0, 1);
    osc->connect(freq, 0, 0);
    
    patch->addModule(osc);
    patch->addModule(adsr);
    patch->addModule(feedback);
    patch->addModule(amp);
    patch->addModule(freq);
    
    adsr->envelope->attackLevel = settings.attackLevel;
    adsr->envelope->attackShape = settings.attackShape;
    adsr->envelope->attackTimePercentage = settings.attackTimePercentage;
    adsr->envelope->decayLevel = settings.decayLevel;
    adsr->envelope->decayShape = settings.decayShape;
    adsr->envelope->decayTimePercentage = settings.decayTimePercentage;
    adsr->envelope->sustainTimePercentage = settings.sustainTimePercentage;
    adsr->envelope->releaseShape = settings.releaseShape;
}

void FSDX7Operator::connectModulator(FSDX7Operator *modulator)
{
    osc->connect(modulator->amp, 0, 1);
}

void FSDX7Operator::connectPitch(FSModule *pitch, int output)
{
    freq->connect(pitch, output, 0);
}

void FSDX7Operator::connectTrigger(FSModule *trigger, int output)
{
    adsr->connect(trigger, output, 0);
}

void FSDX7Operator::connectDuration(FSModule *duration, int output)
{
    adsr->connect(duration, output, 1);
}