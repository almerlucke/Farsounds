//
//  FSTriangleModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSTriangleModule.h"


FSTriangleModule::FSTriangleModule() : FSPhasorModule() {}
FSTriangleModule::FSTriangleModule(double frequency) : FSPhasorModule(frequency) {}
FSTriangleModule::FSTriangleModule(double frequency, double phaseOffset) : FSPhasorModule(frequency, phaseOffset) {}

void FSTriangleModule::run()
{
    FSPhasorModule::run();
    
    double output = _outputs[0].value;
    
    if (output < 0.25) {
        output *= 4;
    } else if (output < 0.5) {
        output = 1.0 - (output - 0.25) * 4;
    } else if (output < 0.75) {
        output = 0.0 - (output - 0.5) * 4;
    } else {
        output = -1.0 + (output - 0.75) * 4;
    }
    
    _outputs[0].value = output;
}