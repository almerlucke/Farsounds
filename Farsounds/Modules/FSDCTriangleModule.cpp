//
//  FSDCTriangleModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSDCTriangleModule.h"

FSDCTriangleModule::FSDCTriangleModule() : FSTriangleModule() {}
FSDCTriangleModule::FSDCTriangleModule(double frequency) : FSTriangleModule(frequency) {}
FSDCTriangleModule::FSDCTriangleModule(double frequency, double phaseOffset) : FSTriangleModule(frequency, phaseOffset) {}

void FSDCTriangleModule::run()
{
    FSTriangleModule::run();
    
    double output = _outputs[0].value;
    
    _outputs[0].value = (output + 1) * 0.5;
}