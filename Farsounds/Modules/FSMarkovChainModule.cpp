//
//  FSMarkovChainModule.cpp
//  Farsounds
//
//  Created by Almer Lucke on 5/28/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSMarkovChainModule.h"

#include <cstddef>

FSMarkovChainModule::FSMarkovChainModule(FSMarkovChain *chain) : FSModule(1, 1)
{
    _chain = chain;
    _lastValue = 0.0;
}

FSMarkovChainModule::~FSMarkovChainModule()
{
    delete _chain;
}

void FSMarkovChainModule::run()
{
    FSModule::run();
    
    FSModuleInput *triggerSignal = _inputs[0];
    double trigger = (triggerSignal != NULL)? triggerSignal->getValue() : 0.0;
    
    if (trigger == 1.0) {
        _lastValue = _chain->nextValue();
    }
    
    _outputs[0].value = _lastValue;
}