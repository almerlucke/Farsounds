//
//  FSADSREnvelope.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSADSREnvelope__
#define __Farsounds__FSADSREnvelope__

#include <stdint.h>

class FSADSREnvelope {
    int _stage;
    uint64_t _attackTime;
    uint64_t _decayTime;
    uint64_t _sustainTime;
    uint64_t _releaseTime;
    uint64_t _currentTime;
    double _fromValue;
    double _toValue;
    double _currentValue;
    double _currentStep;
    double _currentShape;
    
public:
    uint64_t duration;
    double attackLevel;
    double attackShape;
    double attackTimePercentage;
    double decayLevel;
    double decayShape;
    double decayTimePercentage;
    double sustainTimePercentage;
    double releaseShape;
    
    FSADSREnvelope();
    void trigger();
    double generate();
};

#endif /* defined(__Farsounds__FSADSREnvelope__) */
