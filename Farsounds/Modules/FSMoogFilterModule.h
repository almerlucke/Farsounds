//
//  FSMoogFilterModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/20/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSMoogFilterModule__
#define __Farsounds__FSMoogFilterModule__

#include "FSModule.h"
#include "FSMoogFilter.h"

class FSMoogFilterModule :public FSModule {
//    double _resonance;
//    double _cutoff;
//    double _oldx;
//    double _oldy1;
//    double _oldy2;
//    double _oldy3;
//    double _y1;
//    double _y2;
//    double _y3;
//    double _y4;
    FSMoogFilter *_filter;
    
public:
    FSMoogFilterModule(double cutoff, double resonance);
    ~FSMoogFilterModule();
    void run();
};

#endif /* defined(__Farsounds__FSMoogFilterModule__) */
