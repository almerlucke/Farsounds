//
//  FSProxy.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/14/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSProxy.h"
#include <stddef.h>

void FSProxy::run()
{
    FSModule::run();
    
    FSModuleInput *input = _inputs[0];
    _outputs[0].value = (input != NULL)? input->getValue() : 0.0;
}