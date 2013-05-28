//
//  FSUtils.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSUtils__
#define __Farsounds__FSUtils__


#define ARC4_RANDOM_MAX 0x100000000


class FSModule;

class FSUtils {
private:
    static double modZeroBessel(double x);
    
public:
    // generate 32bit linear pcm wav file
    static void generateSoundFile(const char *path, FSModule *module, double durationInSeconds);
    
    // wrap and clip
    static double wrap(double sample, double low, bool lowInclusive, double high, bool highInclusive);
    static double clip(double input, double low, double high);
    
    // input should be 0 -- 1
    static double tableLookup(double input, double *table, int tableLength);
    
    // azimuth range -1 -- 1
    static void equalPowerPanMono(double input, double azimuth, double *left, double *right);
    
    // random
    static double randRange(double low, double high);
    
    // midi note to frequency (A4 - 69 is base)
    static double mtof(int note);
    
    // windowing functions
    static void bartlettWindow(double *window, int windowLength);
    static void hanningWindow(double *window, int windowLength);
    static void hammingWindow(double *window, int windowLength);
    static void blackmanWindow(double *window, int windowLength);
    static void kaiserWindow(double *window, int windowLength, double beta);
};

#endif /* defined(__Farsounds__FSUtils__) */
