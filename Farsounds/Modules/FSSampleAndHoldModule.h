//
//  FSSampleAndHoldModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSampleAndHoldModule__
#define __Farsounds__FSSampleAndHoldModule__

#include "FSModule.h"

class FSSampleAndHoldModule : public FSModule {
    double _holdValue;
    bool _didHold;
    
public:
    FSSampleAndHoldModule();
    void run();
};

#endif /* defined(__Farsounds__FSSampleAndHoldModule__) */
