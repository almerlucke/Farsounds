//
//  FSTimedTriggerModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSTimedTriggerModule.h"
#include "FSEnvironment.h"
#include <stddef.h>


FSTimedTriggerModule::FSTimedTriggerModule(double *times, int numTimes, double initialDelay, bool loop) : FSModule(1, 2)
{
    _numTimes = numTimes;
    
    // copy times array
    _times = new double[numTimes];
    for (int i = 0; i < numTimes; i++) _times[i] = times[i];
    
    _timeIndex = 0;
    _initialDelay = initialDelay;
    
    // keep track of fractions to avoid too much deviation from real time when converting seconds to samples
    double realCounter = initialDelay * FSEnvironment::sampleRate;
    _counter = realCounter;
    _counterFraction = realCounter - _counter;
    _loop = loop;
}

FSTimedTriggerModule::~FSTimedTriggerModule()
{
    delete[] _times;
}

void FSTimedTriggerModule::run()
{
    FSModule::run();
    
    FSModuleInput *resetIn = _inputs[0];
    double reset = (resetIn != NULL)? resetIn->getValue() : 0.0;
    
    if (reset == 1.0) {
        _timeIndex = 0;
        double realCounter = _initialDelay * FSEnvironment::sampleRate;
        _counter = realCounter;
        _counterFraction = realCounter - _counter;
    }
    
    _outputs[0].value = 0.0;
    _outputs[1].value = 0.0;
    
    if (_timeIndex < _numTimes) {
        if (_counter <= 0) {
            double nextTime = _times[_timeIndex++];
            
            if (nextTime > 0.0) {
                _outputs[0].value = 1.0;
                _outputs[1].value = nextTime;
            } else {
                nextTime = -nextTime;
            }
            
            if ((_timeIndex == _numTimes) && _loop) {
                _timeIndex = 0;
            }
            
            // keep track of fractions to avoid too much deviation from real time when converting seconds to samples
            double realCounter = nextTime * FSEnvironment::sampleRate;
            _counter = realCounter;
            _counterFraction += realCounter - _counter;
            int addCount = _counterFraction;
            _counter += addCount;
            _counterFraction -= addCount;
        }
        
        --_counter;
    }
}