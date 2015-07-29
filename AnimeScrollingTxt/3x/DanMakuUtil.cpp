//
//  DanMakuUtil.cpp
//
//  Created by Rein on 2015/03/25.
//
//

#include "DanMakuUtil.h"
#include "DanMakuJsonHelper.h"
#include "DanMakuData.h"

DanMakuUtil *DanMakuUtil::createUtil(){
    auto ret = new (std::nothrow) DanMakuUtil();
    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

DanMakuUtil::DanMakuUtil(){
    jsonHelper = DanMakuJsonHelper::createJsonHelper();
}

DanMakuUtil::~DanMakuUtil(){
    
}

std::vector<DanMakuData *> DanMakuUtil::loadDanmakuData(const char *jsonStr){
    std::vector<DanMakuData *> presentDanMaku = jsonHelper->parseJson(jsonStr);
    
    return presentDanMaku;
}
