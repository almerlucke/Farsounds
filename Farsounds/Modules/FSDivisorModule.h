//
//  FSDivisorModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSDivisorModule__
#define __Farsounds__FSDivisorModule__

#include "FSModule.h"

class FSDivisorModule : public FSModule {
    double _numerator;
    double _denominator;
    
public:
    FSDivisorModule();
    FSDivisorModule(double numerator);
    FSDivisorModule(double numerator, double denominator);
    void run();
};

#endif /* defined(__Farsounds__FSDivisorModule__) */
