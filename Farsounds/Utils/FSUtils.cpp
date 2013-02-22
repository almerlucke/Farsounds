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



#pragma mark - Generate Soundfile
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

#pragma mark - Others
double FSUtils::wrap(double sample, double low, bool lowInclusive, double high, bool highInclusive)
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

double FSUtils::clip(double input, double low, double high)
{
    if (high < low) {
        double t = high;
        high = low;
        low = t;
    }
    
    if (input < low) input = low;
    if (input > high) input = high;
    
    return input;
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
    int xi1 = xf;
    int xi2 = (xi1 < (tableLength - 1))? xi1 + 1 : xi1;
    double fraction = xf - xi1;
    
    return table[xi1] * (1.0 - fraction) + table[xi2] * fraction;
}

#pragma mark - Random
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

#pragma mark - Conversions
// midi note to frequency (A4 - 69 is base)
double FSUtils::mtof(int note)
{
    return pow(2, (note - 69.0) / 12.0) * 440;
}


#pragma mark - Window Functions

double FSUtils::modZeroBessel(double x)
{
    int i;
    double x_2 = x / 2;
    double num = 1;
    double fact = 1;
    double result = 1;
    
    for (i = 1; i < 20; i++) {
        num *= x_2 * x_2;
        fact *= i;
        result += num / (fact * fact);
    }
    
    return result;
}

void FSUtils::bartlettWindow(double *window, int windowLength)
{
    int m = windowLength - 1;
	int halfLength = windowLength / 2;
    
    for (int n = 0; n <= halfLength; n++) {
        double tmp = (double)n - (double)m / 2;
        double val = 1.0 - (2.0 * fabs(tmp)) / m;
        window[n] = val;
        window[windowLength - n - 1] = val;
    }
}

void FSUtils::hanningWindow(double *window, int windowLength)
{
    int m = windowLength - 1;
	int halfLength = windowLength / 2;
    
    for (int n = 0; n <= halfLength; n++) {
        double val = 0.5 - 0.5 * cos(2.0 * M_PI * n / m);
        window[n] = val;
        window[windowLength - n - 1] = val;
    }
}

void FSUtils::hammingWindow(double *window, int windowLength)
{
    int m = windowLength - 1;
	int halfLength = windowLength / 2;
    
    for (int n = 0; n <= halfLength; n++) {
        double val = 0.54 - 0.46 * cos(2.0 * M_PI * n / m);
        window[n] = val;
        window[windowLength - n - 1] = val;
    }
}

void FSUtils::blackmanWindow(double *window, int windowLength)
{
    int m = windowLength - 1;
	int halfLength = windowLength / 2;
    
    for (int n = 0; n <= halfLength; n++) {
        double val = 0.42 - 0.5 * cos(2.0 * M_PI * n / m) + 0.08 * cos(4.0 * M_PI * n / m);
        window[n] = val;
        window[windowLength - n - 1] = val;
    }
}

void FSUtils::kaiserWindow(double *window, int windowLength, double beta)
{
    double m_2 = (double)(windowLength - 1) / 2.0;
    double denom = modZeroBessel(beta);
    
    for (int n = 0; n < windowLength; n++) {
        double val = (n - m_2) / m_2;
        val = 1 - (val * val);
        window[n] = modZeroBessel(beta * sqrt(val)) / denom;
    }
}