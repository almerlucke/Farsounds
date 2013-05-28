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


FSTimedTriggerModule::FSTimedTriggerModule(double *times, int numTimes, double initialDelay, bool loop) : FSModule(1, 3)
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
    
    _timeGenerator = NULL;
}

FSTimedTriggerModule::FSTimedTriggerModule(FSValueGenerator *timeGenerator, double initialDelay) : FSModule(1, 3)
{
    _initialDelay = initialDelay;
    _timeGenerator = timeGenerator;
    
    // keep track of fractions to avoid too much deviation from real time when converting seconds to samples
    double realCounter = initialDelay * FSEnvironment::sampleRate;
    _counter = realCounter;
    _counterFraction = realCounter - _counter;
    
    _times = NULL;
}

FSTimedTriggerModule::~FSTimedTriggerModule()
{
    if (NULL != _times) delete[] _times;
    if (NULL != _timeGenerator) delete _timeGenerator;
}

void FSTimedTriggerModule::run()
{
    FSModule::run();
    
    FSModuleInput *resetIn = _inputs[0];
    double reset = (resetIn != NULL)? resetIn->getValue() : 0.0;
    
    if (reset == 1.0) {
        if (NULL == _timeGenerator) {
            _timeIndex = 0;
        } else {
            _timeGenerator->reset();
        }
        
        double realCounter = _initialDelay * FSEnvironment::sampleRate;
        _counter = realCounter;
        _counterFraction = realCounter - _counter;
    }
    
    _outputs[0].value = 0.0;
    _outputs[1].value = 0.0;
    _outputs[2].value = 0.0;
    
    if (NULL == _timeGenerator && _timeIndex >= _numTimes) return;
    
    if (_counter <= 0) {
        double nextTime = (NULL == _timeGenerator)? _times[_timeIndex++] : _timeGenerator->nextValue();
            
        if (nextTime > 0.0) {
            _outputs[0].value = 1.0;
            _outputs[1].value = nextTime;
        } else {
            nextTime = -nextTime;
        }
        
        if (NULL == _timeGenerator && _timeIndex == _numTimes) {
            _outputs[2].value = 1.0;
            if (_loop) {
                _timeIndex = 0;
            }
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