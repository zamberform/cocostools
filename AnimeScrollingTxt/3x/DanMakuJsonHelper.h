//
//  DanMakuJsonHelper.h
//
//  Created by Rein on 2015/03/26.
//
//

#ifndef __DanMakuJsonHelper__
#define __DanMakuJsonHelper__

#include "cocos2d.h"

class DanMakuData;
class DanMakuJsonHelper : public cocos2d::Ref {
public:
    static DanMakuJsonHelper* createJsonHelper();
    
    std::vector<DanMakuData *> parseJson(const char* jsonString);

};

#endif /* defined(__DanMakuJsonHelper__) */
