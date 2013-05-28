//
//  FSSingleValueGenerator.h
//  Farsounds
//
//  Created by Almer Lucke on 5/28/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSSingleValueGenerator__
#define __Farsounds__FSSingleValueGenerator__

#include "FSValueGenerator.h"

class FSSingleValueGenerator :public FSValueGenerator {
    double _value;
    
public:
    FSSingleValueGenerator(double value);
    ~FSSingleValueGenerator();
    
    double nextValue();
    void reset();
};

#endif /* defined(__Farsounds__FSSingleValueGenerator__) */
