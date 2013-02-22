//
//  FSSawModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSawModule.h"

FSSawModule::FSSawModule() : FSPhasorModule() {}
FSSawModule::FSSawModule(double frequency) : FSPhasorModule(frequency) {}
FSSawModule::FSSawModule(double frequency, double phaseOffset) : FSPhasorModule(frequency, phaseOffset) {}

void FSSawModule::run()
{
    FSPhasorModule::run();
    
    _outputs[0].value = _outputs[0].value * 2 - 1.0;
}