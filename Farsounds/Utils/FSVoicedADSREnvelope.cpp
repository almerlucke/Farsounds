//
//  FSVoicedADSREnvelope.cpp
//  Farsounds
//
//  Created by Almer Lucke on 3/11/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSVoicedADSREnvelope.h"
#include "FSEnvironment.h"
#include <cmath>


FSVoicedADSREnvelope::FSVoicedADSREnvelope()
{
    attackTime = 0.1;
    decayTime = 0.1;
    releaseTime = 0.1;
    attackLevel = 1.0;
    attackShape = 1.0;
    decayLevel = 0.5;
    decayShape = 1.0;
    releaseShape = 1.0;
    _stage = FSVoicedADSREnvelopeStageFinished;
}

#pragma mark - Trigger

void FSVoicedADSREnvelope::noteOn()
{
    _stage = FSVoicedADSREnvelopeStageAttack;
    switch (_stage) {
        case FSVoicedADSREnvelopeStageAttack:
            // attack
            _fromValue = 0.0;
            _toValue = attackLevel;
            _currentValue = 0.0;
            _currentShape = attackShape;
            _currentTime = attackTime * FSEnvironment::sampleRate;
            if (_currentTime != 0) {
                _currentStep = 1.0 / _currentTime;
                break;
            } else {
                _stage++;
                // fall through one stage in switch
            }
        case FSVoicedADSREnvelopeStageDecay:
            // decay
            _fromValue = attackLevel;
            _toValue = decayLevel;
            _currentValue = 0.0;
            _currentShape = decayShape;
            _currentTime = decayTime * FSEnvironment::sampleRate;
            if (_currentTime != 0) {
                _currentStep = 1.0 / _currentTime;
                break;
            } else {
                _stage++;
                // fall through one stage in switch
            }
        case FSVoicedADSREnvelopeStageSustain:
            // sustain
            _fromValue = decayLevel;
            _toValue = decayLevel;
            break;
        default: break;
    }
}

void FSVoicedADSREnvelope::noteOff()
{
    // release
    if (_stage < FSVoicedADSREnvelopeStageRelease) {
        _stage = FSVoicedADSREnvelopeStageRelease;
        _fromValue = (_toValue - _fromValue) * pow(_currentValue, _currentShape) + _fromValue;
        _toValue = 0.0;
        _currentValue = 0.0;
        _currentShape = releaseShape;
        _currentTime = releaseTime * FSEnvironment::sampleRate;
        if (_currentTime != 0) {
            _currentStep = 1.0 / _currentTime;
        } else {
            _stage++;
        }
    }
}


#pragma mark - Generate

bool FSVoicedADSREnvelope::isFinished()
{
    return (_stage == FSVoicedADSREnvelopeStageFinished);
}

double FSVoicedADSREnvelope::generate()
{
    double outputValue = 0.0;
    
    if (_stage < FSVoicedADSREnvelopeStageFinished) {
        if (_stage == FSVoicedADSREnvelopeStageSustain) {
            outputValue = _fromValue;
        } else {
            _currentTime--;
            outputValue = (_toValue - _fromValue) * pow(_currentValue, _currentShape) + _fromValue;
            _currentValue += _currentStep;
            if (_currentTime == 0) {
                switch (_stage) {
                    case FSVoicedADSREnvelopeStageAttack:
                        // go to decay
                        _fromValue = attackLevel;
                        _toValue = decayLevel;
                        _currentValue = 0.0;
                        _currentShape = decayShape;
                        _currentTime = decayTime * FSEnvironment::sampleRate;
                        if (_currentTime != 0) {
                            _currentStep = 1.0 / _currentTime;
                            break;
                        } else {
                            _stage++;
                            // fall through one stage in switch
                        }
                    case FSVoicedADSREnvelopeStageDecay:
                        // go to sustain
                        _fromValue = decayLevel;
                        _toValue = decayLevel;
                        break;
                    default: break;
                }
                _stage++;
            }
        }
    }
    
    return outputValue;
}