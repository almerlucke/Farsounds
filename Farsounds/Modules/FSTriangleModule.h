//
//  FSTriangleModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSTriangleModule__
#define __Farsounds__FSTriangleModule__

#include "FSPhasorModule.h"

class FSTriangleModule :public FSPhasorModule {
    
public:
    FSTriangleModule();
    FSTriangleModule(double frequency);
    FSTriangleModule(double frequency, double phaseOffset);
    void run();
};

#endif /* defined(__Farsounds__FSTriangleModule__) */
