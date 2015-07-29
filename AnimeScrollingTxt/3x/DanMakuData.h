//
//  DanMakuData.h
//
//  Created by Rein on 2015/03/26.
//
//

#ifndef DanMakuData_h
#define DanMakuData_h

#include "DanMakuDefine.h"

class DanMakuData: public cocos2d::Ref{
    CC_CREATE_NO_PARAM_NO_INIT(DanMakuData);
    
    CC_SYNTHESIZE(std::string, textMessage, TextMessage);
    
    CC_SYNTHESIZE(int, textId, TextId);
    
    CC_SYNTHESIZE(MakuTextType, textType, TextType);
    
    CC_SYNTHESIZE(cocos2d::Color3B, textColor, TextColor);
    
    CC_SYNTHESIZE(float, delayTime, DelayTime);
    
    CC_SYNTHESIZE(MakuTextPositionType, positionType, PositionType);
    
    CC_SYNTHESIZE(float, textSpeed, TextSpeed);
    
    CC_SYNTHESIZE(float, textFontSize, TextFontSize);
    
    CC_SYNTHESIZE(std::string, textFontName, TextFontName);
    
    CC_SYNTHESIZE(std::string, userName, UserName);
};

#endif
