//
//  main.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include <iostream>
#include "FSEnvironment.h"
#include "FSUtils.h"
#include "FSPatch.h"
#include "FSSpawnFactory.h"
#include "FSSpawnModule.h"

#include "FSSineModule.h"
#include "FSADSREnvelopeModule.h"
#include "FSScalerModule.h"
#include "FSPanningModule.h"
#include "FSTimedTriggerModule.h"
#include "FSOneShotTriggerModule.h"
#include "FSMultiplierModule.h"
#include "FSAllpassModule.h"
#include "FSTriangleModule.h"
#include "FSSquareModule.h"



int main(int argc, const char * argv[])
{
    FSUtils::seedRand();
    
    FSPatch *mainPatch = new FSPatch(0, 1);
    FSSquareModule *square = new FSSquareModule(100.0);
    
    mainPatch->addModule(square);
    
    mainPatch->outputProxyAtIndex(0)->connect(square, 0, 0);

    FSUtils::generateSoundFile("/Users/aFrogleap/Desktop/test.wav", mainPatch, 3);

    delete mainPatch;
    
    return 0;
}