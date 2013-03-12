//
//  FSVoicedADSREnvelope.h
//  Farsounds
//
//  Created by Almer Lucke on 3/11/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSVoicedADSREnvelope__
#define __Farsounds__FSVoicedADSREnvelope__

#include <stdint.h>

class FSVoicedADSREnvelope {
private:
    enum FSVoicedADSREnvelopeStage {
        FSVoicedADSREnvelopeStageAttack = 0,
        FSVoicedADSREnvelopeStageDecay = 1,
        FSVoicedADSREnvelopeStageSustain = 2,
        FSVoicedADSREnvelopeStageRelease = 3,
        FSVoicedADSREnvelopeStageFinished = 4
    };
    
    FSVoicedADSREnvelopeStage _stage;
    uint64_t _currentTime;
    double _fromValue;
    double _toValue;
    double _currentValue;
    double _currentStep;
    double _currentShape;
    
public:
    // public times are in seconds
    double attackLevel;
    double attackShape;
    double attackTime;
    double decayLevel;
    double decayShape;
    double decayTime;
    double releaseShape;
    double releaseTime;
    
    FSVoicedADSREnvelope();
    void noteOn();
    void noteOff();
    bool isFinished();
    double generate();
};

#endif /* defined(__Farsounds__FSVoicedADSREnvelope__) */
