//
//  FSBiquadFilter.cpp
//  Farsounds
//
//  Created by Almer Lucke on 2/27/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSBiquadFilter.h"
#include "FSEnvironment.h"
#include <cmath>

FSBiquadFilter::FSBiquadFilter(FSBiquadFilterType filterType,
                               double dbGain,
                               double centerFrequency,
                               double bandWidth)
{
    _filterType = filterType;
    _dbGain = dbGain;
    _centerFrequency = centerFrequency;
    _bandWidth = bandWidth;
    _x1 = _x2 = _y1 = _y2 = 0.0;
    
    this->computeCoefficients();
}

void FSBiquadFilter::computeCoefficients()
{
    double A, omega, sn, cs, alpha, beta;
    double a0, a1, a2, b0, b1, b2;

    // setup variables
    A = pow(10, _dbGain /40);
    omega = 2 * M_PI * _centerFrequency / FSEnvironment::sampleRate;
    sn = sin(omega);
    cs = cos(omega);
    alpha = sn * sinh(M_LN2 / 2 * _bandWidth * omega / sn);
    beta = sqrt(A + A);
    
    switch (_filterType) {
        case FSBiquadFilterTypeLPF:
            b0 = (1 - cs) /2;
            b1 = 1 - cs;
            b2 = (1 - cs) /2;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case FSBiquadFilterTypeHPF:
            b0 = (1 + cs) /2;
            b1 = -(1 + cs);
            b2 = (1 + cs) /2;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case FSBiquadFilterTypeBPF:
            b0 = alpha;
            b1 = 0;
            b2 = -alpha;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case FSBiquadFilterTypeNOTCH:
            b0 = 1;
            b1 = -2 * cs;
            b2 = 1;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;
        case FSBiquadFilterTypePEQ:
            b0 = 1 + (alpha * A);
            b1 = -2 * cs;
            b2 = 1 - (alpha * A);
            a0 = 1 + (alpha /A);
            a1 = -2 * cs;
            a2 = 1 - (alpha /A);
            break;
        case FSBiquadFilterTypeLSH:
            b0 = A * ((A + 1) - (A - 1) * cs + beta * sn);
            b1 = 2 * A * ((A - 1) - (A + 1) * cs);
            b2 = A * ((A + 1) - (A - 1) * cs - beta * sn);
            a0 = (A + 1) + (A - 1) * cs + beta * sn;
            a1 = -2 * ((A - 1) + (A + 1) * cs);
            a2 = (A + 1) + (A - 1) * cs - beta * sn;
            break;
        case FSBiquadFilterTypeHSH:
            b0 = A * ((A + 1) + (A - 1) * cs + beta * sn);
            b1 = -2 * A * ((A - 1) + (A + 1) * cs);
            b2 = A * ((A + 1) + (A - 1) * cs - beta * sn);
            a0 = (A + 1) - (A - 1) * cs + beta * sn;
            a1 = 2 * ((A - 1) - (A + 1) * cs);
            a2 = (A + 1) - (A - 1) * cs - beta * sn;
            break;
        default: break;
    }
    
    /* precompute the coefficients */
    _a0 = b0 / a0;
    _a1 = b1 / a0;
    _a2 = b2 / a0;
    _a3 = a1 / a0;
    _a4 = a2 / a0;
    
//    /* zero initial samples */
//    b->x1 = b->x2 = 0;
//    b->y1 = b->y2 = 0;
    
    _needComputeCoefficients = false;
}

void FSBiquadFilter::setDbGain(double dbGain)
{
    _needComputeCoefficients = true;
    _dbGain = dbGain;
    
}

void FSBiquadFilter::setFilterType(FSBiquadFilterType filterType)
{
    _needComputeCoefficients = true;
    _filterType = filterType;
}

void FSBiquadFilter::setCenterFrequency(double centerFrequency)
{
    _needComputeCoefficients = true;
    _centerFrequency = centerFrequency;
}

void FSBiquadFilter::setBandWidth(double bandWidth)
{
    _needComputeCoefficients = true;
    _bandWidth = bandWidth;
}

double FSBiquadFilter::process(double input)
{
    if (_needComputeCoefficients) {
        this->computeCoefficients();
    }
    
    double result;
    
    /* compute result */
    result = _a0 * input + _a1 * _x1 + _a2 * _x2 - _a3 * _y1 - _a4 * _y2;
    
    /* shift x1 to x2, sample to x1 */
    _x2 = _x1;
    _x1 = input;
    
    /* shift y1 to y2, result to y1 */
    _y2 = _y1;
    _y1 = result;
    
    return result;
}