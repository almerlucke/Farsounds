//
//  FSSpawnModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/20/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSpawnModule__
#define __Farsounds__FSSpawnModule__

#include "FSModule.h"
#include "FSSpawnFactory.h"
#include <stdint.h>

class FSSpawnModule :public FSModule {
private:
    struct FSSpawnVoice {
        FSSpawn *spawn;
        FSSpawnVoice *prev;
        FSSpawnVoice *next;
        
        FSSpawnVoice(FSSpawn *s) { spawn = s; }
        ~FSSpawnVoice() { delete spawn; }
    };
    
    FSSpawnFactory *_factory;
    FSSpawnVoice *_voiceList;
    
    void addVoice(FSSpawn *spawn);
    void removeVoice(FSSpawnVoice *voice);
    
public:
    FSSpawnModule(FSSpawnFactory *factory);
    ~FSSpawnModule();
    void run();
};

#endif /* defined(__Farsounds__FSSpawnModule__) */