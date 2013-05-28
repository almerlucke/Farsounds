//
//  FSSimpleMarkovChain.cpp
//  Farsounds
//
//  Created by Almer Lucke on 5/28/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSimpleMarkovChain.h"

#include <cstdarg>

FSSimpleMarkovChain::FSSimpleMarkovChain(int numGenerators, ...) : FSMarkovChain()
{
    va_list argList;
    va_start(argList, numGenerators);
    
    _numGenerators = numGenerators;
    _generators = new FSValueGenerator *[numGenerators];
    
    for (int i = 0; i < numGenerators; i++) {
        _generators[i] = va_arg(argList, FSValueGenerator *);
    }
    
    va_end(argList);
}

FSSimpleMarkovChain::~FSSimpleMarkovChain()
{
    for (int i = 0; i < _numGenerators; i++) {
        delete _generators[i];
    }
    
    delete[] _generators;
}

double FSSimpleMarkovChain::generateValue()
{
    return _generators[_currentState->stateID()]->nextValue();
}