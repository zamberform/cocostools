//
//  DanMakuSystem.h
//
//  Created by Rein on 2015/03/25.
//
//

#ifndef __DanMakuSystem__
#define __DanMakuSystem__

#include "cocos2d.h"
using namespace cocos2d;

class DanMakuUtil;
class DanMakuData;
class DanMakuSystem : public LayerColor {
public:
    static DanMakuSystem* create(Size danmakuSize);
    void loadDanmaku(const char *textJson);
    
    void setStartY(int y);
    void setTextStartX(int x);
    void setDanmakuAlpha(float alphaNum);
    
    void setDanmakuRunSpeed(float danmakuSpeed);
private:
    bool init(Size danmakuSize);
    
    void initDanmakus(std::vector<DanMakuData*> danmakus, int index);
    
    DanMakuUtil* danMakuSupport;
    std::vector<Label *> labels;
    
    float startPosY;
    float textStartX;
    float runSpeed;
};

#endif /* defined(__DanMakuSystem__) */
