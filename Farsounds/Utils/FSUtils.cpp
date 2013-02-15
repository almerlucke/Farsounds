//
//  FSUtils.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSUtils.h"
#include "FSModule.h"
#include "FSEnvironment.h"
#include <sndfile.h>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>

void FSUtils::generateSoundFile(const char *path, FSModule *module, double durationInSeconds)
{
    long long framesToGenerate = FSEnvironment::sampleRate * durationInSeconds;
    int blockSize = 512;
    int numChannels = module->numOutputs();
    double *buffer = new double[blockSize * numChannels];
    
    SNDFILE	*file;
	SF_INFO	sfinfo;
    
	memset (&sfinfo, 0, sizeof (sfinfo)) ;
    
    sfinfo.frames		= framesToGenerate;
	sfinfo.samplerate	= FSEnvironment::sampleRate;
	sfinfo.channels		= numChannels;
	sfinfo.format		= (SF_FORMAT_WAV | SF_FORMAT_PCM_32);
    
    if (!(file = sf_open(path, SFM_WRITE, &sfinfo))) {
        printf ("Error : Not able to open output file.\n") ;
    }
    
    while (framesToGenerate) {
        int numFrames = (framesToGenerate < blockSize)? (int)framesToGenerate : blockSize;
        
        for (int i = 0; i < numFrames; i++) {
            module->resetHasRun();
            module->run();
            for (int j = 0; j < numChannels; j++) {
                buffer[i * numChannels + j] = module->outputAtIndex(j)->value;
            }
        }
        
        framesToGenerate -= numFrames;
        
        sf_write_double(file, buffer, numFrames * numChannels);
    }
    
    delete[] buffer;
    sf_close(file);
}

double FSUtils::wrapSample(double sample, double low, bool lowInclusive, double high, bool highInclusive)
{
    double range = 0.0;
    
    if (high < low) {
        double t = high;
        high = low;
        low = t;
    }
    
    range = high - low;
    
    if (lowInclusive) {
        while (sample <= low) sample += range;
    } else {
        while (sample < low) sample += range;
    }
    
    if (highInclusive) {
        while (sample >= high) sample -= range;
    } else {
        while (sample > high) sample -= range;
    }
    
    return sample;
}

void FSUtils::equalPowerPanMono(double input, double azimuth, double *left, double *right)
{
    azimuth = (azimuth + 1.0) / 2.0;
    *left = cos(0.5 * M_PI * azimuth) * input;
    *right = sin(0.5 * M_PI * azimuth) * input;
}

double FSUtils::tableLookup(double input, double *table, int tableLength)
{
    double xf = input * (tableLength - 1);
    int xi = xf;
    double fraction = xf - xi;
    
    return table[xi] * (1.0 - fraction) + table[xi + 1] * fraction;
}

void FSUtils::seedRand()
{
    srand((unsigned int)time(NULL));
}

double FSUtils::randRange(double low, double high)
{
    if (low > high) {
        double tmp = high;
        high = low;
        low = tmp;
    }
    
    return low + (high - low) * rand() / (double)RAND_MAX;
}