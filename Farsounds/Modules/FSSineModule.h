//
//  FSSineModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSineModule__
#define __Farsounds__FSSineModule__

#include "FSPhasorModule.h"

class FSSineModule : public FSPhasorModule {
private:
    static double *sineTable();
    
public:
    FSSineModule();
    FSSineModule(double frequency);
    FSSineModule(double frequency, double phaseOffset);
    void run();
};

#endif /* defined(__Farsounds__FSSineModule__) */
