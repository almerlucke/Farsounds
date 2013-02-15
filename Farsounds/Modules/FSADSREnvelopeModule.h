//
//  FSADSREnvelopeModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSADSREnvelopeModule__
#define __Farsounds__FSADSREnvelopeModule__

#include "FSADSREnvelope.h"
#include "FSModule.h"

// 2 inputs, first input for trigger, second input for duration in seconds
class FSADSREnvelopeModule : public FSModule {
    
public:
    FSADSREnvelope *envelope;
    
    FSADSREnvelopeModule();
    ~FSADSREnvelopeModule();
    void run();
};

#endif /* defined(__Farsounds__FSADSREnvelopeModule__) */
