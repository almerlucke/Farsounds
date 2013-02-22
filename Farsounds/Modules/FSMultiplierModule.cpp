//
//  FSMultiplierModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/21/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSMultiplierModule.h"
#include <cstddef>

FSMultiplierModule::FSMultiplierModule(double multiplier) :FSModule(1, 1), _multiplier(multiplier) {}

FSMultiplierModule::FSMultiplierModule(double multiplier, int numInputs) :FSModule(numInputs, 1), _multiplier(multiplier) {}

FSMultiplierModule::FSMultiplierModule(int numInputs) :FSModule(numInputs, 1), _multiplier(1.0) {}

void FSMultiplierModule::run()
{
    FSModule::run();
    
    double outputValue = _multiplier;
    
    for (int i = 0; i < _numInputs; i++) {
        FSModuleInput *input = _inputs[i];
        if (input != NULL) {
            outputValue *= input->getValue();
        }
    }
    
    _outputs[0].value = outputValue;
}