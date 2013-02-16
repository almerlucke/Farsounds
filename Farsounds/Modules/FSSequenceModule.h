//
//  FSSequenceModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSequenceModule__
#define __Farsounds__FSSequenceModule__

#include "FSModule.h"

// 2 inputs, 1st: trigger next value in sequence, 2nd: reset sequence on trigger
class FSSequenceModule : public FSModule {
    double *_sequence;
    int _numValues;
    int _index;
    double _currentValue;
    
public:
    FSSequenceModule(double *sequence, int numValues);
    ~FSSequenceModule();
    void run();
};

#endif /* defined(__Farsounds__FSSequenceModule__) */
