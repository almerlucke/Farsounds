//
//  FSPhasor.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSPhasor.h"
#include "FSEnvironment.h"
#include "FSUtils.h"

double FSPhasor::generate(double frequency, double phaseOffset, bool sync)
{
    double phaseIncrement = frequency / FSEnvironment::sampleRate;
 
    if (sync) {
        _previousSample = 0.0;
    }
    
    double sample = FSUtils::wrapSample(_previousSample + phaseOffset, 0.0, false, 1.0, true);
    
    _previousSample = FSUtils::wrapSample(_previousSample + phaseIncrement, 0.0, false, 1.0, true);
    
    return sample;
}