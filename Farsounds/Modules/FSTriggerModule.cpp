//
//  FSTriggerModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSTriggerModule.h"
#include <stddef.h>

FSTriggerModule::FSTriggerModule() : FSModule(1, 1), _threshold(0.5), _prevValue(0.0) {}
FSTriggerModule::FSTriggerModule(double threshold) : FSModule(1, 1), _threshold(threshold), _prevValue(0.0) {}
FSTriggerModule::FSTriggerModule(double threshold, double prevValue) : FSModule(1, 1), _threshold(threshold), _prevValue(prevValue) {}

void FSTriggerModule::run()
{
    FSModule::run();
    
    FSModuleInput *signalIn = _inputs[0];
    double value = (signalIn != NULL)? signalIn->getValue() : 0.0;
    
    if (_prevValue < _threshold && value >= _threshold) {
        _outputs[0].value = 1.0;
    } else {
        _outputs[0].value = 0.0;
    }
    
    _prevValue = value;
}