//
//  FSDCSquareModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSDCSquareModule.h"


FSDCSquareModule::FSDCSquareModule() : FSPhasorModule() {}
FSDCSquareModule::FSDCSquareModule(double frequency) : FSPhasorModule(frequency) {}
FSDCSquareModule::FSDCSquareModule(double frequency, double phaseOffset) : FSPhasorModule(frequency, phaseOffset) {}

void FSDCSquareModule::run()
{
    FSPhasorModule::run();
    
    double output = _outputs[0].value;
    
    if (output < 0.5) {
        output = 1.0;
    } else {
        output = 0.0;
    }
    
    _outputs[0].value = output;
}