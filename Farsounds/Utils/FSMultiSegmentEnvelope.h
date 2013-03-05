//
//  FSMultiSegmentEnvelope.h
//  Farsounds
//
//  Created by Almer Lucke on 2/26/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSMultiSegmentEnvelope__
#define __Farsounds__FSMultiSegmentEnvelope__

#include <stdint.h>

// first segment has start value
// last segment has end value, duration of last segment is not used

struct FSMultiSegmentEnvelopeSegment
{
    // duration in seconds to next segment
    uint64_t duration;
    // value for this segment
    double value;
    // shape of transition to next segment value
    // transition is between 0 - 1
    // output = to + (from - to) * pow(transition, shape);
    double shape;
};

class FSMultiSegmentEnvelope {
    FSMultiSegmentEnvelopeSegment *_segments;
    int _numSegments;
    int _currentSegment;
    uint64_t _count;
    double _shape;
    double _from;
    double _to;
    double _transitionPhase;
    double _transitionIncrement;
    
public:
    
    FSMultiSegmentEnvelope(int numSegments);
    ~FSMultiSegmentEnvelope();
    
    
    FSMultiSegmentEnvelopeSegment *segments();
    void trigger();
    double generate();
};

#endif /* defined(__Farsounds__FSMultiSegmentEnvelope__) */
