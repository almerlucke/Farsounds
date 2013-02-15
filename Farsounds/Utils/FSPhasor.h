//
//  FSPhasor.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSPhasor__
#define __Farsounds__FSPhasor__

class FSPhasor {
    double _previousSample;
    
public:
    
    FSPhasor() : _previousSample(0.0) {}
    
    double generate(double frequency, double phaseOffset, bool sync);
};

#endif /* defined(__Farsounds__FSPhasor__) */
