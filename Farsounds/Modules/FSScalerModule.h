//
//  FSScalerModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSScalerModule__
#define __Farsounds__FSScalerModule__

#include "FSModule.h"

class FSScalerModule : public FSModule {
    double _mult;
    double _offset;
    
public:
    FSScalerModule();
    FSScalerModule(double mult);
    FSScalerModule(double mult, double offset);
    void run();
};

#endif /* defined(__Farsounds__FSScalerModule__) */
