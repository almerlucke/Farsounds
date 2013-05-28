//
//  FSValueGenerator.h
//  Farsounds
//
//  Created by Almer Lucke on 5/28/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSValueGenerator__
#define __Farsounds__FSValueGenerator__

/*
 *  Abstract value generator class
 *
 */

class FSValueGenerator {
    
public:
    FSValueGenerator();
    virtual ~FSValueGenerator();
    
    virtual double nextValue() = 0;
    virtual void reset() = 0;
};

#endif /* defined(__Farsounds__FSValueGenerator__) */
