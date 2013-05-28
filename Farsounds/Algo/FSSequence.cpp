//
//  FSSequence.cpp
//  Farsounds
//
//  Created by Almer Lucke on 5/28/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSequence.h"

#include <cstdarg>
#include <cstddef>

FSSequence::FSSequence(int numSteps, ...) : FSValueGenerator()
{
    va_list argList;
    va_start(argList, numSteps);
    
    _currentStep = 0;
    _numSteps = numSteps;
    _steps = new FSValueGenerator *[numSteps];
    
    for (int i = 0; i < numSteps; i++) {
        _steps[i] = va_arg(argList, FSValueGenerator *);
    }
    
    va_end(argList);
}

FSSequence::~FSSequence()
{
    for (int i = 0; i < _numSteps; i++) {
        delete _steps[i];
    }
    
    delete[] _steps;
}

double FSSequence::nextValue()
{
    double value = _steps[_currentStep++]->nextValue();
    
    if (_currentStep >= _numSteps) {
        _currentStep = 0;
    }
    
    return value;
}

void FSSequence::reset()
{
    _currentStep = 0;
}