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

enum FSDX7Algorithm {
    FSDX7_NO_ALGORITHM = 0,
    FSDX7_ALGORITHM1 = 1,
    FSDX7_ALGORITHM2 = 2,
    FSDX7_ALGORITHM3 = 3,
    FSDX7_ALGORITHM4 = 4,
    FSDX7_ALGORITHM5 = 5,
    FSDX7_ALGORITHM6 = 6,
    FSDX7_ALGORITHM7 = 7,
    FSDX7_ALGORITHM8 = 8,
    FSDX7_ALGORITHM9 = 9,
    FSDX7_ALGORITHM10 = 10,
    FSDX7_ALGORITHM11 = 11,
    FSDX7_ALGORITHM12 = 12,
    FSDX7_ALGORITHM13 = 13,
    FSDX7_ALGORITHM14 = 14,
    FSDX7_ALGORITHM15 = 15,
    FSDX7_ALGORITHM16 = 16,
    FSDX7_ALGORITHM17 = 17,
    FSDX7_ALGORITHM18 = 18,
    FSDX7_ALGORITHM19 = 19,
    FSDX7_ALGORITHM20 = 20,
    FSDX7_ALGORITHM21 = 21,
    FSDX7_ALGORITHM22 = 22,
    FSDX7_ALGORITHM23 = 23,
    FSDX7_ALGORITHM24 = 24,
    FSDX7_ALGORITHM25 = 25,
    FSDX7_ALGORITHM26 = 26,
    FSDX7_ALGORITHM27 = 27,
    FSDX7_ALGORITHM28 = 28,
    FSDX7_ALGORITHM29 = 29,
    FSDX7_ALGORITHM30 = 30,
    FSDX7_ALGORITHM31 = 31,
    FSDX7_ALGORITHM32 = 32
};

struct FSDX7Settings
{
    FSDX7OperatorSettings operatorSettings[6];
    double feedbackLevel;
    
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
    
    void setFeedbackLevel(double fbLevel)
    {
        feedbackLevel = fbLevel;
    }
    
    void setFixedPitch(bool op1, bool op2, bool op3, bool op4, bool op5, bool op6)
    {
        operatorSettings[0].fixedPitch = op1;
        operatorSettings[1].fixedPitch = op2;
        operatorSettings[2].fixedPitch = op3;
        operatorSettings[3].fixedPitch = op4;
        operatorSettings[4].fixedPitch = op5;
        operatorSettings[5].fixedPitch = op6;
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
    
    void setWave(FSDX7OperatorWave wave)
    {
        operatorSettings[0].wave = wave;
        operatorSettings[1].wave = wave;
        operatorSettings[2].wave = wave;
        operatorSettings[3].wave = wave;
        operatorSettings[4].wave = wave;
        operatorSettings[5].wave = wave;
    }
    
    void setWave(FSDX7OperatorWave op1, FSDX7OperatorWave op2, FSDX7OperatorWave op3, FSDX7OperatorWave op4, FSDX7OperatorWave op5, FSDX7OperatorWave op6)
    {
        operatorSettings[0].wave = op1;
        operatorSettings[1].wave = op2;
        operatorSettings[2].wave = op3;
        operatorSettings[3].wave = op4;
        operatorSettings[4].wave = op5;
        operatorSettings[5].wave = op6;
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
    FSMultiplierModule *feedbackModule;
    
    FSDX7(FSDX7Settings settings, FSPatch *patch);
    FSDX7(FSDX7Settings settings, FSDX7Algorithm algorithm, FSModule *output, int outputIndex, FSPatch *patch);
    ~FSDX7();
    
    void connectPitch(FSModule *pitch, int output);
    void connectTrigger(FSModule *trigger, int output);
    void connectDuration(FSModule *duration, int output);
};


#endif /* defined(__Farsounds__FSDX7__) */
