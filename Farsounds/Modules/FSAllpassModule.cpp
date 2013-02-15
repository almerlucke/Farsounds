//
//  FSAllpassModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSAllpassModule.h"
#include "FSEnvironment.h"
#include <stddef.h>

FSAllpassModule::FSAllpassModule() : FSModule(2, 1)
{
    _allpass = new FSAllpass(2000);
}

FSAllpassModule::FSAllpassModule(int delayLength) : FSModule(2, 1)
{
    _allpass = new FSAllpass(delayLength);
}

FSAllpassModule::FSAllpassModule(int delayLength, double feedback) : FSModule(2, 1)
{
    _allpass = new FSAllpass(delayLength);
    _allpass->feedback = feedback;
}

FSAllpassModule::~FSAllpassModule()
{
    delete _allpass;
}

void FSAllpassModule::run()
{
    FSModule::run();
    
    FSModuleInput *signalIn = _inputs[0];
    FSModuleInput *feedbackIn = _inputs[1];
    
    double inputValue = (signalIn != NULL)? signalIn->getValue() : 0.0;
    
    if (feedbackIn != NULL) {
        _allpass->feedback = feedbackIn->getValue();
    }
    
    _outputs[0].value = _allpass->generate(inputValue);
}