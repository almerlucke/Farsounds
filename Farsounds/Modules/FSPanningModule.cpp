//
//  FSPanningModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSPanningModule.h"
#include "FSUtils.h"
#include <stddef.h>

FSPanningModule::FSPanningModule() : FSModule(2, 2), _position(0.0) {}
FSPanningModule::FSPanningModule(double position) : FSModule(2, 2), _position(position) {}

void FSPanningModule::run()
{
    FSModule::run();
    
    FSModuleInput *signalIn = _inputs[0];
    FSModuleInput *positionIn = _inputs[1];
    double inputValue = (signalIn != NULL)? signalIn->getValue() : 0.0;
    double position = (positionIn != NULL)? positionIn->getValue() : _position;

    FSUtils::equalPowerPanMono(inputValue, position, &_outputs[0].value, &_outputs[1].value);
}