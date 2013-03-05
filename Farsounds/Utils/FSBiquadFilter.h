//
//  FSBiquadFilter.h
//  Farsounds
//
//  Created by Almer Lucke on 2/27/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSBiquadFilter__
#define __Farsounds__FSBiquadFilter__

enum FSBiquadFilterType {
    // low pass
    FSBiquadFilterTypeLPF,
    // high pass
    FSBiquadFilterTypeHPF,
    // band pass
    FSBiquadFilterTypeBPF,
    // notch
    FSBiquadFilterTypeNOTCH,
    // peaking band EQ
    FSBiquadFilterTypePEQ,
    // low shelf
    FSBiquadFilterTypeLSH,
    // high shelf
    FSBiquadFilterTypeHSH
};

class FSBiquadFilter {
    double _a0, _a1, _a2, _a3, _a4;
    double _x1, _x2, _y1, _y2;
    double _dbGain;
    FSBiquadFilterType _filterType;
    double _centerFrequency;
    double _bandWidth;
    bool _needComputeCoefficients;
    
    void computeCoefficients();
    
public:
    
    FSBiquadFilter(FSBiquadFilterType filterType,
                   double dbGain,
                   double centerFrequency,
                   double bandWidth);
    
    void setDbGain(double dbGain);
    void setFilterType(FSBiquadFilterType filterType);
    void setCenterFrequency(double centerFrequency);
    void setBandWidth(double bandWidth);
    double process(double input);
};

#endif /* defined(__Farsounds__FSBiquadFilter__) */
