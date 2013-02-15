//
//  FSDivisorModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSDivisorModule.h"
#include <stddef.h>


FSDivisorModule::FSDivisorModule() : FSModule(2, 1), _numerator(1.0), _denominator(1.0) {}
FSDivisorModule::FSDivisorModule(double numerator) : FSModule(2, 1), _numerator(numerator), _denominator(1.0) {}
FSDivisorModule::FSDivisorModule(double numerator, double denominator) : FSModule(2, 1), _numerator(numerator), _denominator(denominator) {}

void FSDivisorModule::run()
{
    FSModule::run();
    
    FSModuleInput *numerIn = _inputs[0];
    FSModuleInput *denomIn = _inputs[1];
    double numer = (numerIn != NULL)? numerIn->getValue() : _numerator;
    double denom = (denomIn != NULL)? denomIn->getValue() : _denominator;
    
    if (denom != 0.0) {
        _outputs[0].value = numer / denom;
    } else {
        _outputs[0].value = 0.0;
    }
}