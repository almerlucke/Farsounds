//
//  FSDX7.h
//  Farsounds
//
//  Created by aFrogleap on 2/23/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSDX7__
#define __Farsounds__FSDX7__

#include "FSDX7Operator.h"

struct FSDX7Settings
{
    
    FSDX7OperatorSettings operatorSettings[6];
    
    void setPitchScale(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].pitchScale = op1;
        operatorSettings[1].pitchScale = op2;
        operatorSettings[2].pitchScale = op3;
        operatorSettings[3].pitchScale = op4;
        operatorSettings[4].pitchScale = op5;
        operatorSettings[5].pitchScale = op6;
    }
    
    void setVelocityLevel(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].velocityLevel = op1;
        operatorSettings[1].velocityLevel = op2;
        operatorSettings[2].velocityLevel = op3;
        operatorSettings[3].velocityLevel = op4;
        operatorSettings[4].velocityLevel = op5;
        operatorSettings[5].velocityLevel = op6;
    }
    
    void setFeedbackLevel(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].feedbackLevel = op1;
        operatorSettings[1].feedbackLevel = op2;
        operatorSettings[2].feedbackLevel = op3;
        operatorSettings[3].feedbackLevel = op4;
        operatorSettings[4].feedbackLevel = op5;
        operatorSettings[5].feedbackLevel = op6;
    }
    
    void setPitchIndependent(bool op1, bool op2, bool op3, bool op4, bool op5, bool op6)
    {
        operatorSettings[0].pitchIndependent = op1;
        operatorSettings[1].pitchIndependent = op2;
        operatorSettings[2].pitchIndependent = op3;
        operatorSettings[3].pitchIndependent = op4;
        operatorSettings[4].pitchIndependent = op5;
        operatorSettings[5].pitchIndependent = op6;
    }
    
    void setAttackLevel(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].attackLevel = op1;
        operatorSettings[1].attackLevel = op2;
        operatorSettings[2].attackLevel = op3;
        operatorSettings[3].attackLevel = op4;
        operatorSettings[4].attackLevel = op5;
        operatorSettings[5].attackLevel = op6;
    }

    void setAttackShape(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].attackShape = op1;
        operatorSettings[1].attackShape = op2;
        operatorSettings[2].attackShape = op3;
        operatorSettings[3].attackShape = op4;
        operatorSettings[4].attackShape = op5;
        operatorSettings[5].attackShape = op6;
    }

    void setAttackTime(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].attackTimePercentage = op1;
        operatorSettings[1].attackTimePercentage = op2;
        operatorSettings[2].attackTimePercentage = op3;
        operatorSettings[3].attackTimePercentage = op4;
        operatorSettings[4].attackTimePercentage = op5;
        operatorSettings[5].attackTimePercentage = op6;
    }

    void setDecayLevel(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].decayLevel = op1;
        operatorSettings[1].decayLevel = op2;
        operatorSettings[2].decayLevel = op3;
        operatorSettings[3].decayLevel = op4;
        operatorSettings[4].decayLevel = op5;
        operatorSettings[5].decayLevel = op6;
    }

    void setDecayShape(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].decayShape = op1;
        operatorSettings[1].decayShape = op2;
        operatorSettings[2].decayShape = op3;
        operatorSettings[3].decayShape = op4;
        operatorSettings[4].decayShape = op5;
        operatorSettings[5].decayShape = op6;
    }

    void setDecayTime(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].decayTimePercentage = op1;
        operatorSettings[1].decayTimePercentage = op2;
        operatorSettings[2].decayTimePercentage = op3;
        operatorSettings[3].decayTimePercentage = op4;
        operatorSettings[4].decayTimePercentage = op5;
        operatorSettings[5].decayTimePercentage = op6;
    }

    void setSustainTime(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].sustainTimePercentage = op1;
        operatorSettings[1].sustainTimePercentage = op2;
        operatorSettings[2].sustainTimePercentage = op3;
        operatorSettings[3].sustainTimePercentage = op4;
        operatorSettings[4].sustainTimePercentage = op5;
        operatorSettings[5].sustainTimePercentage = op6;
    }

    void setReleaseShape(double op1, double op2, double op3, double op4, double op5, double op6)
    {
        operatorSettings[0].releaseShape = op1;
        operatorSettings[1].releaseShape = op2;
        operatorSettings[2].releaseShape = op3;
        operatorSettings[3].releaseShape = op4;
        operatorSettings[4].releaseShape = op5;
        operatorSettings[5].releaseShape = op6;
    }
};

class FSDX7 {
private:
    FSDX7Operator *_operators[6];
    FSDX7Settings _settings;
    
public:
    FSDX7Operator *op1;
    FSDX7Operator *op2;
    FSDX7Operator *op3;
    FSDX7Operator *op4;
    FSDX7Operator *op5;
    FSDX7Operator *op6;
    
    FSDX7(FSDX7Settings settings, FSPatch *patch);
    ~FSDX7();
    
    void connectPitch(FSModule *pitch, int output);
    void connectTrigger(FSModule *trigger, int output);
    void connectDuration(FSModule *duration, int output);
};


#endif /* defined(__Farsounds__FSDX7__) */
