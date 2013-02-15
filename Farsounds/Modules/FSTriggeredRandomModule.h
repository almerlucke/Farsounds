//
//  FSTriggeredRandomModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSTriggeredRandomModule__
#define __Farsounds__FSTriggeredRandomModule__

#include "FSModule.h"

class FSTriggeredRandomModule : public FSModule {
    double _low;
    double _high;
    double _value;
    
public:
    FSTriggeredRandomModule();
    FSTriggeredRandomModule(double low, double high);
    void run();
};

#endif /* defined(__Farsounds__FSTriggeredRandomModule__) */
