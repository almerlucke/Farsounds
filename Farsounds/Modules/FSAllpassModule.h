//
//  FSAllpassModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSAllpassModule__
#define __Farsounds__FSAllpassModule__

#include "FSModule.h"
#include "FSAllpass.h"

// 2 inputs, 0 signal input, 1 feedback input
class FSAllpassModule : public FSModule {
    FSAllpass *_allpass;
    
public:
    FSAllpassModule();
    FSAllpassModule(int delayLength);
    FSAllpassModule(int delayLength, double feedback);
    ~FSAllpassModule();
    void run();
};

#endif /* defined(__Farsounds__FSAllpassModule__) */
