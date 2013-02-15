//
//  FSTestModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSTestModule__
#define __Farsounds__FSTestModule__

#include "FSModule.h"
#include <stddef.h>

class FSTestModule : public FSModule {
private:
    double _oldValue;
public:
    
    FSTestModule() : FSModule(1, 1) { _oldValue = 0.0; }
    
    void run()
    {
        FSModule::run();
        FSModuleInput *input = _inputs[0];
        double value = (input != NULL)? _oldValue + input->getValue() : 1.0;
        _oldValue = value;
        _outputs[0].value = value;
    }
};

#endif /* defined(__Farsounds__FSTestModule__) */
