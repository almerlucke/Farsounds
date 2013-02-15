//
//  FSPatch.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSPatch.h"
#include <stddef.h>

FSPatch::FSPatch(int numInputs, int numOutputs) : FSModule()
{
    _numInputs = numInputs;
    _numOutputs = numOutputs;
    _modules = NULL;
    
    _inputProxies = new FSProxy*[numInputs];
    _outputProxies = new FSProxy*[numOutputs];
    
    for (int i = 0; i < numInputs; i++) {
        _inputProxies[i] = new FSProxy();
        this->addModule(_inputProxies[i]);
    }
    
    for (int i = 0; i < numOutputs; i++) {
        _outputProxies[i] = new FSProxy();
        this->addModule(_outputProxies[i]);
    }
}

FSPatch::~FSPatch()
{
    FSPatchModuleItem *item = _modules;
    while (item != NULL) {
        FSPatchModuleItem *tmpItem = item;
        item = item->next;
        delete tmpItem->module;
        delete tmpItem;
    }
    
    // input and output proxy objects are deleted because they are
    // added as normal modules in the module chain, so we only have to delete
    // the arrays itself
    delete[] _inputProxies;
    delete[] _outputProxies;
}

void FSPatch::addModule(FSModule *module)
{
    FSPatchModuleItem *item = new FSPatchModuleItem;
    if (_modules != NULL) {
        _modules->prev = item;
    }
    item->module = module;
    item->prev = NULL;
    item->next = _modules;
    _modules = item;
}

void FSPatch::removeModule(FSModule *module) {
    FSPatchModuleItem *item = _modules;
    
    while (item != NULL) {
        if (item->module == module) {
            if (item->prev != NULL) {
                item->prev->next = item->next;
            } else {
                _modules = item->next;
            }
            
            if (item->next != NULL) {
                item->next->prev = item->prev;
            }
            
            break;
        }
        item = item->next;
    }
}

void FSPatch::run()
{
    FSModule::run();
    
    // run output proxies to get values for patch outputs
    for (int i = 0; i < _numOutputs; i++) {
        _outputProxies[i]->run();
    }
}

void FSPatch::resetHasRun()
{
    FSModule::resetHasRun();
    
    FSPatchModuleItem *item = _modules;
    while (item != NULL) {
        item->module->resetHasRun();
        item = item->next;
    }
}

void FSPatch::connect(FSModule *module, int outIndex, int inIndex)
{
    if (inIndex > -1 && inIndex < _numInputs) {
        FSProxy *proxy = _inputProxies[inIndex];
        proxy->connect(module, outIndex, 0);
    }
}

FSModuleOutput *FSPatch::outputAtIndex(int index)
{
    if (index > -1 && index < _numOutputs) {
        FSProxy *proxy = _outputProxies[index];
        return proxy->outputAtIndex(0);
    }
    
    return NULL;
}

FSModule *FSPatch::inputProxyAtIndex(int index)
{
    if (index > -1 && index < _numInputs) {
        return _inputProxies[index];
    }
    
    return NULL;
}

FSModule *FSPatch::outputProxyAtIndex(int index)
{
    if (index > -1 && index < _numOutputs) {
        return _outputProxies[index];
    }
    
    return NULL;
}