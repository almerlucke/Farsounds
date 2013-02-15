//
//  FSModuleInput.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/14/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSModuleInput.h"
#include "FSModuleOutput.h"
#include "FSModule.h"
#include <stddef.h>


FSModuleInput::FSModuleInput()
{
    _inputs = NULL;
}

FSModuleInput::~FSModuleInput()
{
    FSModuleInputItem *item = _inputs;
    while (item != NULL) {
        FSModuleInputItem *tmpItem = item;
        item = item->next;
        delete tmpItem;
    }
}

void FSModuleInput::addConnection(FSModule *module, FSModuleOutput *output)
{
    FSModuleInputItem *item = new FSModuleInputItem;
    item->module = module;
    item->output = output;
    item->next = _inputs;
    _inputs = item;
}

double FSModuleInput::getValue()
{
    FSModuleInputItem *item = _inputs;
    double value = 0.0;
    
    // loop through all input connections and pull audio from connected modules
    // add output values to combine into one input value
    while (item != NULL) {
        if (!item->module->hasRun()) item->module->run();
        value += item->output->value;
        item = item->next;
    }
    
    return value;
}