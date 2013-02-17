//
//  FSSoundFileModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/17/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSoundFileModule__
#define __Farsounds__FSSoundFileModule__

#include "FSModule.h"
#include "FSSoundFile.h"

// allow other modules to read from soundfile buffer
// 1 input: value from 0 to 1 (0 is start of soundfile, 1 is end of soundfile)
// n outputs: 1 output for each channel of the soundfile
class FSSoundFileModule : public FSModule
{
private:
    FSSoundFile *_soundFile;
    
public:
    FSSoundFileModule(FSSoundFile *soundFile);
    void run();
};

#endif /* defined(__Farsounds__FSSoundFileModule__) */