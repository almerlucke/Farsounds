//
//  FSADSREnvelopeModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSADSREnvelopeModule.h"
#include "FSEnvironment.h"
#include <stddef.h>


FSADSREnvelopeModule::FSADSREnvelopeModule() : FSModule(2, 1)
{
    envelope = new FSADSREnvelope();
}

FSADSREnvelopeModule::~FSADSREnvelopeModule()
{
    delete envelope;
}

void FSADSREnvelopeModule::run()
{
    FSModule::run();
    
    FSModuleInput *triggerIn = _inputs[0];
    FSModuleInput *durationIn = _inputs[1];
    
    if (durationIn != NULL) {
        envelope->duration = durationIn->getValue() * FSEnvironment::sampleRate;
    }
    
    double trigger = (triggerIn != NULL)? triggerIn->getValue() : 0.0;
    if (trigger == 1.0) envelope->trigger();
    
    _outputs[0].value = envelope->generate();
}