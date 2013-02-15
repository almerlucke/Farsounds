//
//  FSPatch.h
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSPatch__
#define __Farsounds__FSPatch__

#include "FSModule.h"
#include "FSProxy.h"

class FSPatch : public FSModule {
private:
    struct FSPatchModuleItem {
        FSPatchModuleItem *prev;
        FSPatchModuleItem *next;
        FSModule *module;
    };
    
    FSPatchModuleItem *_modules;
    FSProxy **_inputProxies;
    FSProxy **_outputProxies;
    
public:
    
    FSPatch(int numInputs, int numOutputs);
    ~FSPatch();
    
    void addModule(FSModule *module);
    void removeModule(FSModule *module);
    
    // get internal proxy modules to connect objects inside patch to the outside world
    FSModule *inputProxyAtIndex(int index);
    FSModule *outputProxyAtIndex(int index);
    
    // overwrite connect to connect to input proxy
    void connect(FSModule *module, int outIndex, int inIndex);
    // overwrite output at index to get proxy output
    FSModuleOutput *outputAtIndex(int index);
    
    // overwrite reset run to reset all modules inside this patch
    void resetHasRun();
    
    // overwrite run to run output proxies
    void run();
};

#endif /* defined(__Farsounds__FSPatch__) */
