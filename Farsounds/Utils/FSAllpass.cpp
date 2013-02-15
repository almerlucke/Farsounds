//
//  FSAllpass.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSAllpass.h"


FSAllpass::FSAllpass(int delayLength)
{
    _delayLength = delayLength;
    _head = 0;
    feedback = 0.5;
    _delay = new double[delayLength];
}

FSAllpass::~FSAllpass()
{
    delete[] _delay;
}

double FSAllpass::generate(double input)
{
    double delayOut = _delay[_head] + input * feedback;
    double delayIn = input + delayOut * -feedback;
    _delay[_head++] = delayIn;
    if (_head == _delayLength) _head = 0;
    
    return delayOut;
}