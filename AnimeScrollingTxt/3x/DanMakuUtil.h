//
//  DanMakuUtil.h
//
//  Created by Rein on 2015/03/25.
//
//

#ifndef __DanMakuUtil__
#define __DanMakuUtil__

#include "cocos2d.h"
using namespace cocos2d;

class DanMakuJsonHelper;
class DanMakuData;
class DanMakuUtil : public Ref{
public:
    static DanMakuUtil *createUtil();

    DanMakuUtil();
    virtual ~DanMakuUtil();
    
    std::vector<DanMakuData *> loadDanmakuData(const char *jsonStr);
    
private:
    DanMakuJsonHelper* jsonHelper;
};

#endif /* defined(__DanMakuUtil__) */
