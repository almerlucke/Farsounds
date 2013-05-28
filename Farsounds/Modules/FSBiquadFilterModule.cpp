//
//  FSBiquadFilterModule.cpp
//  Farsounds
//
//  Created by Almer Lucke on 2/27/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSBiquadFilterModule.h"
#include <cstddef>

FSBiquadFilterModule::FSBiquadFilterModule(FSBiquadFilterType filterType,
                                           double dbGain,
                                           double centerFrequency,
                                           double bandWidth) : FSModule(1, 1)
{
    _biquad = new FSBiquadFilter(filterType, dbGain, centerFrequency, bandWidth);
}

FSBiquadFilterModule::~FSBiquadFilterModule()
{
    delete _biquad;
}

void FSBiquadFilterModule::run()
{
    FSModule::run();
    
    FSModuleInput *inputSignal = _inputs[0];
    double input = (inputSignal != NULL)? inputSignal->getValue() : 0.0;
    _outputs[0].value = _biquad->process(input);
}