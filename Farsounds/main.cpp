//
//  main.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//


#include "FSVoicedADSREnvelope.h"
#include "midiread_example.h"
#include <iostream>


int main(int argc, const char * argv[])
{
//    FSVoicedADSREnvelope *env = new FSVoicedADSREnvelope();
//    
//    env->attackLevel = 1.0;
//    env->attackTime = 0.0001;
//    env->attackShape = 1.0;
//    env->decayLevel = 0.3;
//    env->decayShape = 1.0;
//    env->decayTime = 0.0001;
//    env->releaseShape = 1.0;
//    env->releaseTime = 0.0001;
//    
//    env->noteOn();
//    
//    for (int i = 0; i < 40; i++) {
//        std::cout << i << " " << env->generate() << std::endl;
//    }
//    
//    env->noteOff();
//    
//    while (!env->isFinished()) {
//        std::cout << env->generate() << std::endl;
//    }

    midiread_example();
    
    return 0;
}