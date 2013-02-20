//
//  FSMoogFilterModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/20/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSMoogFilterModule.h"
#include "FSEnvironment.h"
#include <stddef.h>
#include <cmath>

FSMoogFilterModule::FSMoogFilterModule(double cutoff, double resonance) : FSModule(3, 1)
{
    _cutoff = cutoff;
    _resonance = resonance;
}

void FSMoogFilterModule::run()
{
    FSModule::run();
    
    FSModuleInput *signalInput = _inputs[0];
    FSModuleInput *cutoffInput = _inputs[1];
    FSModuleInput *resInput = _inputs[2];
    
    double sr = FSEnvironment::sampleRate;
    double insamp = (signalInput != NULL)? signalInput->getValue() : 0.0;
    double cutoff = (cutoffInput != NULL)? cutoffInput->getValue() : _cutoff;
    double resonance = (resInput != NULL)? resInput->getValue() : _resonance;
    
    double f = 2 * cutoff / sr;
    double k = 3.6 * f - 1.6 * f * f - 1; //(Empirical tunning)
    double p = (k + 1) * 0.5;
    double scale = exp((1 - p) * 1.386249);
    double r = resonance * scale;
    double x = insamp - r * _y4;
    
    _outputs[0].value = _y4;
    _y1 = x * p + _oldx * p - k * _y1;
    _y2 = _y1 * p + _oldy1 * p - k * _y2;
    _y3 = _y2 * p + _oldy2 * p - k * _y3;
    _y4 = _y3 * p + _oldy3 * p - k * _y4;
    _y4 = _y4 - (_y4 * _y4 * _y4) / 6.0;
    _oldx = x;
    _oldy1 = _y1;
    _oldy2 = _y2;
    _oldy3 = _y3;
}