//
//  FSSampleAndHoldModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSampleAndHoldModule.h"
#include <stddef.h>

FSSampleAndHoldModule::FSSampleAndHoldModule() : FSModule(2, 1), _didHold(false) {}

void FSSampleAndHoldModule::run()
{
    FSModule::run();
    
    FSModuleInput *signalIn = _inputs[0];
    FSModuleInput *triggerIn = _inputs[1];
    double value = (signalIn != NULL)? signalIn->getValue() : 0.0;
    double trigger = (triggerIn != NULL)? triggerIn->getValue() : 0.0;
    
    if (trigger == 1.0 || !_didHold) {
        _holdValue = value;
        _didHold = true;
    }
    
    _outputs[0].value = _holdValue;
}