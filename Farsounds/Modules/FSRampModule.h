//
//  FSRampModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/18/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSRampModule__
#define __Farsounds__FSRampModule__

#include "FSModule.h"
#include <stdint.h>

// 5 inputs:
// input 1: trigger to start ramp
// input 2: ramp from value
// input 3: ramp to value
// input 4: ramp shape (0.1 - 10, exponential pow(x, ramp_shape), 1.0 is linear ramp) 
// input 5: duration in seconds
// if input 2 is not set ramp to value will ramp from current value
// start value can be set for first ramp
// 2 outputs:
// output 1: ramp value
// output 2: trigger when ramp is finished
class FSRampModule : public FSModule {
    double _from;
    double _to;
    double _curValue;
    double _step;
    double _shape;
    double _duration;
    double _oldOutput;
    int64_t _count;
    bool _firstRamp;
    
public:
    FSRampModule();
    FSRampModule(double start);
    FSRampModule(double start, double end);
    FSRampModule(double start, double end, double duration);
    FSRampModule(double start, double end, double duration, double shape);
    void run();
};

#endif /* defined(__Farsounds__FSRampModule__) */
