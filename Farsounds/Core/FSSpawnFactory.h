//
//  FSSpawnFactory.h
//  Farsounds
//
//  Created by aFrogleap on 2/20/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSpawnFactory__
#define __Farsounds__FSSpawnFactory__

#include "FSModule.h"
#include <stdint.h>
#include <cstddef>

struct FSSpawn {
    uint64_t duration;
    FSModule *module;
    
    FSSpawn() { duration = 0; module = NULL; }
    FSSpawn(uint64_t dur, FSModule *mod) { duration = dur; module = mod; }
    ~FSSpawn() { delete module; }
};

class FSSpawnFactory {
public:
    // constructor/deconstructor
    FSSpawnFactory() {}
    virtual ~FSSpawnFactory() {}
    
    // num outputs
    virtual int numOutputsPerSpawn() = 0;
    
    // spawn cycle
    virtual void startProductionCycle() = 0; // start production for one cycle
    virtual FSSpawn *produce() = 0; // produce for current cycle
    virtual void endProductionCycle() = 0; // end production for one cycle
};

#endif /* defined(__Farsounds__FSSpawnFactory__) */
