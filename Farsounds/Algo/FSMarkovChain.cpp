//
//  MarkovChain.cpp
//  MarkovChains
//
//  Created by Almer Lucke on 5/7/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSMarkovChain.h"

#include <cstddef>
#include <cstdarg>

#pragma mark - Init/Dealloc

FSMarkovChain::FSMarkovChain()
{
    _states = NULL;
    _numStates = 0;
    _startState = NULL;
    _currentState = NULL;
    _resetWhenFinished = false;
}

FSMarkovChain::~FSMarkovChain()
{
    for (int i = 0; i < _numStates; i++) {
        delete _states[i];
    }
    
    if (NULL != _states) {
        delete[] _states;
    }
}

void FSMarkovChain::setStates(int startStateID, int numStates, ...)
{
    va_list stateList;
    va_start(stateList, numStates);

    _states = new FSMarkovChainState *[numStates];
    _numStates = numStates;

    for (int i = 0; i < numStates; i++) {
        _states[i] = va_arg(stateList, FSMarkovChainState *);
    }

    _startState = this->findStateByID(startStateID);
    _currentState = _startState;

    va_end(stateList);
}



#pragma mark - Utils
FSMarkovChainState *FSMarkovChain::findStateByID(int stateID)
{
    for (int i = 0; i < _numStates; i++) {
        if (_states[i]->stateID() == stateID) {
            return _states[i];
        }
    }
    
    return NULL;
}



#pragma mark - Reset

void FSMarkovChain::reset()
{
    _currentState = _startState;
}

void FSMarkovChain::setResetWhenFinished(bool resetWhenFinished)
{
    _resetWhenFinished = resetWhenFinished;
}

bool FSMarkovChain::resetWhenFinished()
{
    return _resetWhenFinished;
}



#pragma mark - Get Next Value

double FSMarkovChain::nextValue()
{
    double value = 0.0;
    
    if (NULL != _currentState) {
        value = this->generateValue();
        
        int stateTransitionID = _currentState->nextStateID();
        FSMarkovChainState *newState = this->findStateByID(stateTransitionID);
        
        if (NULL != newState) {
            _currentState = newState;
        } else if (_resetWhenFinished) {
            this->reset();
        }
    }
    
    return value;
}