//
//  FSPanningModule.h
//  Farsounds
//
//  Created by aFrogleap on 2/15/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#ifndef __Farsounds__FSPanningModule__
#define __Farsounds__FSPanningModule__

#include "FSModule.h"

class FSPanningModule : public FSModule {
    double _position; // from -1 to 1
    
public:
    FSPanningModule();
    FSPanningModule(double position);
    void run();
};

#endif /* defined(__Farsounds__FSPanningModule__) */
