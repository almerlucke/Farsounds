//
//  FSPhasorModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSPhasorModule.h"
#include <stddef.h>

FSPhasorModule::FSPhasorModule() : FSModule(3, 1), _frequency(100.0), _phaseOffset(0.0)
{
    _phasor = new FSPhasor;
}

FSPhasorModule::FSPhasorModule(double frequency) : FSModule(3, 1), _frequency(frequency), _phaseOffset(0.0)
{
    _phasor = new FSPhasor;
}

FSPhasorModule::FSPhasorModule(double frequency, double phaseOffset) : FSModule(3, 1), _frequency(frequency), _phaseOffset(phaseOffset)
{
    _phasor = new FSPhasor;
}

FSPhasorModule::~FSPhasorModule() { delete _phasor; }

void FSPhasorModule::run()
{
    FSModule::run();
    
    FSModuleInput *freqIn = _inputs[0];
    FSModuleInput *phaseIn = _inputs[1];
    FSModuleInput *syncIn = _inputs[2];
    
    double frequency = (freqIn != NULL)? freqIn->getValue() : _frequency;
    double phaseOffset = (phaseIn != NULL)? phaseIn->getValue() : _phaseOffset;
    bool sync = (syncIn != NULL)? (syncIn->getValue() == 1.0) : false;
    
    _outputs[0].value = _phasor->generate(frequency, phaseOffset, sync);
}