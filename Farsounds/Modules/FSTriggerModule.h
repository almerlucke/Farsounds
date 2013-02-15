//
//  FSTriggerModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSTriggerModule__
#define __Farsounds__FSTriggerModule__

#include "FSModule.h"

class FSTriggerModule : public FSModule {
    double _threshold;
    double _prevValue;
    
public:
    FSTriggerModule();
    FSTriggerModule(double threshold);
    FSTriggerModule(double threshold, double prevValue);
    void run();
};

#endif /* defined(__Farsounds__FSTriggerModule__) */
