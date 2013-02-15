//
//  FSTriggeredRandomModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSTriggeredRandomModule.h"
#include "FSUtils.h"
#include <stddef.h>

FSTriggeredRandomModule::FSTriggeredRandomModule() : FSModule(3, 1), _low(0.0), _high(1.0)
{
    _value = FSUtils::randRange(_low, _high);
}

FSTriggeredRandomModule::FSTriggeredRandomModule(double low, double high) : FSModule(3, 1), _low(low), _high(high)
{
    _value = FSUtils::randRange(_low, _high);
}

void FSTriggeredRandomModule::run()
{
    FSModule::run();
    
    FSModuleInput *triggerInput = _inputs[0];
    FSModuleInput *lowInput = _inputs[1];
    FSModuleInput *highInput = _inputs[2];
    
    double trigger = (triggerInput != NULL)? triggerInput->getValue() : 0.0;
    double low = (lowInput != NULL)? lowInput->getValue() : _low;
    double high = (highInput != NULL)? highInput->getValue() : _high;
    
    if (trigger == 1.0) {
        _value = FSUtils::randRange(low, high);
    }
    
    _outputs[0].value = _value;
}