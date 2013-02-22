//
//  FSDCTriangleModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSDCTriangleModule__
#define __Farsounds__FSDCTriangleModule__

#include "FSTriangleModule.h"

class FSDCTriangleModule :public FSTriangleModule {
    
public:
    FSDCTriangleModule();
    FSDCTriangleModule(double frequency);
    FSDCTriangleModule(double frequency, double phaseOffset);
    void run();
};

#endif /* defined(__Farsounds__FSDCTriangleModule__) */
