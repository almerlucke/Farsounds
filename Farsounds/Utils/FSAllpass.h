//
//  FSAllpass.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSAllpass__
#define __Farsounds__FSAllpass__

class FSAllpass {
    double *_delay;
    int _delayLength;
    int _head;
    
public:
    double feedback;
    
    FSAllpass(int delayLength);
    ~FSAllpass();
    double generate(double input);
};

#endif /* defined(__Farsounds__FSAllpass__) */
