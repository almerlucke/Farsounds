//
//  FSSquareModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSquareModule.h"

FSSquareModule::FSSquareModule() : FSPhasorModule() {}
FSSquareModule::FSSquareModule(double frequency) : FSPhasorModule(frequency) {}
FSSquareModule::FSSquareModule(double frequency, double phaseOffset) : FSPhasorModule(frequency, phaseOffset) {}

void FSSquareModule::run()
{
    FSPhasorModule::run();
    
    double output = _outputs[0].value;
    
    if (output < 0.5) {
        output = 1.0;
    } else {
        output = -1.0;
    }
    
    _outputs[0].value = output;
}