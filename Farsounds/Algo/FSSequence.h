//
//  FSSequence.h
//  Farsounds
//
//  Created by Almer Lucke on 5/28/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSequence__
#define __Farsounds__FSSequence__

#include "FSValueGenerator.h"

class FSSequence :public FSValueGenerator {
    int _numSteps;
    int _currentStep;
    FSValueGenerator **_steps;
    
public:
    FSSequence(int numSteps, ...);
    ~FSSequence();
    
    double nextValue();
    void reset();
};

#endif /* defined(__Farsounds__FSSequence__) */
