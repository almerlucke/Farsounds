//
//  FSOneShotTriggerModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/21/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSOneShotTriggerModule.h"
#include "FSEnvironment.h"

FSOneShotTriggerModule::FSOneShotTriggerModule() :FSModule(0, 1)
{
    _delay = 0;
    _triggered = false;
}

FSOneShotTriggerModule::FSOneShotTriggerModule(double delay) :FSModule(0, 1)
{
    // delay param is in seconds, translate to sample frames
    _delay = delay * FSEnvironment::sampleRate;
    _triggered = false;
}

void FSOneShotTriggerModule::run()
{
    FSModule::run();
    
    _outputs[0].value = 0.0;
    
    if (_triggered) return;
    
    if (_delay == 0) {
        _triggered = true;
        _outputs[0].value = 1.0;
    } else {
        _delay--;
    }
}