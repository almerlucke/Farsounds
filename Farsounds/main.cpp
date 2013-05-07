//
//  main.cpp
//  Farsounds
//
//  Created by aFrogleap on 2/13/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include <iostream>
#include "FSEnvironment.h"
#include "FSUtils.h"
#include "FSPatch.h"
#include "FSSpawnFactory.h"
#include "FSSpawnModule.h"

#include "FSSineModule.h"
#include "FSADSREnvelopeModule.h"
#include "FSScalerModule.h"
#include "FSPanningModule.h"
#include "FSTimedTriggerModule.h"
#include "FSOneShotTriggerModule.h"
#include "FSMultiplierModule.h"
#include "FSAllpassModule.h"
#include "FSTriangleModule.h"
#include "FSSquareModule.h"
#include "FSRampModule.h"
#include "FSTableModule.h"
#include "FSSequenceModule.h"
#include "FSSoundFile.h"
#include "FSSoundFileModule.h"


class DX7Operator
{
public:
    FSSineModule *osc;
    FSADSREnvelopeModule *adsr;
    FSMultiplierModule *feedback;
    FSMultiplierModule *amp;
    FSMultiplierModule *freq;
    
    DX7Operator(double pitchScale, double velocityLevel, double feedbackLevel, FSPatch *patch)
    {
        osc = new FSSineModule();
        adsr = new FSADSREnvelopeModule();
        feedback = new FSMultiplierModule(feedbackLevel);
        amp = new FSMultiplierModule(velocityLevel, 2);
        freq = new FSMultiplierModule(pitchScale);
        
        feedback->connect(osc, 0, 0);
        osc->connect(feedback, 0, 1); // connect feedback to phase
        amp->connect(osc, 0, 0);
        amp->connect(adsr, 0, 1);
        osc->connect(freq, 0, 0);
        
        patch->addModule(osc);
        patch->addModule(adsr);
        patch->addModule(feedback);
        patch->addModule(amp);
        patch->addModule(freq);
    }
    
    void connectModulator(DX7Operator *modulator)
    {
        osc->connect(modulator->amp, 0, 1);
    }
    
    void connectPitch(FSModule *pitch, int output)
    {
        freq->connect(pitch, output, 0);
    }
    
    void connectTrigger(FSModule *trigger, int output)
    {
        adsr->connect(trigger, output, 0);
    }
    
    void connectDuration(FSModule *duration, int output)
    {
        adsr->connect(duration, output, 1);
    }
};

struct DX7OperatorSettings
{
    double pitchScale;
    double velocityLevel;
    double feedbackLevel;
    bool pitchIndependent;
    double attackLevel;
    double attackShape;
    double attackTimePercentage;
    double decayLevel;
    double decayShape;
    double decayTimePercentage;
    double sustainTimePercentage;
    double releaseShape;
};

struct DX7Settings
{
    DX7OperatorSettings operatorSettings[6];
};

class DX7 {
private:
    DX7Operator *_operators[6];
    DX7Settings _settings;
    
public:
    DX7Operator *op1;
    DX7Operator *op2;
    DX7Operator *op3;
    DX7Operator *op4;
    DX7Operator *op5;
    DX7Operator *op6;
    
    DX7(DX7Settings settings, FSPatch *patch)
    {
        _settings = settings;
        
        DX7OperatorSettings operatorSettings = _settings.operatorSettings[0];
        op1 = new DX7Operator(operatorSettings.pitchScale, operatorSettings.velocityLevel, operatorSettings.feedbackLevel, patch);
        op1->adsr->envelope->attackLevel = operatorSettings.attackLevel;
        op1->adsr->envelope->attackShape = operatorSettings.attackShape;
        op1->adsr->envelope->attackTimePercentage = operatorSettings.attackTimePercentage;
        op1->adsr->envelope->decayLevel = operatorSettings.decayLevel;
        op1->adsr->envelope->decayShape = operatorSettings.decayShape;
        op1->adsr->envelope->decayTimePercentage = operatorSettings.decayTimePercentage;
        op1->adsr->envelope->sustainTimePercentage = operatorSettings.sustainTimePercentage;
        op1->adsr->envelope->releaseShape = operatorSettings.releaseShape;
        
        operatorSettings = _settings.operatorSettings[1];
        op2 = new DX7Operator(operatorSettings.pitchScale, operatorSettings.velocityLevel, operatorSettings.feedbackLevel, patch);
        op2->adsr->envelope->attackLevel = operatorSettings.attackLevel;
        op2->adsr->envelope->attackShape = operatorSettings.attackShape;
        op2->adsr->envelope->attackTimePercentage = operatorSettings.attackTimePercentage;
        op2->adsr->envelope->decayLevel = operatorSettings.decayLevel;
        op2->adsr->envelope->decayShape = operatorSettings.decayShape;
        op2->adsr->envelope->decayTimePercentage = operatorSettings.decayTimePercentage;
        op2->adsr->envelope->sustainTimePercentage = operatorSettings.sustainTimePercentage;
        op2->adsr->envelope->releaseShape = operatorSettings.releaseShape;
        
        operatorSettings = _settings.operatorSettings[2];
        op3 = new DX7Operator(operatorSettings.pitchScale, operatorSettings.velocityLevel, operatorSettings.feedbackLevel, patch);
        op3->adsr->envelope->attackLevel = operatorSettings.attackLevel;
        op3->adsr->envelope->attackShape = operatorSettings.attackShape;
        op3->adsr->envelope->attackTimePercentage = operatorSettings.attackTimePercentage;
        op3->adsr->envelope->decayLevel = operatorSettings.decayLevel;
        op3->adsr->envelope->decayShape = operatorSettings.decayShape;
        op3->adsr->envelope->decayTimePercentage = operatorSettings.decayTimePercentage;
        op3->adsr->envelope->sustainTimePercentage = operatorSettings.sustainTimePercentage;
        op3->adsr->envelope->releaseShape = operatorSettings.releaseShape;
        
        operatorSettings = _settings.operatorSettings[3];
        op4 = new DX7Operator(operatorSettings.pitchScale, operatorSettings.velocityLevel, operatorSettings.feedbackLevel, patch);
        op4->adsr->envelope->attackLevel = operatorSettings.attackLevel;
        op4->adsr->envelope->attackShape = operatorSettings.attackShape;
        op4->adsr->envelope->attackTimePercentage = operatorSettings.attackTimePercentage;
        op4->adsr->envelope->decayLevel = operatorSettings.decayLevel;
        op4->adsr->envelope->decayShape = operatorSettings.decayShape;
        op4->adsr->envelope->decayTimePercentage = operatorSettings.decayTimePercentage;
        op4->adsr->envelope->sustainTimePercentage = operatorSettings.sustainTimePercentage;
        op4->adsr->envelope->releaseShape = operatorSettings.releaseShape;
        
        operatorSettings = _settings.operatorSettings[4];
        op5 = new DX7Operator(operatorSettings.pitchScale, operatorSettings.velocityLevel, operatorSettings.feedbackLevel, patch);
        op5->adsr->envelope->attackLevel = operatorSettings.attackLevel;
        op5->adsr->envelope->attackShape = operatorSettings.attackShape;
        op5->adsr->envelope->attackTimePercentage = operatorSettings.attackTimePercentage;
        op5->adsr->envelope->decayLevel = operatorSettings.decayLevel;
        op5->adsr->envelope->decayShape = operatorSettings.decayShape;
        op5->adsr->envelope->decayTimePercentage = operatorSettings.decayTimePercentage;
        op5->adsr->envelope->sustainTimePercentage = operatorSettings.sustainTimePercentage;
        op5->adsr->envelope->releaseShape = operatorSettings.releaseShape;
        
        operatorSettings = _settings.operatorSettings[5];
        op6 = new DX7Operator(operatorSettings.pitchScale, operatorSettings.velocityLevel, operatorSettings.feedbackLevel, patch);
        op6->adsr->envelope->attackLevel = operatorSettings.attackLevel;
        op6->adsr->envelope->attackShape = operatorSettings.attackShape;
        op6->adsr->envelope->attackTimePercentage = operatorSettings.attackTimePercentage;
        op6->adsr->envelope->decayLevel = operatorSettings.decayLevel;
        op6->adsr->envelope->decayShape = operatorSettings.decayShape;
        op6->adsr->envelope->decayTimePercentage = operatorSettings.decayTimePercentage;
        op6->adsr->envelope->sustainTimePercentage = operatorSettings.sustainTimePercentage;
        op6->adsr->envelope->releaseShape = operatorSettings.releaseShape;
        
        _operators[0] = op1;
        _operators[1] = op2;
        _operators[2] = op3;
        _operators[3] = op4;
        _operators[4] = op5;
        _operators[5] = op6;
    }
    
    ~DX7()
    {
        for (int i = 0; i < 6; i++) delete _operators[i];
    }
    
    void connectPitch(FSModule *pitch, int output)
    {
        for (int i = 0; i < 6; i++) {
            if (!_settings.operatorSettings[i].pitchIndependent) {
                _operators[i]->connectPitch(pitch, output);
            }
        }
    }
    
    void connectTrigger(FSModule *trigger, int output)
    {
        for (int i = 0; i < 6; i++) {
            _operators[i]->connectTrigger(trigger, output);
        }
    }
    
    void connectDuration(FSModule *duration, int output)
    {
        for (int i = 0; i < 6; i++) {
            _operators[i]->connectDuration(duration, output);
        }
    }
};


DX7Settings settings1()
{
    DX7Settings dx7Settings;
    DX7OperatorSettings *dx7OperatorSettings = &dx7Settings.operatorSettings[0];
    dx7OperatorSettings->pitchScale = 200.1;
    dx7OperatorSettings->velocityLevel = 0.4;
    dx7OperatorSettings->feedbackLevel = 0.2;
    dx7OperatorSettings->pitchIndependent = true;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.021;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.1;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[1];
    dx7OperatorSettings->pitchScale = 2.03;
    dx7OperatorSettings->velocityLevel = 0.4;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.02;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.02;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[2];
    dx7OperatorSettings->pitchScale = 1.01;
    dx7OperatorSettings->velocityLevel = 0.8;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.03;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.02;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[3];
    dx7OperatorSettings->pitchScale = 1.02;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.04;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.021;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[4];
    dx7OperatorSettings->pitchScale = 2.02;
    dx7OperatorSettings->velocityLevel = 0.8;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.01;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[5];
    dx7OperatorSettings->pitchScale = 0.99;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.01;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    return dx7Settings;
}

DX7Settings settings2()
{
    DX7Settings dx7Settings;
    DX7OperatorSettings *dx7OperatorSettings = &dx7Settings.operatorSettings[0];
    dx7OperatorSettings->pitchScale = 0.25;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.2;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.01;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[1];
    dx7OperatorSettings->pitchScale = 3.02;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.02;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.02;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[2];
    dx7OperatorSettings->pitchScale = 2.0;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.03;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.02;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[3];
    dx7OperatorSettings->pitchScale = 1.05;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.01;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[4];
    dx7OperatorSettings->pitchScale = 2.01;
    dx7OperatorSettings->velocityLevel = 0.4;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = false;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.02;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    dx7OperatorSettings = &dx7Settings.operatorSettings[5];
    dx7OperatorSettings->pitchScale = 400.1;
    dx7OperatorSettings->velocityLevel = 0.3;
    dx7OperatorSettings->feedbackLevel = 0.0;
    dx7OperatorSettings->pitchIndependent = true;
    dx7OperatorSettings->attackLevel = 1.0;
    dx7OperatorSettings->attackShape = 1.0;
    dx7OperatorSettings->attackTimePercentage = 0.01;
    dx7OperatorSettings->decayLevel = 0.4;
    dx7OperatorSettings->decayShape = 1.0;
    dx7OperatorSettings->decayTimePercentage = 0.01;
    dx7OperatorSettings->sustainTimePercentage = 0.1;
    dx7OperatorSettings->releaseShape = 1.0;
    
    return dx7Settings;
}


int main(int argc, const char * argv[])
{
    FSUtils::seedRand();

    double times[5] = {0.15, 0.15, 0.15, 0.3, -0.15};
    double frequencies[12] = {
        FSUtils::mtof(72), FSUtils::mtof(71), FSUtils::mtof(45),
        FSUtils::mtof(67), FSUtils::mtof(41), FSUtils::mtof(55),
        FSUtils::mtof(33), FSUtils::mtof(47), FSUtils::mtof(48),
        FSUtils::mtof(74), FSUtils::mtof(88), FSUtils::mtof(53)};
    double amps1[5] = {1.0, 0.6, 0.4, 0.6, 0.7};
    
    double times2[8] = {0.15, 0.15, 0.15, 0.3, -0.15, 0.15, 0.15, -0.3};
    double frequencies2[4] = {
        FSUtils::mtof(24), FSUtils::mtof(38), FSUtils::mtof(52), FSUtils::mtof(41)};
    double amps2[5] = {1.0, 0.6, 0.4, 0.6, 0.7};
    
    FSPatch *mainPatch = new FSPatch(0, 1);
    FSTimedTriggerModule *trigger1 = new FSTimedTriggerModule(times, 5, 0, true);
    FSSequenceModule *sequencer1 = new FSSequenceModule(frequencies, 12);
    FSSequenceModule *ampSequencer1 = new FSSequenceModule(amps1, 5);
    FSTimedTriggerModule *trigger2 = new FSTimedTriggerModule(times2, 8, 0, true);
    FSSequenceModule *sequencer2 = new FSSequenceModule(frequencies2, 4);
    FSSequenceModule *ampSequencer2 = new FSSequenceModule(amps2, 5);
    FSMultiplierModule *amp1 = new FSMultiplierModule(2);
    FSMultiplierModule *amp2 = new FSMultiplierModule(2);
    FSAllpassModule *allpass1 = new FSAllpassModule(FSEnvironment::sampleRate * 0.6, 0.3);
    FSAllpassModule *allpass2 = new FSAllpassModule(FSEnvironment::sampleRate * 0.45, 0.2);

    DX7 *dx7 = new DX7(settings1(), mainPatch);
    dx7->connectTrigger(trigger1, 0);
    dx7->connectDuration(trigger1, 1);
    dx7->connectPitch(sequencer1, 0);
    dx7->op2->connectModulator(dx7->op1);
    dx7->op3->connectModulator(dx7->op2);
    dx7->op4->connectModulator(dx7->op3);
    dx7->op6->connectModulator(dx7->op5);
    
    DX7 *dx72 = new DX7(settings2(), mainPatch);
    dx72->connectTrigger(trigger2, 0);
    dx72->connectDuration(trigger2, 1);
    dx72->connectPitch(sequencer2, 0);
    dx72->op2->connectModulator(dx72->op1);
    dx72->op3->connectModulator(dx72->op2);
    dx72->op4->connectModulator(dx72->op3);
    dx72->op6->connectModulator(dx72->op5);
    
    sequencer1->connect(trigger1, 0, 0);
    ampSequencer1->connect(trigger1, 0, 0);
    amp1->connect(dx7->op4->amp, 0, 0);
    amp1->connect(dx7->op6->amp, 0, 0);
    amp1->connect(ampSequencer1, 0, 1);
    mainPatch->addModule(amp1);
    mainPatch->addModule(trigger1);
    mainPatch->addModule(allpass1);
    mainPatch->addModule(sequencer1);
    mainPatch->addModule(ampSequencer1);
    
    sequencer2->connect(trigger2, 0, 0);
    ampSequencer2->connect(trigger2, 0, 0);
    amp2->connect(dx72->op4->amp, 0, 0);
    amp2->connect(dx72->op6->amp, 0, 0);
    amp2->connect(ampSequencer2, 0, 1);
    mainPatch->addModule(amp2);
    mainPatch->addModule(trigger2);
    mainPatch->addModule(allpass2);
    mainPatch->addModule(sequencer2);
    mainPatch->addModule(ampSequencer2);
    
    allpass1->connect(amp1, 0, 0);
    allpass2->connect(amp2, 0, 0);
    
    mainPatch->outputProxyAtIndex(0)->connect(allpass1, 0, 0);
    mainPatch->outputProxyAtIndex(0)->connect(allpass2, 0, 0);

    FSUtils::generateSoundFile("/Users/almerlucke/Desktop/test2.wav", mainPatch, 60);
    
    delete dx7;
    delete dx72;
    delete mainPatch;
    
    return 0;
}