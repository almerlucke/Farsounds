//
//  FSModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSModule__
#define __Farsounds__FSModule__

#include "FSModuleInput.h"
#include "FSModuleOutput.h"

class FSModule {
protected:
    int _numInputs;
    int _numOutputs;
    FSModuleInput **_inputs;
    FSModuleOutput *_outputs;
    bool _hasRun;
    
public:
    FSModule();
    FSModule(int numInputs, int numOutputs);
    virtual ~FSModule();
    
    int numInputs() { return _numInputs; }
    int numOutputs() { return _numOutputs; }
    
    virtual void connect(FSModule *module, int outIndex, int inIndex);
    virtual FSModuleOutput *outputAtIndex(int index);
    
    virtual void run() { _hasRun = true; };
    virtual void resetHasRun() { _hasRun = false; }
    
    bool hasRun() { return _hasRun; }
};

#endif /* defined(__Farsounds__FSModule__) */
