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
#include "FSTriangleModule.h"
#include "FSSawModule.h"
#include "FSSquareModule.h"
#include "FSADSREnvelopeModule.h"
#include "FSMultiplierModule.h"

enum FSDX7OperatorWave {
    FSDX7OperatorWaveSine = 1,
    FSDX7OperatorWaveTri = 2,
    FSDX7OperatorWaveSaw = 3,
    FSDX7OperatorWaveSquare = 4
};

struct FSDX7OperatorSettings
{
    // pitch scaler if pitch is connected to external pitch module and independent pitch is false, else pitchScale in Hz
    double pitchScale;
    double velocityLevel;
    // the way pitch (Hz) scale is interpreted, if false = pitchScale * inputPitch, else = pitchScale
    bool fixedPitch;
    // adsr envelope
    double attackLevel;
    double attackShape;
    double attackTimePercentage;
    double decayLevel;
    double decayShape;
    double decayTimePercentage;
    double sustainTimePercentage;
    double releaseShape;
    FSDX7OperatorWave wave;
};

class FSDX7Operator
{
public:
    FSModule *osc;
    FSADSREnvelopeModule *adsr;
    FSMultiplierModule *amp;
    FSMultiplierModule *freq;
    
    FSDX7Operator(FSDX7OperatorSettings settings, FSPatch *patch);
    
    void connectModulator(FSDX7Operator *modulator);
    void connectPitch(FSModule *pitch, int output);
    void connectTrigger(FSModule *trigger, int output);
    void connectDuration(FSModule *duration, int output);
};

#endif /* defined(__Farsounds__FSDX7Operator__) */
