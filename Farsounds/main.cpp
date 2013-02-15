//
//  main.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include <iostream>
#include "FSTestModule.h"
#include "FSPatch.h"


int main(int argc, const char * argv[])
{
    FSPatch *mainPatch = new FSPatch(0, 1);
    FSPatch *subPatch = new FSPatch(1, 1);
    FSTestModule *outerTestModule = new FSTestModule();
    FSTestModule *innerTestModule = new FSTestModule();
    
    // set up sub patch
    // add test module to sub patch
    subPatch->addModule(innerTestModule);
    // connect test module input to sub patch input proxy
    innerTestModule->connect(subPatch->inputProxyAtIndex(0), 0, 0);
    // connect inner test module output to sub patch output proxy
    subPatch->outputProxyAtIndex(0)->connect(innerTestModule, 0, 0);
    
    // set up main patch
    mainPatch->addModule(outerTestModule);
    mainPatch->addModule(subPatch);
    // connect outer test module output to sub patch input
    subPatch->connect(outerTestModule, 0, 0);
    mainPatch->outputProxyAtIndex(0)->connect(subPatch, 0, 0);
    
    for (int i = 0; i < 10; i++) {
        mainPatch->resetHasRun();
        mainPatch->run();
        printf("out %lf\n", mainPatch->outputAtIndex(0)->value);
    }
    
    delete mainPatch;
    
    return 0;
}