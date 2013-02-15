//
//  FSProxy.h
//  Farsounds
//
//  Created by aFrogleap on 2/14/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSProxy__
#define __Farsounds__FSProxy__

#include "FSModule.h"

class FSProxy : public FSModule {
    
public:
    
    FSProxy() : FSModule(1, 1) {}
    
    void run();
};

#endif /* defined(__Farsounds__FSProxy__) */
