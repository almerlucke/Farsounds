//
//  FSMarkovChainModule.h
//  Farsounds
//
//  Created by Almer Lucke on 5/28/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSMarkovChainModule__
#define __Farsounds__FSMarkovChainModule__

#include "FSModule.h"
#include "FSMarkovChain.h"

class FSMarkovChainModule :public FSModule {
    FSMarkovChain *_chain;
    double _lastValue;
    
public:
    FSMarkovChainModule(FSMarkovChain *chain);
    ~FSMarkovChainModule();
    void run();
};

#endif /* defined(__Farsounds__FSMarkovChainModule__) */
