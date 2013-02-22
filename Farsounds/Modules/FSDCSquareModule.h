//
//  FSDCSquareModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSDCSquareModule__
#define __Farsounds__FSDCSquareModule__

#include "FSPhasorModule.h"

class FSDCSquareModule :public FSPhasorModule {
    
public:
    FSDCSquareModule();
    FSDCSquareModule(double frequency);
    FSDCSquareModule(double frequency, double phaseOffset);
    void run();
};

#endif /* defined(__Farsounds__FSDCSquareModule__) */
