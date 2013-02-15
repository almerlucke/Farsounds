//
//  FSPhasorModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSPhasorModule__
#define __Farsounds__FSPhasorModule__

#include "FSModule.h"
#include "FSPhasor.h"
#include "FSEnvironment.h"
#include <stddef.h>

class FSPhasorModule : public FSModule {
    double _frequency;
    double _phaseOffset;
    FSPhasor *_phasor;
    
public:
    FSPhasorModule();
    FSPhasorModule(double frequency);
    FSPhasorModule(double frequency, double phaseOffset);
    ~FSPhasorModule();
    void run();
};

#endif /* defined(__Farsounds__FSPhasorModule__) */
