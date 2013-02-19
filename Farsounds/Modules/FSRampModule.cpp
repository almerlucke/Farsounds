//
//  FSRampModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/18/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSRampModule.h"
#include "FSEnvironment.h"
#include <cstddef>
#include <cmath>
#include <cstdio>

/*
 double _start;
 double _end;
 double _curValue;
 double _step;
 double _shape;
 int64_t _count;
 */

FSRampModule::FSRampModule() : FSModule(5, 2)
{
    _from = 0;
    _to = 1;
    _curValue = 0;
    _step = 0;
    _duration = 1.0;
    _shape = 1.0;
    _firstRamp = true;
}

FSRampModule::FSRampModule(double from) : FSModule(5, 2)
{
    _from = from;
    _to = 1;
    _curValue = 0;
    _step = 0;
    _duration = 1.0;
    _shape = 1.0;
    _firstRamp = true;
    _oldOutput = 0.0;
}

FSRampModule::FSRampModule(double from, double to) : FSModule(5, 2)
{
    _from = from;
    _to = to;
    _curValue = 0;
    _step = 0;
    _duration = 1.0;
    _shape = 1.0;
    _firstRamp = true;
    _oldOutput = 0.0;
}

FSRampModule::FSRampModule(double from, double to, double duration) : FSModule(5, 2)
{
    _from = from;
    _to = to;
    _curValue = 0;
    _step = 0;
    _duration = duration;
    _shape = 1.0;
    _firstRamp = true;
    _oldOutput = 0.0;
}

FSRampModule::FSRampModule(double from, double to, double duration, double shape) : FSModule(5, 2)
{
    _from = from;
    _to = to;
    _curValue = 0;
    _step = 0;
    _duration = duration;
    _shape = shape;
    _firstRamp = true;
    _oldOutput = 0.0;
}

void FSRampModule::run()
{
    FSModule::run();
    
    FSModuleInput *triggerIn = _inputs[0];
    FSModuleInput *fromIn = _inputs[1];
    FSModuleInput *toIn = _inputs[2];
    FSModuleInput *shapeIn = _inputs[3];
    FSModuleInput *durationIn = _inputs[4];
    
    double trigger = (triggerIn != NULL)? triggerIn->getValue() : 0.0;
    double from = (fromIn != NULL)? fromIn->getValue() : _from;
    double to = (toIn != NULL)? toIn->getValue() : _to;
    double shape = (shapeIn != NULL)? shapeIn->getValue() : _shape;
    double duration = (durationIn != NULL)? durationIn->getValue() : _duration;
    
    if (trigger == 1.0) {
        _count = duration * FSEnvironment::sampleRate;
        
        double realFrom = from;
        
        if (fromIn == NULL) {
            if (_firstRamp) {
                _firstRamp = false;
            } else {
                realFrom = _oldOutput;
            }
        }
        
        _from = realFrom;
        _to = to;
        _shape = shape;
        _curValue = 0.0;
        if (_count <= 0) _count = 1;
        _step = 1.0 / _count;
    }
    
    if (_count == 0) {
        _outputs[0].value = _oldOutput;
    } else {
        _outputs[0].value = _from + (_to - _from) * pow(_curValue, _shape);
        _count--;
        _curValue += _step;
        _oldOutput = _from + (_to - _from) * pow(_curValue, _shape);
    }
}