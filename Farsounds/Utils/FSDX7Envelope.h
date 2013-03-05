//
//  FSDX7Envelope.h
//  Farsounds
//
//  Created by aFrogleap on 2/24/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSDX7Envelope__
#define __Farsounds__FSDX7Envelope__

#include <stdint.h>


class FSDX7Envelope {
    int _stage;
    uint64_t _level1Time; // level4 -> level1, stage 0
    uint64_t _level2Time; // level1 -> level2, stage 1
    uint64_t _level3Time; // level2 -> level3, stage 2
    uint64_t _sustainTime; // hold level 3, stage 3
    uint64_t _releaseTime; // level3 -> level4, stage 4
    uint64_t _currentTime;
    double _fromValue;
    double _toValue;
    double _currentValue;
    double _currentStep;
    double _currentShape;
    
public:
    double duration; // duration in seconds
    double level1;
    double level2;
    double level3;
    double level4;
    double dur1; // duration level4 -> level1
    double dur2; // duration level1 -> level2
    double dur3; // duration level2 -> level3
    double dur4; // sustain duration
    double dur5; // release duration
    
    FSDX7Envelope()
    {
        _stage = 5;
    }
};

#endif /* defined(__Farsounds__FSDX7Envelope__) */
