//
//  FSDX7Operator.h
//  Farsounds
//
//  Created by aFrogleap on 2/23/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSDX7Operator__
#define __Farsounds__FSDX7Operator__

#include "FSPatch.h"
#include "FSSineModule.h"
#include "FSADSREnvelopeModule.h"
#include "FSMultiplierModule.h"

struct FSDX7OperatorSettings
{
    // pitch scaler if pitch is connected to external pitch module and independent pitch is false, else pitchScale in Hz
    double pitchScale;
    // output level (if modulator = depth of modulation, else = output velocity)
    double velocityLevel;
    // self feedback level (distortion)
    double feedbackLevel;
    // the way pitch (Hz) scale is interpreted, if false = pitchScale * inputPitch, else = pitchScale
    bool pitchIndependent;
    // adsr envelope
    double attackLevel;
    double attackShape;
    double attackTimePercentage;
    double decayLevel;
    double decayShape;
    double decayTimePercentage;
    double sustainTimePercentage;
    double releaseShape;
};

class FSDX7Operator
{
public:
    FSSineModule *osc;
    FSADSREnvelopeModule *adsr;
    FSMultiplierModule *feedback;
    FSMultiplierModule *amp;
    FSMultiplierModule *freq;
    
    FSDX7Operator(FSDX7OperatorSettings settings, FSPatch *patch);
    
    void connectModulator(FSDX7Operator *modulator);
    void connectPitch(FSModule *pitch, int output);
    void connectTrigger(FSModule *trigger, int output);
    void connectDuration(FSModule *duration, int output);
};

#endif /* defined(__Farsounds__FSDX7Operator__) */
