//
//  FSModule.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSModule.h"
#include <stddef.h>

FSModule::FSModule()
{
    _inputs = NULL;
    _outputs = NULL;
}

FSModule::FSModule(int numInputs, int numOutputs) : _numInputs(numInputs), _numOutputs(numOutputs)
{
    _inputs = new FSModuleInput*[numInputs];
    _outputs = new FSModuleOutput[numOutputs];
    
    for (int i = 0; i < numInputs; i++) {
        _inputs[i] = NULL;
    }
    
    for (int i = 0; i < numOutputs; i++) {
        _outputs[i].value = 0.0;
    }
}

FSModule::~FSModule()
{
    if (_inputs != NULL) {
        for (int i = 0; i < _numInputs; i++) {
            if (_inputs[i] != NULL) {
                delete _inputs[i];
            }
        }
        
        delete[] _inputs;
    }
    
    if (_outputs != NULL) {
        delete[] _outputs;
    }
}

void FSModule::connect(FSModule *module, int outIndex, int inIndex)
{
    if (inIndex > -1 && inIndex < _numInputs) {
        FSModuleOutput *output = module->outputAtIndex(outIndex);
        if (output != NULL) {
            FSModuleInput *input = _inputs[inIndex];
            if (input == NULL) {
                input = new FSModuleInput();
                _inputs[inIndex] = input;
            }
            input->addConnection(module, output);
        }
    }
}

FSModuleOutput *FSModule::outputAtIndex(int index)
{
    if (index > -1 && index < _numOutputs) {
        return &_outputs[index];
    }
    
    return NULL;
}