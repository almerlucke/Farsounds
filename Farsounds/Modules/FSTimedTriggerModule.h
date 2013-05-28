//
//  FSTimedTriggerModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSTimedTriggerModule__
#define __Farsounds__FSTimedTriggerModule__

#include "FSModule.h"
#include "FSValueGenerator.h"
#include <stdint.h>

// one input, an input trigger can be used to reset the timed trigger module
// two outputs, 1st output for trigger, 2nd output for time (in sec.) until next trigger
class FSTimedTriggerModule : public FSModule {
    double *_times;
    int _numTimes;
    int _timeIndex;
    double _initialDelay;
    bool _loop;
    int64_t _counter;
    double _counterFraction;
    FSValueGenerator *_timeGenerator;
    
public:
    FSTimedTriggerModule(double *times, int numTimes, double initialDelay, bool loop);
    FSTimedTriggerModule(FSValueGenerator *timeGenerator, double initialDelay);
    ~FSTimedTriggerModule();
    void run();
};

#endif /* defined(__Farsounds__FSTimedTriggerModule__) */