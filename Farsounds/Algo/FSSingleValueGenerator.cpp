//
//  FSSingleValueGenerator.cpp
//  Farsounds
//
//  Created by Almer Lucke on 5/28/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#include "FSSingleValueGenerator.h"

FSSingleValueGenerator::FSSingleValueGenerator(double value) : FSValueGenerator()
{
    _value = value;
}

FSSingleValueGenerator::~FSSingleValueGenerator() {}

double FSSingleValueGenerator::nextValue()
{
    return _value;
}

void FSSingleValueGenerator::reset() {}