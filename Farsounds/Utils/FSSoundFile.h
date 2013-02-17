//
//  FSSoundFile.h
//  Farsounds
//
//  Created by aFrogleap on 2/17/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSoundFile__
#define __Farsounds__FSSoundFile__

#include <sndfile.h>

// read a soundfile from disc and store samples and other info
struct FSSoundFile {
    double sampleRate;
    int numChannels;
    sf_count_t numFrames;
    double *frames;
    
    FSSoundFile(const char *path);
    ~FSSoundFile();
};

#endif /* defined(__Farsounds__FSSoundFile__) */
