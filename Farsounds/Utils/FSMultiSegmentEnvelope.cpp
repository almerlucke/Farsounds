//
//  FSMultiSegmentEnvelope.cpp
//  Farsounds
//
//  Created by Almer Lucke on 2/26/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSMultiSegmentEnvelope.h"
#include <cmath>

FSMultiSegmentEnvelope::FSMultiSegmentEnvelope(int numSegments)
{
    _numSegments = numSegments;
    
    // always create one segment more than given
    // last segment is end value for previous segment
    _segments = new FSMultiSegmentEnvelopeSegment[numSegments + 1];
}

FSMultiSegmentEnvelope::~FSMultiSegmentEnvelope()
{
    delete[] _segments;
}

FSMultiSegmentEnvelopeSegment *FSMultiSegmentEnvelope::segments()
{
    return _segments;
}

void FSMultiSegmentEnvelope::trigger()
{
    _count = _segments[0].duration;
    if (_count < 1) _count = 1;
    _currentSegment = 0;
    _transitionPhase = 0.0;
    _transitionIncrement = 1.0 / _count;
    _shape = _segments[0].shape;
    if (_shape < 0.1) _shape = 0.1;
    if (_shape > 10.0) _shape = 10.0;
    _from = _segments[0].value;
    if (_numSegments < 1) {
        _to = _from;
    } else {
        _to = _segments[1].value;
    }
}

double FSMultiSegmentEnvelope::generate()
{
    double output = _from + (_to - _from) * pow(_transitionPhase, _shape);
    
    if (_currentSegment < _numSegments) {
        _transitionPhase += _transitionIncrement;
        if (--_count == 0) {
            _currentSegment++;
            if (_currentSegment < _numSegments) {
                _count = _segments[_currentSegment].duration;
                if (_count < 1) _count = 1;
                _transitionPhase = 0.0;
                _transitionIncrement = 1.0 / _count;
                _shape = _segments[_currentSegment].shape;
                if (_shape < 0.1) _shape = 0.1;
                if (_shape > 10.0) _shape = 10.0;
                _from = _segments[_currentSegment].value;
                _to = _segments[_currentSegment + 1].value;
            }
        }
    }
    
    return output;
}