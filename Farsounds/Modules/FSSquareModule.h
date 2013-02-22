//
//  FSSquareModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSquareModule__
#define __Farsounds__FSSquareModule__

#include "FSPhasorModule.h"

class FSSquareModule :public FSPhasorModule {
    
public:
    FSSquareModule();
    FSSquareModule(double frequency);
    FSSquareModule(double frequency, double phaseOffset);
    void run();
};

#endif /* defined(__Farsounds__FSSquareModule__) */
