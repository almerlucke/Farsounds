//
//  FSWaveModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSWaveModule.h"
#include "FSUtils.h"

FSWaveModule::FSWaveModule(double *waveTable, int waveTableLength) : FSPhasorModule()
{
    _waveTable = waveTable;
    _waveTableLength = waveTableLength;
}

FSWaveModule::FSWaveModule(double *waveTable, int waveTableLength, double frequency) : FSPhasorModule(frequency)
{
    _waveTable = waveTable;
    _waveTableLength = waveTableLength;
}

FSWaveModule::FSWaveModule(double *waveTable, int waveTableLength, double frequency, double phaseOffset) : FSPhasorModule(frequency, phaseOffset)
{
    _waveTable = waveTable;
    _waveTableLength = waveTableLength;
}

void FSWaveModule::run()
{
    FSPhasorModule::run();
    
    _outputs[0].value = FSUtils::tableLookup(_outputs[0].value, _waveTable, _waveTableLength);
}