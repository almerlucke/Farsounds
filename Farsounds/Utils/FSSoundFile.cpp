//
//  FSSoundFile.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/17/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSoundFile.h"
#include <cstring>

FSSoundFile::FSSoundFile(const char *path)
{
    SNDFILE	*file;
	SF_INFO	sfinfo;
    
	memset(&sfinfo, 0, sizeof(sfinfo));
    
    sampleRate = 0.0;
    numChannels = 0;
    numFrames = 0;
    frames = NULL;
    
    if (!(file = sf_open(path, SFM_READ, &sfinfo))) {
        printf ("Error : Not able to open output file.\n") ;
        return;
    }
    
    sampleRate = sfinfo.samplerate;
    numChannels = sfinfo.channels;
    numFrames = sfinfo.frames;
    frames = new double[sfinfo.frames * sfinfo.channels];
    
    sf_count_t itemsRead = sf_read_double(file, frames, numFrames * numChannels);

    if (itemsRead != (numFrames * numChannels)) {
        delete[] frames;
        sampleRate = 0.0;
        numChannels = 0;
        numFrames = 0;
        frames = NULL;
    }
}

FSSoundFile::~FSSoundFile()
{
    delete[] frames;
}