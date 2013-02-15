//
//  FSScalerModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSScalerModule.h"
#include <stddef.h>

FSScalerModule::FSScalerModule() : FSModule(3, 1), _mult(1.0), _offset(0.0) {}
FSScalerModule::FSScalerModule(double mult) : FSModule(3, 1), _mult(mult), _offset(0.0) {}
FSScalerModule::FSScalerModule(double mult, double offset) : FSModule(3, 1), _mult(mult), _offset(offset) {}

void FSScalerModule::run()
{
    FSModule::run();
    
    FSModuleInput *signalIn = _inputs[0];
    FSModuleInput *multIn = _inputs[1];
    FSModuleInput *offsetIn = _inputs[2];
    double in = (signalIn != NULL)? signalIn->getValue() : 0.0;
    double mult = (multIn != NULL)? multIn->getValue() : _mult;
    double offset = (offsetIn != NULL)? offsetIn->getValue() : _offset;
    
    _outputs[0].value = in * mult + offset;
}