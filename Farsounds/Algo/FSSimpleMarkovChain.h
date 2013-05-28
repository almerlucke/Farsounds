//
//  FSSimpleMarkovChain.h
//  Farsounds
//
//  Created by Almer Lucke on 5/28/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSimpleMarkovChain__
#define __Farsounds__FSSimpleMarkovChain__

/*
 * Concrete MarkovChain subclass
 *
 * Use stateID as index into a value generator array to generate a value for the current state
 */

#include "FSMarkovChain.h"
#include "FSValueGenerator.h"

class FSSimpleMarkovChain :public FSMarkovChain {
    int _numGenerators;
    FSValueGenerator **_generators;
    
public:
    FSSimpleMarkovChain(int numGenerators, ...);
    ~FSSimpleMarkovChain();
    double generateValue();
};

#endif /* defined(__Farsounds__FSSimpleMarkovChain__) */
