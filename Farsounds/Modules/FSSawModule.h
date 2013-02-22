//
//  FSSawModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSawModule__
#define __Farsounds__FSSawModule__

#include "FSPhasorModule.h"

class FSSawModule :public FSPhasorModule {
    
public:
    FSSawModule();
    FSSawModule(double frequency);
    FSSawModule(double frequency, double phaseOffset);
    void run();
};

#endif /* defined(__Farsounds__FSSawModule__) */
