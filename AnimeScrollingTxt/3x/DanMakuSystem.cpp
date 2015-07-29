//
//  DanMakuSystem.cpp
//
//  Created by Rein on 2015/03/25.
//
//

#include "DanMakuSystem.h"
#include "DanMakuUtil.h"
#include "DanMakuData.h"

DanMakuSystem* DanMakuSystem::create(Size danmakuSize){
    auto ret = new (std::nothrow) DanMakuSystem();
    if (ret && ret->init(danmakuSize))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool DanMakuSystem::init(Size danmakuSize){
    if (!LayerColor::init()) {
        return false;
    }
    
    setContentSize(danmakuSize);
    
    startPosY = getContentSize().height;
    
    textStartX = getContentSize().width/2;
    
    runSpeed = 100.0f;
    
    return true;
}

void DanMakuSystem::loadDanmaku(const char *textJson){
    danMakuSupport = DanMakuUtil::createUtil();
    
    std::vector<DanMakuData *> danmakus = danMakuSupport->loadDanmakuData(textJson);
    
    for (int i = 0; i<danmakus.size(); i++) {
        initDanmakus(danmakus, i);
    }
}

void DanMakuSystem::initDanmakus(std::vector<DanMakuData*> danmakus, int index){
    auto danmaku = dynamic_cast<DanMakuData *>(danmakus[index]);
    
    auto danmakuLabel = Label::createWithTTF(danmaku->getTextMessage(), danmaku->getTextFontName(), danmaku->getTextFontSize());
    danmakuLabel->setAnchorPoint(Vec2(0, 1));
    
    float adjustPosX = 0.0f;
    switch (danmaku->getPositionType()) {
        case TEXT_POSITION_TOP:
        case TEXT_POSITION_BOTTOME:
            adjustPosX = getContentSize().width / 2;
            danmakuLabel->setAnchorPoint(Vec2(0.5,1));
            break;
        default:
            adjustPosX = textStartX + danmaku->getDelayTime() * runSpeed;
            break;
    }
    
    danmakuLabel->setPosition(Vec2(adjustPosX
                                   , startPosY));
    
    danmakuLabel->setColor(danmaku->getTextColor());
    addChild(danmakuLabel);
    
    if (index > 0) {
        auto danmakuPreData = dynamic_cast<DanMakuData *>(danmakus[index - 1]);
        float textPosY = 0.0f;
        if (danmaku->getPositionType() == TEXT_POSITION_BOTTOME) {
            textPosY = danmakuLabel->getContentSize().height;
            
            if (danmakuPreData->getPositionType() == TEXT_POSITION_BOTTOME) {
                textPosY = labels[index - 1]->getPosition().y + labels[index - 1]->getContentSize().height;
            }
            
            danmakuLabel->setPositionY(textPosY);
        }
        
        if (danmaku->getPositionType() == TEXT_POSITION_TOP) {
            textPosY = getContentSize().height;
            
            if (danmakuPreData->getPositionType() == TEXT_POSITION_TOP) {
                textPosY = labels[index - 1]->getPosition().y - labels[index - 1]->getContentSize().height;
            }
            
            danmakuLabel->setPositionY(textPosY);
        }
    }
    
    if (index > 0 && danmaku->getPositionType() == TEXT_POSITION_NORMORL) {
        auto adjustPosY = 0.0;
        auto adjustPrePosX = labels[index - 1]->getPositionX() + labels[index - 1]->getContentSize().width;
        if (adjustPosX <= adjustPrePosX) {
            adjustPosY = labels[index - 1]->getPositionY()-danmakuLabel->getContentSize().height / 2 - labels[index - 1]->getContentSize().height / 2;
            
            danmakuLabel->setPositionY(adjustPosY);
        }
        danmakuLabel->setPositionX(adjustPosX);
    }
    
    labels.push_back(danmakuLabel);

    FiniteTimeAction *action1;
    FiniteTimeAction *action2;
    
    if (danmaku->getPositionType() != TEXT_POSITION_NORMORL) {
        action1 = DelayTime::create(danmaku->getDelayTime());
    }
    else{
        action1 = MoveTo::create((adjustPosX + danmakuLabel->getContentSize().width) / runSpeed, Vec2(-danmakuLabel->getContentSize().width, danmakuLabel->getPosition().y));
    }
    action2 = CallFunc::create(CC_CALLBACK_0(Label::removeFromParent, danmakuLabel));
    
    danmakuLabel->runAction(Sequence::create(action1, action2, NULL));
}

void DanMakuSystem::setDanmakuAlpha(float alphaNum){
    for (int i = 0; i<labels.size(); i++) {
        auto colorEffect = labels[i]->getTextColor();
        colorEffect.a = alphaNum;
        
        labels[i]->setTextColor(colorEffect);
    }
}

void DanMakuSystem::setStartY(int y){
    startPosY = y;
}

void DanMakuSystem::setTextStartX(int x){
    textStartX = x;
}

void DanMakuSystem::setDanmakuRunSpeed(float danmakuSpeed){
    runSpeed = danmakuSpeed;
}

