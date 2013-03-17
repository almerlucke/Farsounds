//
//  FSMoogFilter.h
//  Farsounds
//
//  Created by Almer Lucke on 3/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSMoogFilter__
#define __Farsounds__FSMoogFilter__


class FSMoogFilter {
private:
    double _state[4];
    double _output;
    double _resonance;
    double _frequency;
    double _Q;
    double _P;
    
    void calculateQ();
    void calculateP();
    
public:
    FSMoogFilter();
    FSMoogFilter(double frequency);
    FSMoogFilter(double frequency, double resonance);
    
    void setResonance(double resonance);
    void setFrequency(double frequency);
    double resonance();
    double frequency();
    
    double process(double input);
};



#endif /* defined(__Farsounds__FSMoogFilter__) */
