//
//  FSOneShotTriggerModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/21/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSOneShotTriggerModule__
#define __Farsounds__FSOneShotTriggerModule__

#include "FSModule.h"
#include <stdint.h>

class FSOneShotTriggerModule :public FSModule {
    uint64_t _delay;
    bool _triggered;
    
public:
    FSOneShotTriggerModule();
    FSOneShotTriggerModule(double delay); // delay (in seconds) single trigger
    void run();
};

#endif /* defined(__Farsounds__FSOneShotTriggerModule__) */
