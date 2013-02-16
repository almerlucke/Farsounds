//
//  FSSequenceModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSequenceModule.h"
#include <stddef.h>

FSSequenceModule::FSSequenceModule(double *sequence, int numValues) : FSModule(2, 1)
{
    // copy sequence
    _sequence = new double[numValues];
    _numValues = numValues;
    for (int i = 0; i < numValues; i++) {
        _sequence[i] = sequence[i];
    }
    
    _index = 0;
    _currentValue = 0.0;
}

FSSequenceModule::~FSSequenceModule()
{
    delete[] _sequence;
}

void FSSequenceModule::run()
{
    FSModule::run();
    
    FSModuleInput *triggerIn = _inputs[0];
    FSModuleInput *resetIn = _inputs[1];
    double trigger = (triggerIn != NULL)? triggerIn->getValue() : 0.0;
    double reset = (resetIn != NULL)? resetIn->getValue() : 0.0;
    
    if (reset) _index = 0;
    if (trigger) {
        _currentValue = _sequence[_index++];
        if (_index >= _numValues) {
            _index = 0;
        }
    }
    
    _outputs[0].value = _currentValue;
}