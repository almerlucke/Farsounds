//
//  FSADSREnvelope.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSADSREnvelope.h"
#include <cmath>

FSADSREnvelope::FSADSREnvelope()
{
    duration = 100;
    attackTimePercentage = 0.125;
    decayTimePercentage = 0.125;
    sustainTimePercentage = 0.5;
    attackLevel = 1.0;
    attackShape = 1.0;
    decayLevel = 0.5;
    decayShape = 1.0;
    releaseShape = 1.0;
    _stage = 4;
}

#pragma mark - Trigger

void FSADSREnvelope::trigger()
{
    _attackTime = duration * attackTimePercentage;
    _decayTime = duration * decayTimePercentage;
    _sustainTime = duration * sustainTimePercentage;
    _releaseTime = duration * (1.0 - (attackTimePercentage + decayTimePercentage + sustainTimePercentage));
    
    _stage = 0;
    switch (_stage) {
        case 0:
            // attack
            _fromValue = 0.0;
            _toValue = attackLevel;
            _currentValue = 0.0;
            _currentShape = attackShape;
            _currentTime = _attackTime;
            if (_currentTime != 0) {
                _currentStep = 1.0 / _currentTime;
                break;
            } else {
                _stage++;
                // fall through one stage in switch
            }
        case 1:
            // decay
            _fromValue = attackLevel;
            _toValue = decayLevel;
            _currentValue = 0.0;
            _currentShape = decayShape;
            _currentTime = _decayTime;
            if (_currentTime != 0) {
                _currentStep = 1.0 / _currentTime;
                break;
            } else {
                _stage++;
                // fall through one stage in switch
            }
        case 2:
            // sustain
            _fromValue = decayLevel;
            _toValue = decayLevel;
            _currentValue = 0.0;
            _currentShape = 1.0;
            _currentTime = _sustainTime;
            if (_currentTime != 0) {
                _currentStep = 1.0 / _currentTime;
                break;
            } else {
                _stage++;
                // fall through one stage in switch
            }
        case 3:
            // release
            _fromValue = decayLevel;
            _toValue = 0.0;
            _currentValue = 0.0;
            _currentShape = releaseShape;
            _currentTime = _releaseTime;
            if (_currentTime != 0) {
                _currentStep = 1.0 / _currentTime;
                break;
            } else {
                _stage++;
                // fall through one stage in switch
            }
        default: break;
    }
}

#pragma mark - Generate

double FSADSREnvelope::generate()
{
    double outputValue = 0.0;
    
    if (_stage < 4) {
        _currentTime--;
        outputValue = (_toValue - _fromValue) * pow(_currentValue, _currentShape) + _fromValue;
        _currentValue += _currentStep;
        if (_currentTime == 0) {
            switch (_stage) {
                case 0:
                    // decay
                    _fromValue = attackLevel;
                    _toValue = decayLevel;
                    _currentValue = 0.0;
                    _currentShape = decayShape;
                    _currentTime = _decayTime;
                    if (_currentTime != 0) {
                        _currentStep = 1.0 / _currentTime;
                        break;
                    } else {
                        _stage++;
                        // fall through one stage in switch
                    }
                case 1:
                    // sustain
                    _fromValue = decayLevel;
                    _toValue = decayLevel;
                    _currentValue = 0.0;
                    _currentShape = 1.0;
                    _currentTime = _sustainTime;
                    if (_currentTime != 0) {
                        _currentStep = 1.0 / _currentTime;
                        break;
                    } else {
                        _stage++;
                        // fall through one stage in switch
                    }
                case 2:
                    // release
                    _fromValue = decayLevel;
                    _toValue = 0.0;
                    _currentValue = 0.0;
                    _currentShape = releaseShape;
                    _currentTime = _releaseTime;
                    if (_currentTime != 0) {
                        _currentStep = 1.0 / _currentTime;
                        break;
                    } else {
                        _stage++;
                        // fall through one stage in switch
                    }
                default: break;
            }
            _stage++;
        }
    }
    
    return outputValue;
}