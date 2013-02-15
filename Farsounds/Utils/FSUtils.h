//
//  FSUtils.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSUtils__
#define __Farsounds__FSUtils__

class FSModule;

class FSUtils {
public:
    static void generateSoundFile(const char *path, FSModule *module, double durationInSeconds);
    static double wrapSample(double sample, double low, bool lowInclusive, double high, bool highInclusive);
    
    // input should be 0 -- 1
    static double tableLookup(double input, double *table, int tableLength);
    
    // azimuth range -1 -- 1
    static void equalPowerPanMono(double input, double azimuth, double *left, double *right);
    
    static void seedRand();
    static double randRange(double low, double high);
};

#endif /* defined(__Farsounds__FSUtils__) */
