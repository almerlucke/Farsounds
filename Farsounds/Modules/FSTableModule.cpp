//
//  FSTableModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSTableModule.h"
#include "FSUtils.h"
#include <cstddef>

FSTableModule::FSTableModule(double *table, int tableLength) : FSModule(1, 1)
{
    _table = table;
    _tableLength = tableLength;
}

void FSTableModule::run()
{
    FSModule::run();
    
    FSModuleInput *lookupSignal = _inputs[0];
    
    _outputs[0].value = 0.0;
    if (lookupSignal != NULL) {
        double input = FSUtils::clip(lookupSignal->getValue(), 0, 1);
        _outputs[0].value = FSUtils::tableLookup(input, _table, _tableLength);
    }
}