//
//  FSTableModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/22/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSTableModule__
#define __Farsounds__FSTableModule__

#include "FSModule.h"

// 1 input, lookup signal 0 - 1
// 1 output, looked up value
class FSTableModule :public FSModule {
    double *_table;
    int _tableLength;
    
public:
    FSTableModule(double *table, int tableLength);
    void run();
};

#endif /* defined(__Farsounds__FSTableModule__) */
