//
//  FSDCSineModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSDCSineModule__
#define __Farsounds__FSDCSineModule__

#include "FSSineModule.h"

class FSDCSineModule :public FSSineModule {
    
public:
    FSDCSineModule();
    FSDCSineModule(double frequency);
    FSDCSineModule(double frequency, double phaseOffset);
    void run();
};

#endif /* defined(__Farsounds__FSDCSineModule__) */
