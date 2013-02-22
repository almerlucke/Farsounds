//
//  FSWaveModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSWaveModule__
#define __Farsounds__FSWaveModule__

#include "FSPhasorModule.h"

class FSWaveModule :public FSPhasorModule {
    double *_waveTable;
    int _waveTableLength;
    
public:
    FSWaveModule(double *waveTable, int waveTableLength);
    FSWaveModule(double *waveTable, int waveTableLength, double frequency);
    FSWaveModule(double *waveTable, int waveTableLength, double frequency, double phaseOffset);
    void run();
};

#endif /* defined(__Farsounds__FSWaveModule__) */
