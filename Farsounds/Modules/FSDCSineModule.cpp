//
//  FSDCSineModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSDCSineModule.h"

FSDCSineModule::FSDCSineModule() : FSSineModule() {}
FSDCSineModule::FSDCSineModule(double frequency) : FSSineModule(frequency) {}
FSDCSineModule::FSDCSineModule(double frequency, double phaseOffset) : FSSineModule(frequency, phaseOffset) {}

void FSDCSineModule::run()
{
    FSSineModule::run();
    
    _outputs[0].value = (_outputs[0].value + 1.0) * 0.5;
}