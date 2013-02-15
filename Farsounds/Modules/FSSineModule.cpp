//
//  FSSineModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSineModule.h"
#include "FSUtils.h"
#include <cmath>
#include <stdio.h>

const int kFSSineModuleTableSize = 4096;

double *FSSineModule::sineTable()
{
    static double __sineTable[kFSSineModuleTableSize];
    static bool __sineTableInit = false;
    
    if (!__sineTableInit) {
        __sineTableInit = true;
        
        for (int i = 0; i < kFSSineModuleTableSize; i++) {
            __sineTable[i] = sin(2 * M_PI * i / (double)(kFSSineModuleTableSize - 1));
        }
    }
    
    return __sineTable;
}

FSSineModule::FSSineModule() : FSPhasorModule() {}
FSSineModule::FSSineModule(double frequency) : FSPhasorModule(frequency) {}
FSSineModule::FSSineModule(double frequency, double phaseOffset) : FSPhasorModule(frequency, phaseOffset) {}

void FSSineModule::run()
{
    FSPhasorModule::run();
    _outputs[0].value = FSUtils::tableLookup(_outputs[0].value, sineTable(), kFSSineModuleTableSize);
}