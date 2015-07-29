//
//  DanMakuEnum.h
//
//  Created by Rein on 2015/03/26.
//
//

#ifndef DanMakuDefine_h
#define DanMakuDefine_h

#include "cocos2d.h"
using namespace cocos2d;

#define CC_CREATE_NO_PARAM_NO_INIT(varType)\
public: \
static inline varType *create(void){ \
varType *var = new varType();\
if (var)\
{\
var->autorelease();\
return var;\
}\
CC_SAFE_DELETE(var);\
return nullptr;\
}

typedef enum {
    TEXT_NORMORL
} MakuTextType;

typedef enum {
    TEXT_POSITION_NORMORL = 0,
    TEXT_POSITION_TOP,
    TEXT_POSITION_BOTTOME
} MakuTextPositionType;

#endif
