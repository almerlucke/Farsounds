//
//  FSBiquadFilterModule.h
//  Farsounds
//
//  Created by Almer Lucke on 2/27/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSBiquadFilterModule__
#define __Farsounds__FSBiquadFilterModule__

#include "FSModule.h"
#include "FSBiquadFilter.h"

class FSBiquadFilterModule :public FSModule {
    FSBiquadFilter *_biquad;
    
public:
    FSBiquadFilterModule(FSBiquadFilterType filterType,
                         double dbGain,
                         double centerFrequency,
                         double bandWidth);
    ~FSBiquadFilterModule();
    void run();
};

#endif /* defined(__Farsounds__FSBiquadFilterModule__) */
