//
//  FSModuleInput.h
//  Farsounds
//
//  Created by aFrogleap on 2/14/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSModuleInput__
#define __Farsounds__FSModuleInput__

class FSModuleOutput;
class FSModule;

class FSModuleInput {
private:
    struct FSModuleInputItem {
        FSModuleInputItem *next;
        FSModuleOutput *output;
        FSModule *module;
    };
    
    FSModuleInputItem *_inputs; // list of module outputs linked to this input
    
public:
    
    FSModuleInput();
    ~FSModuleInput();
    
    void addConnection(FSModule *module, FSModuleOutput *output);
    double getValue();
};

#endif /* defined(__Farsounds__FSModuleInput__) */
