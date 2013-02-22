//
//  FSMultiplierModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/21/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSMultiplierModule__
#define __Farsounds__FSMultiplierModule__

#include "FSModule.h"

class FSMultiplierModule :public FSModule {
    double _multiplier;
public:
    FSMultiplierModule(double multiplier);
    FSMultiplierModule(double multiplier, int numInputs);
    FSMultiplierModule(int numInputs);
    void run();
};

#endif /* defined(__Farsounds__FSMultiplierModule__) */
